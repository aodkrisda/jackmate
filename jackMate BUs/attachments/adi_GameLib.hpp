
#ifndef GAMELIB_HPP
#define GAMELIB_HPP

#endif // GAMELIB_HPP


#define _GameLib_GAME_STATE int

#define _GameLib_EMPTY_TABLE 0
#define _GameLib_ONE_D       1
#define _GameLib_ONE_D_ONE_P 2
#define _GameLib_ONE_D_TWO_P 3

#include <vector>
#include "D:\\Adi\\blackjack\\openCV\\OpenCV2.2\\include\\opencv2\\core\\core.hpp"
using namespace std;
using namespace cv;

typedef struct Card{
    char value; //filled by SIFT
	Point center; //center of card
	char color; //0 or 1 = used by DFS to find hand
	vector<Point> rect; //describing the quardinates of the card on the image captured
	vector<Point> letter;
}card;

// a struct to represent hands
typedef struct Hand{
    int numHand;    //the hand's serial number
	Point center;   //used for sorting and finding the dealer
    vector<card> cards;
}hand;

typedef struct gameTable{
    int numCards;
    vector<hand> players;
}gameTable;

// holds history data about the game - the card values seen

// holds all the information about the game
typedef struct gameState{
    int numDecks;
    gameTable table;
    //card history[];
    //GAME_STATE state;
}GameState;


//  PROTOTYPES


// translates the matrix (frame) to a table data structure
void getTableFromMat(gameTable *confirmTable, Mat* matrix);

// returns 0 if the tables are the same, 1 if they are different
int checkDiffTables(gameTable *newTable, gameTable *confirmTable);

//checks if the new table is consistant with the new table
// returns 1 iff they are consistant
int checkConsistancy(gameState state, gameTable newTable);

/* updates the state of the game according to the new table state
 * - adds to history new cards
 * - update hands of players and adds new ones if needed
 * - updates number of cards on the table
*/
void updateGameState(gameState newTable);
