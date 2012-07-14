/*general workflow of the server:
			get an address (by pref.) --> get a socket (that fits the address pref.'s) --> bind them together --> start listening ---
						--> accept conections from new client with a new service thread.
		
			each client has a thread of his own in the process:
					we loop over:
						1.recV() a command from user.
						2.send() back a default msg. or an input msg. to the client

					remember: we send() back a msg. (2) - at the other end the client will wait for that msg.
							this is done so the client won't send a bunch of messages to the server
							and we will end-up with a buffer containing a concatenation of two commands.
*/




#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "Libs/dequeue.h"

#define NUM_CLIENTS 15     //max number of clients we want backlogged on listen
#define MAX_MSG_SIZE 1024  //max size for messages

int pushBottomCommand(char *buffer);
void *serve_client(void *args);
int sendall(int s, char *buf, int *len);
void extractPushStr(char *dqBuf, char *destBuf);
int pushCommand(char *buffer);

void randMutateStr(char *str);

struct thread_args{
	int fd;
	dequeue *dq;
};

int main(int argc, char **argv)
{

	int listener;     			// listening socket descriptor
	int newfd;      		 	 // newly accept()ed socket descriptor
	char *PORT;				//we will assign this ptr the argv[1] ptr address just to clarify the code later (argv[1] == port # from 							//											command line)
	struct sockaddr_in remoteaddr; 		// client address: we pass this to accept - it will conatin info on our new client - we don't
						//				don't use it just need it to run accept()
	socklen_t addrlen;			// this will hold the size of remoteaddr when accept() returns

	dequeue *dq;				//our dequeue

	fd_set master, readfds;			//fd sets to pass to select() - master will hold listener and stdout, readfds will be passed to select
						//		--because select changes the set it works on we keep a master set and copy from it 
						//		to readfds each time before we select()
	int fdmax;				// select (for some reason) needs the highest numberd fd + 1 value we use to be passed to it

	int yes=1;        			// for setsockopt() SO_REUSEADDR, below
	int rv;

	struct addrinfo hints, *ai;		//we are going to ask for an address - hints is what we basicaly want - ai will be what we get

	//threads related vars.
	pthread_t thread;			// pthread_t is an int or a long this var. we pass it to pthread_create it will hold the thread's id
	int thread_rv;				// return value from pthread_create() - just to catch errors
	struct thread_args eta[1];		// a struct we built to pass arguments to the function we run we pthread_create

	
	// check input from commamd line
	if (argc != 2){
		fprintf(stdout, "ERROR: please enter port number as an argument\n");
		return 0;
	}

	PORT = argv[1];			//assign the port string from command line to PORT
	
	dq = createDequeue();		// create the dequeue

	eta[0].dq = dq;			//we assign the dq to the struct - this is passed to each thread

	// get us a socket and bind it

	memset(&hints, 0, sizeof hints); 		//nullify hints (write zeros to it)
	hints.ai_family = AF_INET;			//set use ipv4
	hints.ai_socktype = SOCK_STREAM;		//not sure about this one - basically anything else is default defined
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo("127.0.0.1", PORT, &hints, &ai)) != 0) {	//get the address back to ai (last argument in this call
		fprintf(stdout, "ERROR: %s\n", gai_strerror(rv));   //rv is just for error ref.
		return 0;
	}

	//get an fd from the OS we ask for a socket that matches the addrinfo from getaddrinfo
	listener = socket(ai->ai_family, ai->ai_socktype, 0);
	if (listener < 0) {
		fprintf(stdout, "ERROR: couldn't get a socket from the OS!!\n");
		freeaddrinfo(ai); // all done with this
		return 0;
	}

		//NOTICE:  I wrote in the comment below that this is beej's function - this is a library function that beej used
		// 			didn't realy understand why - but all it does is remove some kind of err. msg. so it can't do any harm
	// lose the pesky "address already in use" error message   --- this is another one of beej's functions
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	//we bind the socket and the addres together so next we can listen()
	if (bind(listener, ai->ai_addr, ai->ai_addrlen) < 0) {
		close(listener);
		freeaddrinfo(ai); // all done with this
		return 0;
	}

	freeaddrinfo(ai); // all done with this

	// listen -- after this call we can start handling clients using accept()
	if (listen(listener, 15) == -1) {
		perror("listen");
		close(listener);
		return 0;
	}

	FD_ZERO(&master);	//this function resets the set before the first use
	FD_ZERO(&readfds);	//same as above

	FD_SET(listener, &master);	//put listener in the master set
	FD_SET(0, &master);		//put stdin in the master set
	fdmax = listener;		//set fdmax to be the highest value of fd we use

	printf("DEBUG: started stack-server\npress any key to exit\n");

	// main loop
	while(1) {
		readfds = master; // copy master to readfds
		if (select(fdmax+1, &readfds, NULL, NULL, NULL) == -1) {  //run select()
			perror("select");
			exit(0);
		}

		if (FD_ISSET(listener, &readfds)){		//check if we have someone to accept() -- a new client that wants to talk to us
			newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);//accept the new client - we get back a new fd for this client
			eta[0].fd = newfd;		//set the thread args struct fd field to the new fd
			thread_rv = pthread_create(&thread, NULL, serve_client, (void *)&eta[0]);//create a new thread to handle the new client
			if (thread_rv){//err checking
				fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", thread_rv);
			}
		}
		
		if (FD_ISSET(0, &readfds)){		//check if someone pushed a key -- this is a sign for us to exit
			break;
		}
	}

	freeDequeue(dq);		//free dq
	close(listener);		//close the fd we listened on
	return 1;
}



