/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * ProcessingThread.hpp :        a thread class that works with the capture thread through the image buffer
 *                               it gets a feed of frames and makes all the process needed to
 *                               show information on the screen - cv, text, probability calculations etc.
 *
 *
 * GUI is mainly based on qt-opencv-multithreaded (see below credits)
 */

// CREDITS
/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* ProcessingThread.cpp                                                 */
/*                                                                      */
/* Nick D'Ademo <nickdademo@gmail.com>                                  */
/*                                                                      */
/* Copyright (c) 2011 Nick D'Ademo                                      */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
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

#include "ImageBuffer.h"
#include "ProcessingThread.h"
#include "MatToQImage.h"

#include "GameLib.hpp"
#include "tablesLib.hpp"
#include "card_detection.h"

#include <stdlib.h>
#include <iostream>
#include <unistd.h>

// Qt header files
#include <QDebug>
// OpenCV header files
#include <opencv/cv.h>
#include <opencv/highgui.h>
// Configuration header file
#include "Config.h"



// Constructor
ProcessingThread::ProcessingThread(ImageBuffer *imageBuffer, int inputSourceWidth, int inputSourceHeight)
    : QThread(), imageBuffer(imageBuffer), inputSourceWidth(inputSourceWidth),
      inputSourceHeight(inputSourceHeight)
{
    // Create images
    currentFrameCopy.create(Size(inputSourceWidth,inputSourceHeight),CV_8UC3);
    currentFrameCopyGrayscale.create(Size(inputSourceWidth,inputSourceHeight),CV_8UC1);
    // Initialize variables
    stopped=false;
    sampleNo=0;
    fpsSum=0;
    avgFPS=0;
    fps.clear();
    // Initialize currentROI variable
    currentROI=Rect(0,0,inputSourceWidth,inputSourceHeight);
    // Store original ROI
    originalROI=currentROI;

    //pre-process surf params.
    preLoadGlyphs(this->Glyphs ,this->keypoints);

    //game-settings init.
    initGameState(&GameState, _GameLib_NUM_DECKS);
    this->pcounter = 0;

    cleanTable(&newTable);
    SetBlackFlag = 0;

    blackVal = 300000;


} // ProcessingThread constructor

// Destructor
ProcessingThread::~ProcessingThread()
{
} // ProcessingThread destructor

// the function the thread will run when it is called
void ProcessingThread::run()
{
    while(1)
    {
        /////////////////////////////////
        // Stop thread if stopped=TRUE //
        /////////////////////////////////
        stoppedMutex.lock();
        if (stopped)
        {
            stopped=false;
            stoppedMutex.unlock();
            break;
        }
        stoppedMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        // Save processing time
        processingTime=t.elapsed();
        // Start timer (used to calculate processing rate)
        t.start();
        // Get frame from queue
        Mat currentFrame=imageBuffer->getFrame();
        // Make copy of current frame (processing will be performed on this copy)
        currentFrame.copyTo(currentFrameCopy);
        // Set ROI of currentFrameCopy
        currentFrameCopy.locateROI(frameSize,framePoint);
        currentFrameCopy.adjustROI(-currentROI.y,-(frameSize.height-currentROI.height-currentROI.y),
                                   -currentROI.x,-(frameSize.width-currentROI.width-currentROI.x));

        updateMembersMutex.lock();

        updateMembersMutex.unlock();

        // Update statistics
        updateFPS(processingTime);
        currentSizeOfBuffer=imageBuffer->getSizeOfImageBuffer();

        if (GameState.status == NEW_GAME) writeCount();

        if (decideToProcess()){
            writeHistory();

            // set the black level
            if (SetBlackFlag == 1){
                blackVal = setBlackCalib(currentFrame);
                SetBlackFlag = 0;
            }

            process(&currentFrame);
        }
        draw_on_image(GameState.table, &currentFrameCopy);
        frame=MatToQImage(currentFrameCopy);

        emit newFrame(frame);
        //printTest();
    }
    qDebug() << "Stopping processing thread...";
}

