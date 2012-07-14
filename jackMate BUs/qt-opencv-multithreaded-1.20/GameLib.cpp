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

    state->status = NEW_GAME;

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
//void getTableFromMat(gameTable *confirmTable, Mat *matrix){
//  return;
//}

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
            if (tempA.cards.at(i).value == tempB.cards.at(j).value){
                tempB.cards.at(j).value = -1;  // mark the card in hand B for next iterations
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

// converts char values to numerical values
int getNumVal(char charVal){

    switch (charVal){
    case 'A': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case '10': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
    default: return -1;//just in case
    }


}


// gets a hand and a array of size 13 and returns in the array how many cards from wach value there are in the hand
void getHandInventory(hand h, char inv[]){
    char val;

    for (uint j = 0; j < h.cards.size(); j++){
        val = getNumVal(h.cards.at(j).value);
        if (val > 13 || val < 1) {
            continue; // an exception
        }
        else {
            inv[val-1]++;
        }
    }

    return;
}


// gets a table and a array of size 13 and returns in the array how many cards from wach value there are on the table
void getTableInventory(gameTable *table, char inv[]){
    hand *handPtr = NULL;
    int i;

    for (i = 0; i < table->players.size(); i++){
        handPtr = (&table->players.at(i));
        getHandInventory(*handPtr, inv);
    }

    return;
}

// returns the diff array of the two inventory arrays
// both of the arrays must be of size 13, and invA must represent the inventory chronologically after invB
void getDiffInventory(char invA[], char invB[], char diff[]){

    for (uint i = 0; i < 13; i++){
        diff[i] = invA[i] - invB[i];
    }
    return;
}

/* returns in an array of size 13 - for each card value (2, 3,...,K,A) how many more cards of that value
 * are there in table A compared to table B
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

    return;
}

// update the game state's history with the inventory
void updateHistory(gameState *state, char inv[]){

    for (uint i = 0; i < 13; i++){
        state->history[i] += inv[i];
    }

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

/* return the value of the hand or blackjack
 */
int getHandVal(hand h){
    int sum = 0;
    int sumA = 0;
    int val = 0;
    int ACount = 0;

    if (h.cards.size() == 2){
        if (((h.cards.at(0).value == 'A') && (h.cards.at(0).value == 'J')) ||   // blackJack
            ((h.cards.at(0).value == 'J') && (h.cards.at(0).value == 'A'))
                ){
            return BLACK_JACK;
        }

    }

    for (uint i = 0; i < h.cards.size(); i++){
        val = getNumVal(h.cards.at(i).value);
        if (val == -1) return -1;
        else if (val == 1) ACount++; //keep jacks for the end
        else if (val < 11) sum += val;
        else sum += 10;
    }

   // if (sum > 21) return 2;

    if (ACount == 0){
//        if (sum == 21) return 1;
//        else return 0;
        return sum;
    }
    else{   //jCount > 0
        sumA = (sum + 11 + (ACount-1));
        if (sumA <= 21) return sum;

        return sumA = sum + ACount;
//        if (sumA <= 21) return 1;
//        else if (sumA > 21) return 2;    //if we bust here we bust with an A == 11
//        else return 0;
    }
}

std::string getAdvice(hand player, hand dealer){

    if (player.cards.size() == 2){
        if (player.cards.at(0).value == 'A' && player.cards.at(1).value == 'A'){
            return "Suggested play: SPLIT.";
        }

        else if (( getNumVal(player.cards.at(0).value) >= 10 ) &&
                 ( getNumVal(player.cards.at(1).value) >= 10 )){
            return "Suggested play: STAND";
        }

        else if (player.cards.at(0).value == '9' && player.cards.at(1).value == '9'){
            if (dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else  if (player.cards.at(0).value == '8' && player.cards.at(1).value == '8'){
            return "Suggested play: SPLIT";
        }

        else  if (player.cards.at(0).value == '7' && player.cards.at(1).value == '7'){
            if (dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '6' && player.cards.at(1).value == '6'){
            if (dealer.cards.at(0).value == '2'){
                return "Suggested play: HIT";
            }
            else if (dealer.cards.at(0).value == '7'
                     || dealer.cards.at(0).value == '8'
                     || dealer.cards.at(0).value == '9'
                     || dealer.cards.at(0).value == 'A'
                     || dealer.cards.at(0).value == 'T'
                     || dealer.cards.at(0).value == 'J'
                     || dealer.cards.at(0).value == 'Q'
                     || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '5' && player.cards.at(1).value == '5'){
            if (dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (player.cards.at(0).value == '4' && player.cards.at(1).value == '4'){
            return "Suggested play: HIT";
        }

        else if (player.cards.at(0).value == '3' && player.cards.at(1).value == '3'){
            if (dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    || dealer.cards.at(0).value == '7'){
                return "Suggested play: SPLIT";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (player.cards.at(0).value == '2' && player.cards.at(1).value == '2'){
            if (dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    || dealer.cards.at(0).value == '7'){
                return "Suggested play: SPLIT";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '9')) ||
                 ((player.cards.at(0).value == '9') && (player.cards.at(1).value == 'A'))){
            return "Suggested play: STAND";
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '8')) ||
                 ((player.cards.at(0).value == '8') && (player.cards.at(1).value == 'A'))){
            return "Suggested play: STAND";
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '7')) ||
                 ((player.cards.at(0).value == '7') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'){
                return "Suggested play: STAND";
            }
            else if (dealer.cards.at(0).value == '3'
                     || dealer.cards.at(0).value == '4'
                     || dealer.cards.at(0).value == '5'
                     || dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '6')) ||
                 ((player.cards.at(0).value == '6') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '5')) ||
                 ((player.cards.at(0).value == '5') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '4')) ||
                 ((player.cards.at(0).value == '4') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '3')) ||
                 ((player.cards.at(0).value == '3') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '2')) ||
                 ((player.cards.at(0).value == '2') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: HIT";
            }
        }
    }// end of if player has 2 cards


    int val = 0;
    for (uint i = 0; i < player.cards.size(); i++){
        val += getNumVal(player.cards.at(i).value);
    }

    if (val == 8){
        return "Suggested play: HIT";
    }

    else if (val == 9){
        if (dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '4'
                || dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: DOUBLE DOWN";
        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 10){
        if (dealer.cards.at(0).value == 'A'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: DOUBLE DOWN";
        }
    }

    else if (val == 11){
        if (dealer.cards.at(0).value == 'A'){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: DOUBLE DOWN";
        }
    }

    else if (val == 12){
        if (dealer.cards.at(0).value == '4'
                || dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: STAND";
        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 13){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '4'
                || dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: STAND";
        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 14){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '4'
                || dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: STAND";
        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 15){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '4'
                || dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: STAND";
        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 16){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '4'
                || dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: STAND";
        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 17){
        return "Suggested play: STAND";
    }


    return "error"; //just in case
}

void tableToString(gameState state, string *str){
    int i,j, hVal, dVal;
    char endFlag = 0;
    gameTable *table = &state.table;
    hand dealer = table->players.at(0);

    std::ostringstream os;

    os << "Dealer: ";

    //print the hand
    hand *handPtr = &table->players.at(0);
    for (j = 0; j < handPtr->cards.size(); j++){
        os << handPtr->cards.at(j).value << " ";
    }
    os << "\n";

    //print hand msg
    dVal = getHandVal(table->players.at(0));
    if (dVal == BLACK_JACK){
        os << "Dealer has BlackJack";
        endFlag = 1;
    }
    else if (dVal >= 21) {  //if the dealer bust
        os << "Dealer Bust" << "\n\n";
        endFlag = 1;
    }
    else if (dVal == 21){
        os << "Dealer has 21" << "\n\n";
        endFlag = 1;
    }
    else {
        if (dVal >= 17) endFlag = 1;
        os << "Dealer has " << dVal << "\n\n";
    }

    for (i = 1; i < table->players.size(); i++){
        //print hand
        os << "Player " << i << ": ";
        hand *handPtr = &table->players.at(i);
        for (j = 0; j < handPtr->cards.size(); j++){
            os << handPtr->cards.at(j).value << " ";
        }
        os << "\n";

        //print msg
        hVal = getHandVal(table->players.at(i));
        if (hVal == BLACK_JACK){
            os << "Player" << i << " has BlackJack";
        }
        else if (hVal >= 21) {  //if the dealer is bust
            os << "Player " << i << " Bust" << "\n";
        }
        else if (hVal == 21){
            os << "Player" << i << " has 21" << "\n";
        }
        else if (state.status != DEALER_TURN){  //print advice if the players are still playing
            os << getAdvice(*handPtr, dealer) << "\n";
        }

        //end game messages
        if ((hVal <= 21) && (state.status == DEALER_TURN) && (endFlag)){
            if (hVal == dVal) {
                os << "PUSH\n";
            }
            else if (hVal > dVal){
                os << "WIN\n";
            }
            else {
                os << "LOSE\n";
            }
        }
        os << "\n";
    }
    *str = os.str();

    return;
}

//int main(){
//    gameTable table;
//    hand hand1;
//    hand hand2;
//    int i;

//    //tests for cleanTable()
//        printf("starting tests\n\n");

//    // insert stuff
//        printf("adding stuff to the table\n");
//    table.numCards = 1;
//    hand1.handValue = 2;
//    hand1.numHand = 1;
//    table.players.push_back(hand1);
//    // print the stuff
//        printf("printing it out\n");
//    if (table.players.size() == 0) printf("the table is empty\n");
//    else {
//        printf("not empty\n");
//        printf("the table has: %d card(s),",table.numCards);
//        printf("%d hand(s),", table.players.size());
//        printf(" the hand number is %d,", table.players.at(0).numHand);
//        printf(" the hand value is %d\n", table.players.at(0).handValue);
//        }

//    printf("cleaning table\n");
//    cleanTable(&table);
//    // print the stuff
//    if (table.players.size() == 0) printf("the table is empty\n");
//    else printf("the table has: %d card(s), %d hand(s), the hand number is %d, the hand value is %d\n",
//                table.numCards, table.players.size(), table.players.at(1).numHand, table.players.at(1).handValue);
//        printf("end of cleanTable() test\n\n\n");
//        //tests for void initGameState(GameState *state, int numDeck)
//        printf("testing void initGameState(GameState *state, int numDeck)\n");
//        GameState state;
//        printf("passing NULL instead of a state\n");
//        initGameState(NULL, 3);
//        printf("didn't crash!\n");
//        printf("init with a real struct:\n");
//        initGameState(&state, 1);
//        printf("printing history:\n");
//        for (i = 0; i < 13; i++){
//            printf("%d: %d\t",i, state.history[i]);
//        }
//        printf("\n");
//        printf("numDecks: %d", state.numDecks);
//        printf("checking table\n");
//        if (table.players.size() == 0) printf("the table is empty\n");
//        else {
//            printf("not empty\n");
//            printf("the table has: %d card(s),",table.numCards);
//            printf("%d hand(s),", table.players.size());
//            printf(" the hand number is %d,", table.players.at(0).numHand);
//            printf(" the hand value is %d\n", table.players.at(0).handValue);
//            }
//        printf("end of initGameState() test\n\n\n");

//        //tests for void extractValues(gameTable *table)
//        //printf("testing void initGameState(GameState *state, int numDeck)\n");


//         //tests for int compareHands(hand handA, hand handB){
//                printf("testing int compareHands(hand handA, hand handB){\n\n");

//                card cards[10];

//                printf("creating two similar hands\n");
//                for (i = 0; i < 5; i++){
//                    cards[i].value = i;
//                    hand1.cards.push_back(cards[i]);
//                }
//                hand1.handValue = 1;

//                for (i = 5; i < 10; i++){
//                    cards[i].val = 9-i;
//                    hand2.cards.push_back(cards[i]);
//                }
//                hand2.handValue = 1;

//                printf("comparing\n");
//                if (compareHands(hand1, hand2) == 1){
//                    printf("the func. worked\n");
//                }
//                else {
//                    printf("error\n");
//                }
//                for (i = 0;i < 10; i++){
//                        printf("%d: %d\t", i, cards[i].val);
//                }
//                printf("\n");

//                printf("creating two defferent hands\n");
//                for (i = 0; i < 5; i++){
//                    cards[i].val = i+1;
//                    hand1.cards.push_back(cards[i]);
//                }
//                hand1.handValue = 1;

//                for (i = 5; i < 10; i++){
//                    cards[i].val = i+1;
//                    hand2.cards.push_back(cards[i]);
//                }
//                hand2.handValue = 2;

//                printf("comparing\n");
//                if (compareHands(hand1, hand2) == 0){
//                    printf("the func. worked\n");
//                }
//                else {
//                    printf("error\n");
//                }
//                for (i = 0;i < 10; i++){
//                        printf("%d: %d\t", i, cards[i].val);
//                }
//                printf("\n");


//                printf("end of int compareHands(hand handA, hand handB){ test\n\n\n");




//        //tests for int checkDiffTables(gameTable *TableA, gameTable *tableB){
//        printf("testing int checkDiffTables(gameTable *TableA, gameTable *tableB){\n\n");
//        gameTable table1, table2;

//                printf("setting the tables to diff. num of cards\n");
//                table1.numCards = 0;
//                table2.numCards = 4;
//                printf("checking\n");
//                if (checkDiffTables(&table1, &table2) == 1){
//                    printf("the func. worked\n");
//                }
//                else printf("error\n");
//                printf("setting the tables to diff num of hands\n");
//                table1.numCards = 4;
//                table1.players.push_back(hand1);
//                table1.players.push_back(hand2);
//                table2.players.push_back(hand1);
//                printf("checking\n");
//                if (checkDiffTables(&table1, &table2) == 1){
//                    printf("the func. worked\n");
//                }
//                else printf("error\n");
//                printf("setting the tables to same hands exactly, same #cards\n");
//                table2.players.push_back(hand2);
//                printf("checking\n");
//                if (checkDiffTables(&table1, &table2) == 0){
//                    printf("the func. worked\n");
//                }
//                else printf("error\n");
//                printf("setting the hands to same #hands, #cards, diff hands");
//                table1.players.at(1).cards.at(0).val = 13;
//                printf("checking\n");
//                if (checkDiffTables(&table1, &table2) == 1){
//                    printf("the func. worked\n");
//                }
//                else printf("error\n");




//        printf("end of int checkDiffTables(gameTable *TableA, gameTable *tableB){ test\n\n\n");



//        //tests for void getTableInventory(gameTable *table, char inv[]){{
//        printf("testing void getTableInventory(gameTable *table, char inv[]){\n\n");

//        char inv[13] = {0};
//        //zero everything
//        for (i = 0; i < 13; i++){
//                printf("%d:%d\t", i, inv[i]);
//                cards[i].val = 0;
//        }
//        printf("\n");
//        table1.players.clear();
//        hand1.cards.clear();
//        hand2.cards.clear();
//        //populate
//        for (i = 0; i < 5; i++){
//                cards[i].val = i+1;
//                hand1.cards.push_back(cards[i]);
//        }
//        for (i = 5; i < 10; i++){
//                cards[i].val = 10-i;
//                hand2.cards.push_back(cards[i]);
//        }
//        table1.players.push_back(hand1);
//        table1.players.push_back(hand2);


//        getTableInventory(&table1, inv);
//        for (i = 0; i < 13; i++){
//                printf("%d:%d\t", i, inv[i]);
//        }
//        printf("\n");

//        printf("end of void getTableInventory(gameTable *table, char inv[]){ test\n\n\n");



//         //tests for void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){
//                printf("testing void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){\n");
//                cleanTable(&table1);
//                cleanTable(&table2);
//                hand hands1[4] = {0};
//                hand hands2[4] = {0};
//                card cards2[20] = {0};

//                cards2[0].val = 2;
//                cards2[1].val = 1;
//                cards2[2].val = 13;
//                cards2[3].val = 11;
//                cards2[4].val = 8;
//                cards2[5].val = 7;
//                cards2[6].val = 6;
//                cards2[7].val = 6;

//                cards2[8].val = 2;
//                cards2[9].val = 1;
//                cards2[10].val = 13;
//                cards2[11].val = 11;
//                cards2[12].val = 8;
//                cards2[13].val = 7;
//                cards2[14].val = 6;
//                cards2[15].val = 6;
//                cards2[16].val = 13;
//                cards2[17].val = 6;
//                cards2[18].val = 3;
//                cards2[19].val = 6;

//                printf("finished init. cards\n");
//                // create two hands
//                for (i = 0; i < 4; i++){
//                    hands1[i].cards.push_back(cards2[2*i]);
//                    hands1[i].cards.push_back(cards2[2*i+1]);
//                    hands2[i].cards.push_back(cards2[2*i + 8]);
//                    hands2[i].cards.push_back(cards2[2*i+1 + 8]);
//                }
//                hands2[2].cards.push_back(cards2[16]);
//                hands2[3].cards.push_back(cards2[17]);
//                hands2[3].cards.push_back(cards2[18]);
//                hands2[3].cards.push_back(cards2[19]);

//                printf("created hands.\n");fflush(stdout);
//                for (i = 0; i < 4; i++){
//                    table1.players.push_back(hands1[i]);
//                    table2.players.push_back(hands2[i]);
//                }

//                printf("getTableDiff.\n");fflush(stdout);
//                int diff[13] = {0};
//                getDiffTables(&table2, &table1, diff, 13);

//                for (i = 0; i < 13; i++){
//                        printf("%d:%d\t", i, diff[i]);
//                }
//                printf("\n");

//                printf("end of void getDiffTables(gameTable *tableA, gameTable *tableB, int diff[], int size){ test\n\n\n");


//        //tests for int compareHands(hand handA, hand handB){
//        //printf("testing int compareHands(hand handA, hand handB){\n");
//        //
//        //printf("end of int compareHands(hand handA, hand handB){ test\n\n\n");
//        return 1;

//}
