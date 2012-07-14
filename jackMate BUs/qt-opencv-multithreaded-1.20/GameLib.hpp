
#ifndef GAMELIB_HPP
#define GAMELIB_HPP

#endif // GAMELIB_HPP

#define NEW_GAME        0
#define PLAYER_TURN     1
#define DEALER_TURN     2
#define END_GAME        3

#define BLACK_JACK      10000


#define _GameLib_NUM_DECKS   1

#include <vector>
#include <opencv2/core/core.hpp>
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
    int numHand;    // the hand's serial number
    int handValue;  // the hand's value
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
    int history[13];
    int status;
}GameState;


//  PROTOTYPES

// initializer for the game-state
void initGameState(GameState *state, int numDeck);

// translates the matrix (frame) to a table data structure
//void getTableFromMat(gameTable *confirmTable, Mat *matrix);

// extract the values of the cards on the table
void extractValues(gameTable *table);

// gets a hand and a array of size 13 and returns in the array how many cards from wach value there are in the hand
void getHandInventory(hand h, char inv[]);

// returns 0 if the tables are the same, 1 if they are different
int checkDiffTables(gameTable *newTable, gameTable *confirmTable);

// returns the diff array of the two inventory arrays
// both of the arrays must be of size 13, and invA must represent the inventory chronologically after invB
void getDiffInventory(char invA[], char invB[], char diff[]);

//checks if the new table is consistant with the new table
// returns 1 iff they are consistant
int checkConsistancy(gameState state, gameTable newTable);

// update the game state's history with the inventory
void updateHistory(gameState *state, char inv[]);

/* updates the state of the game according to the new table state
 * - adds to history new cards
 * - update hands of players and adds new ones if needed
 * - updates number of cards on the table
*/
void updateGameState(gameState *state, gameTable newTable);

void cleanTable(gameTable *table);

// returns
void tableToString(gameState state, string *str);

// returns a string with what the player should do
std::string getAdvice(hand player, hand dealer);
