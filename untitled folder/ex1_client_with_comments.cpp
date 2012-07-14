#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_MSG_LEN 1024

//PROTOTYPES DEC.
int checkAnswer(char *buffer);
int sendall(int s, char *buf, int *len);
void readBuffer(char *buffer, int bufLen);

int main(int argc, char **argv){
	int sockfd;     // listening socket descriptor
	char *PORT, buf[MAX_MSG_LEN];

	fd_set master, readfds;		//we use these for select()
	int maxfd;			//maxfd will hold the highest valued fd - stdin

	int yes=1;        // for setsockopt() SO_REUSEADDR, below
	int rv, numbytes;

	struct addrinfo hints, *ai;		//hints will be set to what kind of address we want, ai will be what we get to use

	//check argumets
	if (argc != 2){
		fprintf(stdout, "ERROR: please enter port number as an argument\n");
		return 0;
	}

	//just assign argv[1] to the char *port var.
	PORT = argv[1];

	//reset hints -- clean it up of junk
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;		//set address family to ipv4
	hints.ai_socktype = SOCK_STREAM;	//we want a stream address
	hints.ai_flags = AI_PASSIVE;		//passive == default settings to the rest
	if ((rv = getaddrinfo("127.0.0.1", PORT, &hints, &ai)) != 0) {	//get an address
		fprintf(stderr, "ERROR: %s\n", gai_strerror(rv));   //rv is just for error ref.
		return 0;
	}

	//get a socket to communicate  with the server
	sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (sockfd < 0){
		fprintf(stdout, "ERROR: couldn't get a socket from the OS!!\n");
		freeaddrinfo(ai);
		return 0;
	}

	//beej used this to remove some kind of error message that might pop-up here so we follow the beej
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	//connect to ai - the address with the socket we got - on the other end of the line the server sees this and accept()s us.
	if (connect(sockfd, ai->ai_addr, ai->ai_addrlen) == -1) {
		close(sockfd);
		freeaddrinfo(ai);
		fprintf(stdout, "ERROR: failed to connect to server\n");
		return 0;
	}

	freeaddrinfo(ai); // all done with this

	//reset the sets we use select() with
	FD_ZERO(&master);
	FD_SET(sockfd, &master);
	maxfd = sockfd;	//select will need the highest valued fd so save this one here - it is the only one we have here anyway
	FD_ZERO(&readfds);

	printf("you are now connected: enter 'exit' to quit.\n\n");

	while(1){
		printf(">>");
		if (fgets(buf, MAX_MSG_LEN, stdin) == NULL) {		//read from user
			fprintf(stdout, "Error: EOF or IO error occurred\n");
		}
		numbytes = strlen(buf);
		buf[numbytes-1] = '\0';		//null-terminate! SAFETY FIRST!
		numbytes--;		//fgets reads the '\n' char to the buffer so in the line above we changed it to '\0' here we cut the length by one

		if (sendall(sockfd, buf, &numbytes) == -1){
			fprintf(stdout, "ERROR: failed to send the whole buffer\n"
					"sent only %d bytes out of %d, \n", numbytes, (int)strlen(buf));
		}

		if (strcmp("exit", buf) == 0){		//if the user send exit  -- exit
			break;
		}

		readfds = master;
		if (select(maxfd+1, &readfds, NULL, NULL, NULL) == -1){
			perror("select");
			return 0;
		}

		if (FD_ISSET(sockfd, &readfds)){
			numbytes = recv(sockfd, buf, MAX_MSG_LEN ,0);
			if (numbytes == 0){    //this value means: connection closed
				break;
			}

			if (numbytes == -1){		//this value means an error has occured
				fprintf(stdout, "ERROR: error handling client\n");
				break;
			}
			else {
				buf[numbytes] = '\0';	//null-terminate the string we send (again i know)
				if (checkAnswer(buf)) {   //check if we got an output on a top command otherwise just keep on working normaly
					printf("%s\n", buf);
				}
			}
		}
	}

	printf("exiting stackClient\n");
	close(sockfd);
	return 1;
}


/*beej's function: wrapping a send() function to make sure big buffers
 * are sent properly
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

int checkAnswer(char *buffer){
	char *p = NULL;

	p = buffer;
	while (*p != '\0' && *p != ' ')
		p++;

	if (*p == '\0') return 0; //no space means not an output on a top command

	if (*p == ' '){
		*p = '\0';   //mark the space char
		if (strcmp("OUTPUT:", buffer) == 0){
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