//  updates the FPS rate by calculating it from time kept
void ProcessingThread::updateFPS(int timeElapsed)
{
    // Add instantaneous FPS value to queue
    if(timeElapsed>0)
    {
        fps.enqueue((int)1000/timeElapsed);
        // Increment sample number
        sampleNo++;
    }
    // Maximum size of queue is 16
    if(fps.size() > 16)
        fps.dequeue();
    // Update FPS value every 16 samples
    if((fps.size()==16)&&(sampleNo==16))
    {
        // Empty queue and store sum            // Canny edge detection

        while(!fps.empty())
            fpsSum+=fps.dequeue();
        avgFPS=fpsSum/16; // Calculate average FPS
        fpsSum=0; // Reset sum
        sampleNo=0; // Reset sample number
    }
} // updateFPS()

// a shutdown function for the thread
void ProcessingThread::stopProcessingThread()
{
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
} // stopProcessingThread()


void ProcessingThread::setROI()
{
    // Save selection as new (current) ROI
    currentROI=selectionBox;
    qDebug() << "ROI successfully SET.";
    // Reset setROIOn flag to FALSE
    setROIFlag=false;
} // setROI()

void ProcessingThread::resetROI()
{
    // Reset ROI to original
    currentROI=originalROI;
    qDebug() << "ROI successfully RESET.";
    // Reset resetROIOn flag to FALSE
    resetROIFlag=false;
} // resetROI()

// calc. te avg FPS for display
int ProcessingThread::getAvgFPS()
{
    return avgFPS;
} // getAvgFPS()

// a getter function to check the size of the image buffer
int ProcessingThread::getCurrentSizeOfBuffer()
{
    return currentSizeOfBuffer;
} // getCurrentSizeOfBuffer()

Rect ProcessingThread::getCurrentROI()
{
    return currentROI;
} // getCurrentROI();


/* a predicate to check if the frame should be processed
 * keeps a counter modulo _PROCESSINGTHREAD_PFPS (definee in ProcessingThread.hpp)
 * if the counter is 0 we want to process otherwise we don't
 *
 * return 1 iff we want the frame to be processed
 */
int ProcessingThread::decideToProcess(){

    // process frame
    if (pcounter == 0) {
        pcounter = (pcounter + 1) % _PROCESSINGTHREAD_PFPS;
        return 1;
    }

    // don't process frame
    pcounter = (pcounter + 1) % _PROCESSINGTHREAD_PFPS;
    return 0;
}


/* this is the function where all the processing on frames is done
    and new game state is set

  */
