/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * GameLibh.cpp :     a library of types and methods that makes the abstraction of a black-jack game.
 *                    defines types like card, hand, game and functions on these types
 *                    in addition, the types hold extra info. for the use of the computer-vision libs.
 *
 *
 */

#include "GameLib.hpp"
#include <math.h>
#include <stdio.h>

// sets the table to zero cards and no players
void cleanTable(gameTable *table){
    table->numCards = 0;
    table->players.clear();
    return;
}

// cleans the history in the game state
void cleanHistory(gameState *state){

    // set the array to 0
    for (uint i = 0; i < 13; i++){
        state->history[i] = 0;
    }

    return;
}

// initializer for the game-state
void initGameState(GameState *state, int numDeck){
    if (state == NULL) return;

    state->status = NEW_GAME;

    // zero the history count
    cleanHistory(state);

    state->deckCount = 0;
    state->numDecks = numDeck;
    cleanTable(&(state->table));

    state->gameCount = 0;
    state->winCount = 0;

    return;
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
    case 'T': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
    default: return -1;//just in case
    }


}


// gets a hand and an array of size 13 and returns in the array how many cards from wach value there are in the hand
void getHandInventory(hand h, char inv[]){
    char val;

    for (uint j = 0; j < h.cards.size(); j++){
        val = getNumVal(h.cards.at(j).value);
        if (val > 13 || val < 1) {
            continue;
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
    uint i;

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



// update the game state's history with the inventory
void updateHistory(gameState *state, char inv[]){

    for (uint i = 0; i < 13; i++){
        state->history[i] += inv[i];
    }

    return;
}


/* return the value of the hand or blackjack
 */
int getHandVal(hand h){
    int sum = 0;
    int sumA = 0;
    int val = 0;
    int ACount = 0;
    if (h.cards.size() == 2){
        if (((h.cards.at(0).value == 'A') && ((h.cards.at(1).value == 'T')
                                              || (h.cards.at(1).value == 'J')
                                              || (h.cards.at(1).value == 'Q')
                                              || (h.cards.at(1).value == 'K')))
                ||
                ((h.cards.at(1).value == 'A') && ((h.cards.at(0).value == 'T')
                                                  || (h.cards.at(0).value == 'J')
                                                  || (h.cards.at(0).value == 'Q')
                                                  || (h.cards.at(0).value == 'K')))
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

    if (ACount == 0){
        return sum;
    }
    else{   //jCount > 0
        sumA = (sum + 11 + (ACount-1));
        if (sumA <= 21) return sumA;
        else {
            return sumA = sum + ACount;
        }
    }
}

// returns the count by the ZEN count system
int countCards(char inv[]){
    int count = 0;

    count += (-1)*inv[0];
    count += (1)*inv[1];
    count += (1)*inv[2];
    count += (2)*inv[3];
    count += (2)*inv[4];
    count += (2)*inv[5];
    count += (1)*inv[6];
    count += (0)*inv[7];
    count += (0)*inv[8];
    count += (-2)*inv[9];
    count += (-2)*inv[10];
    count += (-2)*inv[11];
    count += (-2)*inv[12];

    return count;
}


// calculates true-count from the running count
// true count :=  running count / decks left in play
int calcTrueCount(gameState state){
    int histSize = 0;

    for (int i = 0; i < 13; i++){
        histSize += state.history[i];
    }
    double num = (state.numDecks)*NUM_CARDS_IN_DECK - histSize;
    double q = num / NUM_CARDS_IN_DECK;

    int decksLeft = (int)(ceil(q));

    int trueCount = state.deckCount / decksLeft;

    return (trueCount * state.bettingUnit);
}

// creates a string msg to display on screen
void tableToString(gameState *state, string *str, char inv[]){
    int hVal, dVal;
    uint i,j;
    char endFlag = 0;
    gameTable *table = &(state->table);
    hand dealer = table->players.at(0);

    std::ostringstream os;


    if (state->status == NEW_GAME){
        os << "NEW_GAME\n";
    }
    else if (state->status == PLAYER_TURN){
        os << "PLAYER_TURN\n";
    }
    else if (state->status == DEALER_TURN){
        os << "DEALER_TURN\n";
    }
    else if (state->status == END_GAME){
        os << "END_GAME\n";
        state->gameCount++;
    }
    os << state->gameCount << " games played, " << state->winCount << " games won.\n";

    os << "The Count is: " << calcTrueCount(*state) << "\n\n";

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
        os << "Dealer has BlackJack\n\n";
    }
    else if (dVal > 21) {  //if the dealer bust
        os << "Dealer Bust" << "\n\n";
    }
    else if (dVal == 21){
        os << "Dealer has 21" << "\n\n";
    }
    else {
        os << "Dealer has " << dVal << "\n\n";
    }

    if (dVal >= 17){
        endFlag = 1;
    }
    else {
        endFlag = 0;
    }

    for (i = 1; i < table->players.size(); i++){
        //print hand

        hand *handPtr = &table->players.at(i);
        if (handPtr->cards.size() < 2) continue;

        os << "Player " << i << ": ";

        for (j = 0; j < handPtr->cards.size(); j++){
            os << handPtr->cards.at(j).value << " ";
        }
        os << "\n";

        //print msg
        hVal = getHandVal(table->players.at(i));
        if (hVal == BLACK_JACK){
            os << "Player" << i << " has BlackJack\n";
        }
        else if (hVal > 21) {  //if the player is bust
            os << "Player " << i << " Bust" << "\n";
        }
        else if (hVal <= 21){
            os << "Player" << i << " has " << hVal << "\n";
        }

        if (state->status == PLAYER_TURN && (hVal <= 21)){  //print advice if the players are still playing
            os << state->stratFunc(*handPtr, dealer) << "\n";
            float hit, stand;
            calc_hit_chance(hVal,state->history, inv, state->numDecks,state->table.players.at(0).cards.at(0).value,&stand, &hit);
            os << "Chances on HIT: " << floor(hit*100) << "%\n";
            os << "Chances on STAND: " << floor(stand*100) << "%\n";
        }


        //end game messages
        if (state->status == END_GAME){
            if (hVal == dVal) {
                os << "PUSH!\n";
            }
            else if ( ((hVal > dVal) && (hVal <=21)) || (((dVal > 21) && (dVal != BLACK_JACK)) && (hVal <= 21)) || (hVal == BLACK_JACK)){
                os << "WIN!\n";
                state->winCount++;
            }
            else {
                os << "LOSE!\n";
            }
        }
        os << "\n";
    }
    *str = os.str();

    return;
}

void historyToString(gameState state, string *output){
    std::ostringstream os;

    os << "Cards Seen: \n";

    for (uint i = 0; i < 13; i++){
        switch(i){
        case 0: {
            os << " A";
            break;
        }
        case 10: {
            os << " J";
            break;
        }
        case 11: {
            os << " Q";
            break;
        }
        case 12: {
            os << " K";
            break;
        }
        case 9: {
            os << i+1;
            break;
        }
        default: {
            os << " " << i+1;
            break;
        }
        }
        os << "\t";
        os << state.history[i];
        os << "\n";
    }
    *output = os.str();

    return;
}

float calc_D_chance(char Draw, int Val_to_beat,short hand_As,short hand_2s,short hand_3s,short hand_4s,short hand_5s,
                    short hand_6s,short hand_7s,short hand_8s,short hand_9s,short hand_10s,
                    short hand_Js,short hand_Qs,short hand_Ks,
                    short rem_As,short rem_2s,short rem_3s,short rem_4s,short rem_5s,
                    short rem_6s,short rem_7s,short rem_8s,short rem_9s,short rem_10s,
                    short rem_Js,short rem_Qs,short rem_Ks,int rem_sum){
    // recursion stoppers
    if ((Draw=='A') && (rem_As < 1)) return 0; //the chance of the dealer to win is 0 cause he tries to
    if ((Draw=='2') && (rem_2s < 1)) return 0; //draw a card the the deck has run out of
    if ((Draw=='3') && (rem_3s < 1)) return 0;
    if ((Draw=='4') && (rem_4s < 1)) return 0;
    if ((Draw=='5') && (rem_5s < 1)) return 0;
    if ((Draw=='6') && (rem_6s < 1)) return 0;
    if ((Draw=='7') && (rem_7s < 1)) return 0;
    if ((Draw=='8') && (rem_8s < 1)) return 0;
    if ((Draw=='9') && (rem_9s < 1)) return 0;
    if ((Draw=='T') && (rem_10s < 1)) return 0;
    if ((Draw=='J') && (rem_Js < 1)) return 0;
    if ((Draw=='Q') && (rem_Qs < 1)) return 0;
    if ((Draw=='K') && (rem_Ks < 1)) return 0;

    //draw is possible

    if (Draw == 'A'){
        hand_As++;
        rem_As--;
    } else if (Draw == '2'){
        hand_2s++;
        rem_2s--;
    } else if (Draw == '3'){
        hand_3s++;
        rem_3s--;
    } else if (Draw == '4'){
        hand_4s++;
        rem_4s--;
    } else if (Draw == '5'){
        hand_5s++;
        rem_5s--;
    } else if (Draw == '6'){
        hand_6s++;
        rem_6s--;
    } else if (Draw == '7'){
        hand_7s++;
        rem_7s--;
    } else if (Draw == '8'){
        hand_8s++;
        rem_8s--;
    } else if (Draw == '9'){
        hand_9s++;
        rem_9s--;
    } else if (Draw == 'T'){
        hand_10s++;
        rem_10s--;
    } else if (Draw == 'J'){
        hand_Js++;
        rem_Js--;
    } else if (Draw == 'Q'){
        hand_Qs++;
        rem_Qs--;
    } else if (Draw == 'K'){
        hand_Ks++;
        rem_Ks--;
    }

    rem_sum--;

    int dealer_hand_val = 2*hand_2s +
            3*hand_3s +
            4*hand_4s +
            5*hand_5s +
            6*hand_6s +
            7*hand_7s +
            8*hand_8s +
            9*hand_9s +
            10*hand_10s +
            10*hand_Js +
            10*hand_Qs +
            10*hand_Ks;
    // 11*hand_As; //debug - what if A is 1 ?

    if (hand_As != 0){
        int sumA = (dealer_hand_val + 11 + (hand_As-1));
        if (sumA <= 21)
            dealer_hand_val = sumA;
        else
            dealer_hand_val = dealer_hand_val + hand_As;
    }

    if (Val_to_beat > 21) return 1; // the player is busted
    if (Val_to_beat == 21) return 0; // the player won
    if (dealer_hand_val > 21) return 0; //dealer busted
    if (dealer_hand_val > Val_to_beat) return 1; //&& <=21 - this was checked here ^
    if (dealer_hand_val >= 17) return 0; //dealerstands
    if (rem_sum <= 0) return 0; //the deck is empty - div by 0 protection

    float ret_val= (
                (((float)rem_As / (float) rem_sum) * calc_D_chance('A',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_2s / (float) rem_sum) * calc_D_chance('2',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_3s / (float) rem_sum) * calc_D_chance('3',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_4s / (float) rem_sum) * calc_D_chance('4',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_5s / (float) rem_sum) * calc_D_chance('5',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_6s / (float) rem_sum) * calc_D_chance('6',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_7s / (float) rem_sum) * calc_D_chance('7',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_8s / (float) rem_sum) * calc_D_chance('8',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_9s / (float) rem_sum) * calc_D_chance('9',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_10s / (float) rem_sum) * calc_D_chance('T',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                    hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                    rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                    rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_Js / (float) rem_sum) * calc_D_chance('J',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_Qs / (float) rem_sum) * calc_D_chance('Q',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )  +
                (((float)rem_Ks / (float) rem_sum) * calc_D_chance('K',Val_to_beat,hand_As,hand_2s,hand_3s,hand_4s,hand_5s,
                                                                   hand_6s,hand_7s,hand_8s,hand_9s,hand_10s,hand_Js,hand_Qs,hand_Ks,
                                                                   rem_As,rem_2s,rem_3s,rem_4s,rem_5s,rem_6s,rem_7s,rem_8s,rem_9s,rem_10s,
                                                                   rem_Js,rem_Qs,rem_Ks,rem_sum)
                 )

                );
    return ret_val;

}

//history - including the current tables small history
int calc_P_chance(int hand_val,char history[13],char DealerCard, float* chance_if_stand, float* chance_if_hit){
    short my_history[13];
    int sum_rem = 0;
    for (int i=0; i<13 ; i++){
        my_history[i] = (int) history[i];
        sum_rem = sum_rem + my_history[i];
    }
    *chance_if_stand = 0;
    *chance_if_hit = 0;

    if (DealerCard == 'N' ) return 0;

    if (DealerCard == 'A' ) my_history[0]++;
    if (DealerCard == '2' ) my_history[1]++;
    if (DealerCard == '3' ) my_history[2]++;
    if (DealerCard == '4' ) my_history[3]++;
    if (DealerCard == '5' ) my_history[4]++;
    if (DealerCard == '6' ) my_history[5]++;
    if (DealerCard == '7' ) my_history[6]++;
    if (DealerCard == '8' ) my_history[7]++;
    if (DealerCard == '9' ) my_history[8]++;
    if (DealerCard == 'T' ) my_history[9]++;
    if (DealerCard == 'J' ) my_history[10]++;
    if (DealerCard == 'Q' ) my_history[11]++;
    if (DealerCard == 'K' ) my_history[12]++;


    float d_curr_chance = calc_D_chance(DealerCard, hand_val,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                        my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                        my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                        my_history[10],my_history[11],my_history[12],sum_rem-1); //-1 because dealers card
    int hand_val_for_A = 0;
    int sumA = (hand_val + 11);
    if (sumA <= 21)
        hand_val_for_A = sumA;
    else
        hand_val_for_A = hand_val + 1;


    float d_chance_if_hit = 1;
    if (sum_rem!=0) //if there is another card to take
        d_chance_if_hit = ( // what if A is == 1 ?
                            (((float)history[0] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val_for_A,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0]-1,my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[1] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+2,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1]-1,my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[2] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+3,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2]-1,my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[3] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+4,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3]-1,my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[4] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+5,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3],my_history[4]-1,
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[5] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+6,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5]-1,my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[6] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+7,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6]-1,my_history[7],my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[7] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+8,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7]-1,my_history[8],my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[8] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+9,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8]-1,my_history[9],
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[9] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+10,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                   my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                   my_history[5],my_history[6],my_history[7],my_history[8],my_history[9]-1,
                                                                                   my_history[10],my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[10] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+10,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                    my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                    my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                    my_history[10]-1,my_history[11],my_history[12],sum_rem-2)
                             )  +

                            (((float)history[11] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+10,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                    my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                    my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                    my_history[10],my_history[11]-1,my_history[12],sum_rem-2)
                             )  +

                            (((float)history[12] / (float) sum_rem) * calc_D_chance(DealerCard,hand_val+10,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                                                    my_history[0],my_history[1],my_history[2],my_history[3],my_history[4],
                                                                                    my_history[5],my_history[6],my_history[7],my_history[8],my_history[9],
                                                                                    my_history[10],my_history[11],my_history[12]-1,sum_rem-2)
                             )

                            );

    *chance_if_stand = 1-d_curr_chance;
    *chance_if_hit = 1-d_chance_if_hit;

    return 1;


}

void calc_hit_chance(int hand_val,int seen_history[13],char seen_history_curr[13],int num_decks,char DealerCard, float* chance_if_stand, float* chance_if_hit){

    char remaining_cards[13];

    for (int i=0;  i < 13 ; i++){
        remaining_cards[i]= 4*num_decks - seen_history[i] - seen_history_curr[i];
        if (remaining_cards[i] < 0){
            *chance_if_stand =0;
            * chance_if_hit = 0;
            return;
        }

    }

    calc_P_chance(hand_val,remaining_cards,DealerCard,chance_if_stand,chance_if_hit);
    printf("hit: %f\tstand: %f", *chance_if_hit, *chance_if_stand);fflush(stdout);
    if (*chance_if_stand < 0) *chance_if_stand = 0;
    if (*chance_if_hit < 0) *chance_if_hit = 0;
    return;
}