/*beej's function: wrapping a send() function to make sure big buffers
 * are sent properly-- we have a problem if the os decides to cut our msg for it's own reasons we have to make sure we sent the whole thing
	probably not a must-use function but according to beej as the data size we want to send grows there is a chance for this problem to pop-up
 */
int sendall(int s, char *buf, int *len)
{
	int total = 0;        // how many bytes we've sent
	int bytesleft = *len; // how many we have left to send
	int n;

	while(total < *len) {
		n = send(s, buf+total, bytesleft, 0);
		if (n == -1) { break; }
		total += n;
		bytesleft -= n;
	}

	*len = total; // return number actually sent here

	return n==-1?-1:0; // return -1 on failure, 0 on success
}


/*the thread's function to handle a single client on stackServer prog.*/
void *serve_client(void *args){
	int numbytes = -2, fd;
	char buf[MAX_MSG_SIZE];
	struct thread_args *eta;
	dequeue *dq;
	char dqBuffer[MAX_MSG_SIZE];

	eta = (struct thread_args *)args;
	fd = eta->fd;
	dq = eta->dq;

	fd_set master, readfds;		//we handle select issues the same as in the main thread
	int maxfd;

	FD_ZERO(&master);
	FD_ZERO(&readfds);
	FD_SET(fd, &master);
	maxfd = fd;

	while (1){
		readfds = master;
		if (select(maxfd+1, &readfds, NULL, NULL, NULL) == -1){
			perror("select");
			return 0;
		}
		if (FD_ISSET(fd, &readfds)){
			numbytes = recv(fd, buf, MAX_MSG_SIZE ,0);

			if (numbytes == 0){    //this value means: connection closed
				break;
			}

			if (numbytes == -1){	//this value means we have encountered an error
				fprintf(stdout, "error handling client\n");
				break;
			}

			buf[numbytes] = '\0';	//null-terminate everything - do you can sleep better at night!

			if (strcmp(buf, "exit") == 0){	//if the user sent "exit" we exit the loop and close everything
				break;
			}
			//from here it is just the case of finding out what the client asked for and calling the right DQ function
			//we always send back a message so if there isn't any output to display for the client we send a default serverOK
			//message that indicates to the client we heard him and that he can pass the next request to us
		
			else if ((pushCommand(buf)) == 1){
				extractPushStr(buf, dqBuffer);
				if (push(dq, dqBuffer) == -1){
					fprintf(stdout, "ERROR: couldn't push to the dequeue\n");
				}
				strncpy(buf, "serverOK",strlen("serverOK"));
				buf[ strlen("serverOK") ] = '\0';
			}
			else if (strcmp(buf, "POP") == 0){
				pop(dq);
				strncpy(buf, "serverOK",strlen("serverOK"));
				buf[ strlen("serverOK") ] = '\0';
			}
			else if (strcmp(buf, "TOP") == 0){
				if (top(dq, dqBuffer, MAX_MSG_SIZE) == 0){
					strncpy(buf, "OUTPUT: stack is empty",strlen("OUTPUT: stack is empty"));
					buf[strlen("OUTPUT: stack is empty")] = '\0';
					dqBuffer[0] = '\0';
				}
				else {
					strncpy(buf, "OUTPUT: ",strlen("OUTPUT: "));
					strcat(buf, dqBuffer);
					buf[strlen(dqBuffer) + strlen("OUTPUT: ")] = '\0';
				}

			}
			else if (strcmp(buf, "BOTTOM") == 0){
				if (bottom(dq, dqBuffer, MAX_MSG_SIZE) == 0){
					strncpy(buf, "OUTPUT: stack is empty",strlen("OUTPUT: stack is empty"));
					buf[strlen("OUTPUT: stack is empty")] = '\0';
					dqBuffer[0] = '\0';
				}
				else {
					strncpy(buf, "OUTPUT: ",strlen("OUTPUT: "));
					strcat(buf, dqBuffer);
					buf[strlen(dqBuffer) + strlen("OUTPUT: ")] = '\0';
				}
			}
			else if (strcmp(buf, "POPBOTTOM") == 0){
				popBottom(dq);
				strncpy(buf, "serverOK",strlen("serverOK"));
				buf[ strlen("serverOK") ] = '\0';
			}
			else if (pushBottomCommand(buf) == 1){
				extractPushStr(buf, dqBuffer);
				if (pushBottom(dq, dqBuffer) == -1){
					fprintf(stdout, "ERROR: couldn't push to the dequeue\n");
				}
				strncpy(buf, "serverOK",strlen("serverOK"));
				buf[ strlen("serverOK") ] = '\0';
			}

			//send an answer to client - if he sent a top/bottom command we send back something like: "OUTPUT: %s"
			//otherwise we send the default serverOK message meaning he can send the next command to us
			numbytes = strlen(buf);
			if (sendall(fd, buf, &numbytes) == -1){
				fprintf(stderr, "ERROR: failed to send the whole buffer\n"
						"sent only %d bytes out of %d, \n", numbytes, (int)(strlen(buf)+7));
			}
		}
	}

	close(fd);
	pthread_exit(NULL);
}


