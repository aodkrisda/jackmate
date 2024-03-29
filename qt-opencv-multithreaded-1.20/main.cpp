/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* main.cpp                                                             */
/*                                                                      */
/* Nick D'Ademo <nickdademo@gmail.com>                                  */
/*                                                                      */
/* Copyright (c) 2011 Nick D'Ademo                                      */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a co//tests for void getTableInventory(gameTable *table, char inv[]){{
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

        printf("end of void getTableInventory(gameTable *table, char inv[]){ test\n\n\n");py of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#include "MainWindow.h"

// Qt header files
#include <QtGui/QApplication>

#define X_INITIAL 0
#define Y_INITIAL 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(QUOTE(APP_VERSION));
    MainWindow w;
    w.show();
    // Set the initial screen position of the main window
    w.setGeometry(X_INITIAL, Y_INITIAL, w.width(), w.height());
    return a.exec();
} // main()
