#include "GameLib.hpp"
#include <stdio.h>

// sets the table to zero cards and no players
void cleanTable(gameTable *table){
    table->numCards = 0;
    table->players.clear();
    return;
}

// initializer for the game-state
void initGameState(GameState *state, int numDeck){
    int i;
    if (state == NULL) return;

    // zero the history count
    for (i = 0; i < 13; i++){
        state->history[i] = 0;
    }

    state->numDecks = numDeck;
    cleanTable(&(state->table));

    return;
}

void extractValues(gameTable *table){
    return;
}

// translates the matrix (frame) to a table data structure
void getTableFromMat(gameTable *confirmTable, Mat *matrix){
    return;
}

// a sub-function for checkDiffTables() returns 1 iff the hands have the same card values
/* this function takes the two hands to compare makes a copy of them
 * sorts the copy and compares every component on both hands
 * a mis-match will occur if we have tow comp. with the same order in the hand but with different card values
 * IMPORTANT: WE DO NOT ASSUME THE CARDS ARE READ IN A SPECIFIC ORDER IN OPPOSED TO HANDS
 */
int compareHands(hand handA, hand handB){
    uint i, j;
    char match;
    hand tempA, tempB;

    // copy hands data over to temp. vars.
    tempA.numHand = handA.numHand;
    tempA.cards = handA.cards;
    tempB.numHand = handB.numHand;
    tempB.cards = handB.cards;

    for (i = 0; i < tempA.cards.size(); i++){
	match = 0;
        for (j = 0; j < tempB.cards.size(); j++){
            if (tempA.cards.at(i).val == tempB.cards.at(j).val){
                tempB.cards.at(j).val = -1;  // mark the card in hand B for next iterations
                match = 1;
                break;
            }
        }

        if (!match) return 0;   // we didn't find a match for card i in hand A - the hands are not the same
    }

    return 1;
}

// returns 0 if the tables are the same, 1 if they are different
int checkDiffTables(gameTable *TableA, gameTable *tableB){

    // different number of cards on the table
    if (TableA->numCards != tableB->numCards) return 1;
    // different number of hands on the table
    if (TableA->players.size() != tableB->players.size()) return 1;
    // run over the hands - they are ordered so theyre place in the vector should be the same
    uint i = 0;
    int diff = 0;
    for (i = 0; i < TableA->players.size(); i++){
        // compare the two hands
        diff = compareHands(TableA->players.at(i), tableB->players.at(i));
        if (!diff) return 1;
    }

    return 0;
}


// gets a table and a array of size 13 and returns in the array how many cards from wach value there are in the table
void getTableInventory(gameTable *table, char inv[]){
    hand *handPtr = NULL;
    int i, j;
    char val;

    for (i = 0; i < table->players.size(); i++){
        handPtr = (&table->players.at(i));
        for (j = 0; j < handPtr->cards.size(); j++){
            val = handPtr->cards.at(j).val;
            if (val > 13 || val < 1) {
                continue; // an exception
            }
            else {
                inv[val-1]++;
            }
        }
    }
}

/* returns in an array of size 13 - for each card value (2, 3,...,K,A) how many more cards of that value
 * there are in table A compared to table B
 */
void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){
    char inventoryA[13] = {0};
    char inventoryB[13] = {0};
    char diffInventory[13] = {0};
    hand *handPtr = NULL;
    int i, j;
    char val = 0;
printf("in getDiffTables.\n");fflush(stdout);

    if (size != 13) return;
    getTableInventory(tableA, inventoryA);
    getTableInventory(tableB, inventoryB);

    for (i = 0; i < 13; i++){
        diff[i] = inventoryA[i] - inventoryB[i];
    }

	printf("done in func.\n");fflush(stdout);
    return;
}

//checks if the new table is consistant with the new table
// returns 1 iff they are consistant
int checkConsistancy(gameState state, gameTable newTable){
    return 1;
}

/* updates the state of the game according to the new table state - assuming THERE IS a difference
 * - adds to history new cards
 * - update hands of players and adds new ones if needed
 * - updates number of cards on the table
*/
void updateGameState(gameState *state, gameTable newTable){
    uint i = 0;
    vector<hand> *hands = &(state->table.players);
    vector<hand> *newHands = &(newTable.players);
    hands->at(0).cards;

    // no new cards or ne whands on the table - nothing to do
    if ((state->table.numCards == newTable.numCards) && (hands->size() == newTable.players.size())) return;

    // the table is clean - a game was finished: clean the table
    if (state->table.numCards == 0){
        cleanTable(&(state->table));
        return;
    }

    // if we have the same number of hands - then there is a new card in a hand
    if (hands->size() == newHands->size()){
        for (i = 0; i < hands->size(); i++){

        }
    }
}


