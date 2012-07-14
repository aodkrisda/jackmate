/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * GameLibh.hpp :     a library of types and methods that makes the abstraction of a black-jack game.
 *                    defines types like card, hand, game and functions on these types
 *                    in addition, the types hold extra info. for the use of the computer-vision libs.
 *
 *
 */


#ifndef GAMELIB_HPP
#define GAMELIB_HPP

//CONSTANTS

#define NUM_CARDS_IN_DECK 52

//constant game states
#define NEW_GAME        0
#define PLAYER_TURN     1
#define DEALER_TURN     2
#define END_GAME        3

// constant value for blackJack
#define BLACK_JACK      10000

//default value for number of deck
#define _GameLib_NUM_DECKS   1

#include <vector>
#include <opencv2/core/core.hpp>
#include "tablesLib.hpp"

using namespace std;
using namespace cv;

typedef struct Card{
    char value;                 //filled by SIFT
    Point center;               //center of card
    char color;                 //0 or 1 = used by DFS to find hand
    vector<Point> rect;         //describing the quardinates of the card on the image captured
    vector<Point> letter;
}card;

// a struct to represent hands
typedef struct Hand{
    int numHand;              // the hand's serial number
    int handValue;            // the hand's value
    Point center;             //used for sorting and finding the dealer
    vector<card> cards;
}hand;


typedef struct gameTable{
    int numCards;
    vector<hand> players;
}gameTable;

// we have several strategy tables with the same sign.
typedef std::string (*strategyFunctionPtr)(hand player, hand dealer);

// holds history data about the game - the card values seen

// holds all the information about the game
typedef struct gameState{
    int numDecks;
    gameTable table;
    int history[13];
    int deckCount;
    int status;
    int gameCount;
    int winCount;
    strategyFunctionPtr stratFunc;
}GameState;




//  PROTOTYPES

// initializer for the game-state
void initGameState(GameState *state, int numDeck);

// cleans the history in the game state
void cleanHistory(gameState *state);

// translates the matrix (frame) to a table data structure
//void getTableFromMat(gameTable *confirmTable, Mat *matrix);

// extract the values of the cards on the table
void extractValues(gameTable *table);

// gets a hand and a array of size 13 and returns in the array how many cards from wach value there are in the hand
void getHandInventory(hand h, char inv[]);

void getTableInventory(gameTable *table, char inv[]);

// returns the running count of the inventory
int countCards(char inv[]);

// calculate the true count from the running count
int calcTrueCount(gameState state);

// converts char values to numerical values
int getNumVal(char charVal);

// return the value of the hand
int getHandVal(hand h);

// returns the diff array of the two inventory arrays
// both of the arrays must be of size 13, and invA must represent the inventory chronologically after invB
void getDiffInventory(char invA[], char invB[], char diff[]);

// update the game state's history with the inventory
void updateHistory(gameState *state, char inv[]);

// cleans the table struct given
void cleanTable(gameTable *table);

// returns a string depiction of the table struct. in the game state
void tableToString(gameState *state, string *str, char inv[]);

// returns a string depiction of the history array in the game state
void historyToString(gameState state, string *output);

// returns a string with what the player should do
//std::string getAdvice(hand player, hand dealer);

void calc_hit_chance(int hand_val,int seen_history[13],char seen_history_curr[13],int num_decks,char DealerCard, float* chance_if_stand, float* chance_if_hit);

Scalar getScal(int color);

#endif // GAMELIB_HPP