/* checks if the buffer's prefix is "PUSH " */
int pushCommand(char *buffer){
	char *p = NULL;

	p = buffer;
	while (*p != '\0' && *p != ' ')
		p++;

	if (*p == '\0') return 0; //no space means not a push command

	if (*p == ' '){
		*p = '\0';   //mark the space char
		if (strcmp("PUSH", buffer) == 0){
			*p = ' ';    //remove the mark
			return 1;
		}
		else {
			*p = ' ';    //remove the mark
			return 0;
		}
	}

	return 0;    //if we got here it can't be a PUSH command return 0;
}


/*checks if the buffer's prefix is "PUSHBOTTOM"*/
int pushBottomCommand(char *buffer){
	char *p = NULL;

	p = buffer;
	while (*p != '\0' && *p != ' ')
		p++;

	if (*p == '\0') return 0; //no space means not a push command

	if (*p == ' '){
		*p = '\0';   //mark the space char
		if (strcmp("PUSHBOTTOM", buffer) == 0){
			*p = ' ';    //remove the mark
			return 1;
		}
		else {
			*p = ' ';    //remove the mark
			return 0;
		}
	}

	return 0;    //if we got here it can't be a PUSH command return 0;
}

/*a function ver similar to puchCmd only it extracts the string
 * passed to push - we didn't want to clutter the while loop in serve_client more
 * than we had to
 */
void extractPushStr(char *Buf, char *destBuf){
	char *p = NULL;

	p = Buf;
	while (*p != '\0' && *p != ' ')
		p++;

	if (*p == '\0') return;
	else if (*p == ' '){
		p++;
		strncpy(destBuf, p,strlen(p));
		destBuf[strlen(p)] = '\0';
	}
	return;
}



