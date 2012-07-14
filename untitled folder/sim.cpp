#include <algorithms>

#define NONE	9
#define STAND	0
#define HIT	1
#define SPLIT	2



// GLOBALS
int deckSize = 52;
char deck[deckSize] = {0};
int deckIndex = 0;

char dealer[40] = {0};
int dealerSize = 0;
int dealerSum;

char player[40] = {0};
int playerSize = 0;
int playerSum;

char exFlag;
char extra[40] = {0};
int extraSize = 0;
int extraSum;

int main(){

	// init Vars.
	initVars();

	//init deck + shuffle it
	createDeck();
	shuffleDeck();
		
	//deal two cards for dealer and player
	startGame();

	// player's turn
	play = NONE;
	while (play != STAND && play != BUST){
		play = tablePlayer(dealer, player);
		if (play == HIT){
			hitPlayer();
		}
		else if (play == SPLIT){
			splitPlayer();
		}
	}

	

}

void initVars(){
	
	deckSize = 52;
	deck = {0};
	deckIndex = 0;

	dealer = {0};
	dealerSize = 0;
	dealerSum;

	play = NONE;
	player = {0};
	playerSize = 0;
	playerSum;

	exFlag = 0;
	extra = {0};
	extraSize = 0;
	extraSum = 0;
}

void createDeck(){
	// create the deck
	for (uint i = 0; i < deckSize; i++){
		deck[i] = ((i % 13) + 1 > 10)?10:(i % 13) + 1);
	}
	return;
}

void shuffleDeck(){
	//shuffle the deck
	std::random_shuffle(deck, deck + deckSize);

	return;
}

void checkDeck(){
	if (deckIndex == deckSize){
		shuffleDeck();
		deckIndex = 0;
	}
	return;
}


void startGame(){
	
	// two cards for the dealer (card 0 is hidden)
	checkDeck();
	dealer[dealerSize] = deck[deckIndex];
	deckIndex++;
	dealerSize++;
	
	checkDeck();
	dealer[dealerSize] = deck[deckIndex];
	deckIndex++;
	dealerSize++;

	dealerSum = dealer[dealerSize-2] + dealer[dealerSize-1];

	// two cards for the player
	checkDeck();
	player[playerSize] = deck[deckIndex];
	deckIndex++;
	playerSoze++;
	
	checkDeck();
	player[playerSize] = deck[deckIndex];
	deckIndex++;
	plsyerSize++;
}

void hitPlayer(){
	
	checkDeck();
	player[playerSize] = deck[deckIndex];
	playerSize++;
	deckIndex++;

	return;
}

void splitPlayer(){

	

	return;
}

int randomPlayer(char dealer[], char player[]){


	return 1;
}
	
