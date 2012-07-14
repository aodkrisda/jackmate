/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * ImageBuffer.hpp :    a library that implements the different strategy tables
 *                      which give back strings of advice
 *
 *
 */

#include "GameLib.hpp"
#include "tablesLib.hpp"


using namespace std;
using namespace cv;

//############  ONE DECK    ##############################
std::string getAdvice1Deck(hand player, hand dealer){

    if (player.cards.size() == 2){
        if (player.cards.at(0).value == 'A' && player.cards.at(1).value == 'A'){
            if (dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT.";
            }
            else {
                return "Suggested play: SPLIT.";
            }
        }

        else if (( getNumVal(player.cards.at(0).value) >= 10 ) &&
                 ( getNumVal(player.cards.at(1).value) >= 10 )){
            return "Suggested play: STAND";
        }

        else if (player.cards.at(0).value == '9' && player.cards.at(1).value == '9'){
            if (dealer.cards.at(0).value == '7'
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
            if (dealer.cards.at(0).value == 'A'
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

        else  if (player.cards.at(0).value == '7' && player.cards.at(1).value == '7'){
            if (dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else if (dealer.cards.at(0).value == 'T'
                     || dealer.cards.at(0).value == 'J'
                     || dealer.cards.at(0).value == 'Q'
                     || dealer.cards.at(0).value == 'K'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '6' && player.cards.at(1).value == '6'){
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

        else  if (player.cards.at(0).value == '5' && player.cards.at(1).value == '5'){
            if (dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            return "Suggested play: DOUBLE DOWN";
        }

        else if (player.cards.at(0).value == '4' && player.cards.at(1).value == '4'){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '3' && player.cards.at(1).value == '3'){
            if (dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '2' && player.cards.at(1).value == '2'){
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

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '9')) ||
                 ((player.cards.at(0).value == '9') && (player.cards.at(1).value == 'A'))){
            return "Suggested play: STAND";
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '8')) ||
                 ((player.cards.at(0).value == '8') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: STAND";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '7')) ||
                 ((player.cards.at(0).value == '7') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else if (dealer.cards.at(0).value == '2'
                     || dealer.cards.at(0).value == '7'
                     || dealer.cards.at(0).value == '8'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '6')) ||
                 ((player.cards.at(0).value == '6') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
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
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '4')) ||
                 ((player.cards.at(0).value == '4') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '3')) ||
                 ((player.cards.at(0).value == '3') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '2')) ||
                 ((player.cards.at(0).value == '2') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }
    }// end of "if player has 2 cards"


    int val = getHandVal(player);

    if (val == 7){
        return "Suggested play: HIT";
    }

    else if (val == 8){
        if (dealer.cards.at(0).value == '5'
                || dealer.cards.at(0).value == '6'){
            return "Suggested play: DOUBLE DOWN";

        }
        else {
            return "Suggested play: HIT";
        }
    }

    else if (val == 9){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: DOUBLE DOWN";
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

    else if (val == 12){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 13){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 14){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 15){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 16){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val >= 17){
        return "Suggested play: STAND";
    }
    else {
        return "Suggested play: HIT";
    }


    return "error"; //just in case
}
//############ END OF ONE DECK    ##############################
//############  TWO DECKS    ##############################
std::string getAdvice2Deck(hand player, hand dealer){

    if (player.cards.size() == 2){
        if (player.cards.at(0).value == 'A' && player.cards.at(1).value == 'A'){
            if (dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT.";
            }
            else {
                return "Suggested play: SPLIT.";
            }
        }

        else if (( getNumVal(player.cards.at(0).value) >= 10 ) &&
                 ( getNumVal(player.cards.at(1).value) >= 10 )){
            return "Suggested play: STAND";
        }

        else if (player.cards.at(0).value == '9' && player.cards.at(1).value == '9'){
            if (dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else  if (player.cards.at(0).value == '8' && player.cards.at(1).value == '8'){
            if (dealer.cards.at(0).value == 'A'
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

        else  if (player.cards.at(0).value == '7' && player.cards.at(1).value == '7'){
            if (dealer.cards.at(0).value == '9'
                    ||dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '6' && player.cards.at(1).value == '6'){
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

        else  if (player.cards.at(0).value == '5' && player.cards.at(1).value == '5'){
            if (dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            return "Suggested play: DOUBLE DOWN";
        }

        else if (player.cards.at(0).value == '4' && player.cards.at(1).value == '4'){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: SPLIT";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (player.cards.at(0).value == '3' && player.cards.at(1).value == '3'){
            if (dealer.cards.at(0).value == '8'
                    ||dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '2' && player.cards.at(1).value == '2'){
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

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '9')) ||
                 ((player.cards.at(0).value == '9') && (player.cards.at(1).value == 'A'))){
            return "Suggested play: STAND";
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '8')) ||
                 ((player.cards.at(0).value == '8') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: STAND";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '7')) ||
                 ((player.cards.at(0).value == '7') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else if (dealer.cards.at(0).value == '7'
                     || dealer.cards.at(0).value == '8'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
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
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '4')) ||
                 ((player.cards.at(0).value == '4') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '3')) ||
                 ((player.cards.at(0).value == '3') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '2')) ||
                 ((player.cards.at(0).value == '2') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '2'
                    || dealer.cards.at(0).value == '3'
                    || dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
            }
        }
    }// end of "if player has 2 cards"


    int val = getHandVal(player);

    if (val == 7){
        return "Suggested play: HIT";
    }

    else if (val == 8){
        return "Suggested play: HIT";
    }

    else if (val == 9){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: DOUBLE DOWN";
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

    else if (val == 12){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 13){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 14){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 15){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 16){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val >= 17){
        return "Suggested play: STAND";
    }
    else {
        return "Suggested play: HIT";
    }


    return "error"; //just in case
}
//############ END OF TWO DECKS    ##############################


//############  SIX DECKS    ##############################
std::string getAdvice6Deck(hand player, hand dealer){

    if (player.cards.size() == 2){
        if (player.cards.at(0).value == 'A' && player.cards.at(1).value == 'A'){
            if (dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT.";
            }
            else {
                return "Suggested play: SPLIT.";
            }
        }

        else if (( getNumVal(player.cards.at(0).value) >= 10 ) &&
                 ( getNumVal(player.cards.at(1).value) >= 10 )){
            return "Suggested play: STAND";
        }

        else if (player.cards.at(0).value == '9' && player.cards.at(1).value == '9'){
            if (dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else  if (player.cards.at(0).value == '8' && player.cards.at(1).value == '8'){
            if (dealer.cards.at(0).value == 'A'
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

        else  if (player.cards.at(0).value == '7' && player.cards.at(1).value == '7'){
            if (dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    ||dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '6' && player.cards.at(1).value == '6'){
            if (dealer.cards.at(0).value == '7'
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

        else  if (player.cards.at(0).value == '5' && player.cards.at(1).value == '5'){
            if (dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            return "Suggested play: DOUBLE DOWN";
        }

        else if (player.cards.at(0).value == '4' && player.cards.at(1).value == '4'){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: SPLIT";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (player.cards.at(0).value == '3' && player.cards.at(1).value == '3'){
            if (dealer.cards.at(0).value == '8'
                    ||dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '2' && player.cards.at(1).value == '2'){
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

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '9')) ||
                 ((player.cards.at(0).value == '9') && (player.cards.at(1).value == 'A'))){
            return "Suggested play: STAND";
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '8')) ||
                 ((player.cards.at(0).value == '8') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: STAND";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '7')) ||
                 ((player.cards.at(0).value == '7') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else if (dealer.cards.at(0).value == '7'
                     || dealer.cards.at(0).value == '8'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
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
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '4')) ||
                 ((player.cards.at(0).value == '4') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '3')) ||
                 ((player.cards.at(0).value == '3') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '2')) ||
                 ((player.cards.at(0).value == '2') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }
    }// end of "if player has 2 cards"


    int val = getHandVal(player);

    if (val == 7){
        return "Suggested play: HIT";
    }

    else if (val == 8){
        return "Suggested play: HIT";
    }

    else if (val == 9){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: DOUBLE DOWN";
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

    else if (val == 12){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 13){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 14){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 15){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 16){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val >= 17){
        return "Suggested play: STAND";
    }
    else {
        return "Suggested play: HIT";
    }


    return "error"; //just in case
}
//############ END OF SIX DECKS    ##############################


//############  EIGHT DECKS    ##############################
std::string getAdvice8Deck(hand player, hand dealer){

    if (player.cards.size() == 2){
        if (player.cards.at(0).value == 'A' && player.cards.at(1).value == 'A'){
            if (dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT.";
            }
            else {
                return "Suggested play: SPLIT.";
            }
        }

        else if (( getNumVal(player.cards.at(0).value) >= 10 ) &&
                 ( getNumVal(player.cards.at(1).value) >= 10 )){
            return "Suggested play: STAND";
        }

        else if (player.cards.at(0).value == '9' && player.cards.at(1).value == '9'){
            if (dealer.cards.at(0).value == '7'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else  if (player.cards.at(0).value == '8' && player.cards.at(1).value == '8'){
            if (dealer.cards.at(0).value == 'A'
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

        else  if (player.cards.at(0).value == '7' && player.cards.at(1).value == '7'){
            if (dealer.cards.at(0).value == '8'
                    || dealer.cards.at(0).value == '9'
                    ||dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'
                    ){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '6' && player.cards.at(1).value == '6'){
            if (dealer.cards.at(0).value == '7'
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

        else  if (player.cards.at(0).value == '5' && player.cards.at(1).value == '5'){
            if (dealer.cards.at(0).value == 'A'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'){
                return "Suggested play: HIT";
            }
            return "Suggested play: DOUBLE DOWN";
        }

        else if (player.cards.at(0).value == '4' && player.cards.at(1).value == '4'){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'){
                return "Suggested play: SPLIT";
            }
            else {
                return "Suggested play: HIT";
            }
        }

        else if (player.cards.at(0).value == '3' && player.cards.at(1).value == '3'){
            if (dealer.cards.at(0).value == '8'
                    ||dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else {
                return "Suggested play: SPLIT";
            }
        }

        else if (player.cards.at(0).value == '2' && player.cards.at(1).value == '2'){
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

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '9')) ||
                 ((player.cards.at(0).value == '9') && (player.cards.at(1).value == 'A'))){
            return "Suggested play: STAND";
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '8')) ||
                 ((player.cards.at(0).value == '8') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '6'){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: STAND";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '7')) ||
                 ((player.cards.at(0).value == '7') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '9'
                    || dealer.cards.at(0).value == 'T'
                    || dealer.cards.at(0).value == 'J'
                    || dealer.cards.at(0).value == 'Q'
                    || dealer.cards.at(0).value == 'K'
                    || dealer.cards.at(0).value == 'A'){
                return "Suggested play: HIT";
            }
            else if (dealer.cards.at(0).value == '7'
                     || dealer.cards.at(0).value == '8'){
                return "Suggested play: STAND";
            }
            else {
                return "Suggested play: DOUBLE DOWN";
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
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '4')) ||
                 ((player.cards.at(0).value == '4') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '4'
                    || dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: DOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '3')) ||
                 ((player.cards.at(0).value == '3') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }

        else if (((player.cards.at(0).value == 'A') && (player.cards.at(1).value == '2')) ||
                 ((player.cards.at(0).value == '2') && (player.cards.at(1).value == 'A'))){
            if (dealer.cards.at(0).value == '5'
                    || dealer.cards.at(0).value == '6'
                    ){
                return "Suggested play: HDOUBLE DOWN";
            }
            else {
                return "Suggested play: Hit";
            }
        }
    }// end of "if player has 2 cards"


    int val = getHandVal(player);

    if (val == 7){
        return "Suggested play: HIT";
    }

    else if (val == 8){
        return "Suggested play: HIT";
    }

    else if (val == 9){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: DOUBLE DOWN";
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

    else if (val == 12){
        if (dealer.cards.at(0).value == '2'
                || dealer.cards.at(0).value == '3'
                || dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 13){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 14){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 15){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val == 16){
        if (dealer.cards.at(0).value == '7'
                || dealer.cards.at(0).value == '8'
                || dealer.cards.at(0).value == '9'
                || dealer.cards.at(0).value == 'T'
                || dealer.cards.at(0).value == 'J'
                || dealer.cards.at(0).value == 'Q'
                || dealer.cards.at(0).value == 'K'
                || dealer.cards.at(0).value == 'A'
                ){
            return "Suggested play: HIT";
        }
        else {
            return "Suggested play: STAND";
        }
    }

    else if (val >= 17){
        return "Suggested play: STAND";
    }
    else {
        return "Suggested play: HIT";
    }


    return "error"; //just in case
}
//############ END OF EIGHT DECKS    ##############################