int ProcessingThread::process(Mat *matrix){

    // we reachecd the end of a game and we see the table is empty (from cards/any other things besides the table)
    if ( (GameState.status == END_GAME) && (is_frame_empty(*matrix, blackVal))){
        GameState.status = NEW_GAME;

    }
    if (GameState.status==END_GAME) return 0; //don't process


    int avr_card_h;
    int avr_card_w;
    cleanTable(&newTable);
    getTableFromMat(&newTable, matrix,&avr_card_h,&avr_card_w);     // get info of the table from the frame
    fill_known_cards(&newTable,&GameState.table,*matrix,Glyphs, keypoints,70,20); //get the letters of the cards

    // check that te dealer didn't move too much (indicates that the dealer was hidden behind a hand in the frame)
    if (is_dealer_in_same_location(&newTable, &GameState.table,avr_card_h,avr_card_h) == 0){
        return 0;
    }

    // get the number of cards of each value on the table
    char tempInv[13] = {0};
    getTableInventory(&newTable, tempInv);
    // get the count of the cards on the table
    int tempCount = countCards(tempInv);

    // if the game hasn't ended check if it's the dealers turn (has > 1 cards) or the players' turn
    if ((GameState.status != END_GAME) && (newTable.players.size() > 0)){
        if ((newTable.players.size() > 0) && (newTable.players.at(0).cards.size() > 1)){
            GameState.status = DEALER_TURN;
        }
        else {
            GameState.status = PLAYER_TURN;
        }
    }

    // check if the dealer has any players to play against (if they all bust - go to end game)
    char flag = 0;
    if ((newTable.players.size() > 1) && (GameState.status == PLAYER_TURN)){
        flag = 1;
        for (uint i = 1; i < newTable.players.size(); i++){
            int val = getHandVal(newTable.players.at(i));
            if ((val <= 21) || (val == BLACK_JACK) ){
                flag = 0;
                break;
            }

        }
    }


    // check on dealers turn if there is a player who didn't bust/lose to the dealer yet
    if ((newTable.players.size() > 1) &&
            (GameState.status == DEALER_TURN)){
        flag = 1;  // will stay 1 after the for iff the dealer has the highest hand
        int dval = getHandVal(newTable.players.at(0));
        for (uint i = 1; i < newTable.players.size(); i++){
            int val = getHandVal(newTable.players.at(i));

            if ((dval == BLACK_JACK) || (dval >= 17)) {
                flag = 1;
                break;
            }
            if ((val > dval) && (val <= 21) ){
                flag = 0;
                break;
            }

        }
    }

    // from the last to checks (above) the flag is 1 if the game has ended - update the Game State
    if (flag == 1){
        // a game ended update GameState (nothing new should go on the table until it is empty again
        GameState.status = END_GAME;

        //update the game state history
        for (uint i = 0; i < 13; i++){
            GameState.history[i] += tempInv[i];
        }

        //update the game state count with the temp count
        GameState.deckCount += tempCount;

        int dVal = getHandVal(newTable.players.at(0));
        for (uint k = 1; k < newTable.players.size(); k++){
            int hVal = getHandVal(newTable.players.at(k));

            GameState.gameCount++;
            if ( ((hVal > dVal) && (hVal <=21)) || (((dVal > 21) && (dVal != BLACK_JACK)) && (hVal <= 21)) || (hVal == BLACK_JACK)){
                GameState.winCount++;
            }
        }
    }



    // store the new processed table and update output text
    GameState.table = newTable;
    // display new text on screen
    updateGameText(tempInv);

    return 1;
}

void ProcessingThread::writeCount(){

    std::ostringstream s;

    s << "The Count is: " << calcTrueCount(GameState) << "\n\n";
    QString countStr = QString::fromStdString(s.str());

    emit clearMsgText();
    emit newTextMsg(countStr);

}


// update the history (cards seen) on the screen
void ProcessingThread::writeHistory(){

    emit clearHistBoard();

    std::string tempStr = "";
    historyToString(GameState, &tempStr);
    QString histStr = QString::fromStdString(tempStr);
    histStr.toAscii();

    emit updateHistBoard(histStr);

    return;
}

// update the game text on screen
void ProcessingThread::updateGameText(char inv[]){

    emit clearMsgText();

    if (GameState.table.players.size() < 1) return;

    std::string str;
    tableToString(&GameState, &str, inv);
    QString msg = QString::fromStdString(str);
    msg.toAscii();

    emit newTextMsg(msg);

    return;
}

// a slot to get a command to clean the history
void ProcessingThread::deckShuffled(){
    GameState.deckCount = 0;
    cleanHistory(&GameState);
    return;
}

// sets the internal number of games played
void ProcessingThread::setGameCount(int n){
    GameState.gameCount = n;
    return;
}

// sets the internal number of games won
void ProcessingThread::setWinCount(int n){
    GameState.winCount = n;
    return;
}

// sets the black level for calibration
void ProcessingThread::setBlack(){
    this->SetBlackFlag = 1;
    return;
}

// sets the number of decks in game state
void ProcessingThread::setNumDecks(int numDecks){
    this->GameState.numDecks = numDecks;

    switch(numDecks){
    case 1:{
        GameState.stratFunc = getAdvice1Deck;
        break;
    }
    case 2:{
        GameState.stratFunc = getAdvice2Deck;
        break;
    }
    case 6:{
        GameState.stratFunc = getAdvice6Deck;
        break;
    }
    case 8:{
        GameState.stratFunc = getAdvice8Deck;
        break;
    }
    default:{
        GameState.stratFunc = getAdvice1Deck;
        break;
    }
    }

    return;
}


void ProcessingThread::setCardsType(int type){
    return;
}