int main(){
    gameTable table;
    hand hand1;
    hand hand2;
    int i;

    //tests for cleanTable()
	printf("starting tests\n\n");

    // insert stuff
	printf("adding stuff to the table\n");
    table.numCards = 1;
    hand1.handValue = 2;
    hand1.numHand = 1;
    table.players.push_back(hand1);
    // print the stuff
	printf("printing it out\n");
    if (table.players.size() == 0) printf("the table is empty\n");
    else {
	printf("not empty\n");
    	printf("the table has: %d card(s),",table.numCards);
	printf("%d hand(s),", table.players.size());
	printf(" the hand number is %d,", table.players.at(0).numHand);
	printf(" the hand value is %d\n", table.players.at(0).handValue);
	}

    printf("cleaning table\n");
    cleanTable(&table);
    // print the stuff
    if (table.players.size() == 0) printf("the table is empty\n");
    else printf("the table has: %d card(s), %d hand(s), the hand number is %d, the hand value is %d\n",
                table.numCards, table.players.size(), table.players.at(1).numHand, table.players.at(1).handValue);
	printf("end of cleanTable() test\n\n\n");
	//tests for void initGameState(GameState *state, int numDeck)
        printf("testing void initGameState(GameState *state, int numDeck)\n");
        GameState state;
        printf("passing NULL instead of a state\n");
        initGameState(NULL, 3);
        printf("didn't crash!\n");
        printf("init with a real struct:\n");
        initGameState(&state, 1);
        printf("printing history:\n");
        for (i = 0; i < 13; i++){
            printf("%d: %d\t",i, state.history[i]);
        }
        printf("\n");
        printf("numDecks: %d", state.numDecks);
        printf("checking table\n");
        if (table.players.size() == 0) printf("the table is empty\n");
        else {
            printf("not empty\n");
            printf("the table has: %d card(s),",table.numCards);
            printf("%d hand(s),", table.players.size());
            printf(" the hand number is %d,", table.players.at(0).numHand);
            printf(" the hand value is %d\n", table.players.at(0).handValue);
            }
	printf("end of initGameState() test\n\n\n");

 	//tests for void extractValues(gameTable *table)
        //printf("testing void initGameState(GameState *state, int numDeck)\n");


         //tests for int compareHands(hand handA, hand handB){
                printf("testing int compareHands(hand handA, hand handB){\n\n");

                card cards[10];

                printf("creating two similar hands\n");
                for (i = 0; i < 5; i++){
                    cards[i].val = i;
                    hand1.cards.push_back(cards[i]);
                }
                hand1.handValue = 1;

                for (i = 5; i < 10; i++){
                    cards[i].val = 9-i;
                    hand2.cards.push_back(cards[i]);
                }
                hand2.handValue = 1;

                printf("comparing\n");
                if (compareHands(hand1, hand2) == 1){
                    printf("the func. worked\n");
                }
                else {
                    printf("error\n");
                }
		for (i = 0;i < 10; i++){
			printf("%d: %d\t", i, cards[i].val);
		}
		printf("\n");

		printf("creating two defferent hands\n");
                for (i = 0; i < 5; i++){
                    cards[i].val = i+1;
                    hand1.cards.push_back(cards[i]);
                }
                hand1.handValue = 1;

                for (i = 5; i < 10; i++){
                    cards[i].val = i+1;
                    hand2.cards.push_back(cards[i]);
                }
                hand2.handValue = 2;

                printf("comparing\n");
                if (compareHands(hand1, hand2) == 0){
                    printf("the func. worked\n");
                }
                else {
                    printf("error\n");
                }
		for (i = 0;i < 10; i++){
			printf("%d: %d\t", i, cards[i].val);
		}
		printf("\n");

	
                printf("end of int compareHands(hand handA, hand handB){ test\n\n\n");




	//tests for int checkDiffTables(gameTable *TableA, gameTable *tableB){
        printf("testing int checkDiffTables(gameTable *TableA, gameTable *tableB){\n\n");
	gameTable table1, table2;

                printf("setting the tables to diff. num of cards\n");
                table1.numCards = 0;
                table2.numCards = 4;
                printf("checking\n");
                if (checkDiffTables(&table1, &table2) == 1){
                    printf("the func. worked\n");
                }
                else printf("error\n");
                printf("setting the tables to diff num of hands\n");
		table1.numCards = 4;
                table1.players.push_back(hand1);
                table1.players.push_back(hand2);
                table2.players.push_back(hand1);
                printf("checking\n");
                if (checkDiffTables(&table1, &table2) == 1){
                    printf("the func. worked\n");
                }
                else printf("error\n");
                printf("setting the tables to same hands exactly, same #cards\n");
                table2.players.push_back(hand2);
                printf("checking\n");
                if (checkDiffTables(&table1, &table2) == 0){
                    printf("the func. worked\n");
                }
                else printf("error\n");
                printf("setting the hands to same #hands, #cards, diff hands");
                table1.players.at(1).cards.at(0).val = 13;
                printf("checking\n");
                if (checkDiffTables(&table1, &table2) == 1){
                    printf("the func. worked\n");
                }
                else printf("error\n");
	
	


	printf("end of int checkDiffTables(gameTable *TableA, gameTable *tableB){ test\n\n\n");



	//tests for void getTableInventory(gameTable *table, char inv[]){{
        printf("testing void getTableInventory(gameTable *table, char inv[]){\n\n");
	
	char inv[13] = {0};
	//zero everything
	for (i = 0; i < 13; i++){
		printf("%d:%d\t", i, inv[i]);
		cards[i].val = 0;
	}	
	printf("\n");
	table1.players.clear();
	hand1.cards.clear();
	hand2.cards.clear();
	//populate
	for (i = 0; i < 5; i++){
		cards[i].val = i+1;
		hand1.cards.push_back(cards[i]);	
	}
	for (i = 5; i < 10; i++){
		cards[i].val = 10-i;
		hand2.cards.push_back(cards[i]);
	}
	table1.players.push_back(hand1);
	table1.players.push_back(hand2);

	
	getTableInventory(&table1, inv);
	for (i = 0; i < 13; i++){
		printf("%d:%d\t", i, inv[i]);
	}	
	printf("\n");

	printf("end of void getTableInventory(gameTable *table, char inv[]){ test\n\n\n");



	 //tests for void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){
                printf("testing void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){\n");
                cleanTable(&table1);
                cleanTable(&table2);
                hand hands1[4] = {0};
                hand hands2[4] = {0};
                card cards2[20] = {0};

                cards2[0].val = 2;
                cards2[1].val = 1;
                cards2[2].val = 13;
                cards2[3].val = 11;
                cards2[4].val = 8;
                cards2[5].val = 7;
                cards2[6].val = 6;
                cards2[7].val = 6;

                cards2[8].val = 2;
                cards2[9].val = 1;
                cards2[10].val = 13;
                cards2[11].val = 11;
                cards2[12].val = 8;
                cards2[13].val = 7;
                cards2[14].val = 6;
                cards2[15].val = 6;
                cards2[16].val = 13;
                cards2[17].val = 6;
		cards2[18].val = 3;
		cards2[19].val = 6;

		printf("finished init. cards\n");
                // create two hands
                for (i = 0; i < 4; i++){
                    hands1[i].cards.push_back(cards2[2*i]);
                    hands1[i].cards.push_back(cards2[2*i+1]);
                    hands2[i].cards.push_back(cards2[2*i + 8]);
                    hands2[i].cards.push_back(cards2[2*i+1 + 8]);
                }
                hands2[2].cards.push_back(cards2[16]);
                hands2[3].cards.push_back(cards2[17]);
		hands2[3].cards.push_back(cards2[18]);
		hands2[3].cards.push_back(cards2[19]);

		printf("created hands.\n");fflush(stdout);
                for (i = 0; i < 4; i++){
                    table1.players.push_back(hands1[i]);
                    table2.players.push_back(hands2[i]);
                }

		printf("getTableDiff.\n");fflush(stdout);
                int diff[13] = {0};
                getDiffTables(&table2, &table1, diff, 13);

		for (i = 0; i < 13; i++){
			printf("%d:%d\t", i, diff[i]);
		}
		printf("\n");

                printf("end of void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){ test\n\n\n");


	//tests for int compareHands(hand handA, hand handB){
        //printf("testing int compareHands(hand handA, hand handB){\n");
	//
	//printf("end of int compareHands(hand handA, hand handB){ test\n\n\n");
        return 1;

}
