/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * ImageBuffer.hpp :    a library that implements the different strategy tables
 *                      which give back strings of advice
 *
 *
 */

#ifndef TABLESLIB_H
#define TABLESLIB_H
#include "GameLib.hpp"

std::string getAdvice1Deck(struct Hand player, struct Hand dealer);

std::string getAdvice2Deck(struct Hand player, struct Hand dealer);

std::string getAdvice6Deck(struct Hand player, struct Hand dealer);

std::string getAdvice8Deck(struct Hand player, struct Hand dealer);


#endif // TABLESLIB_H
