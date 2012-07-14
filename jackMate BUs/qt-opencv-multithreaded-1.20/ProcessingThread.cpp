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

//DEBUG
#include "frame_processor.h"
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

void printTest();

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


    //game-settings init.
    initGameState(&GameState, _GameLib_NUM_DECKS);
    this->pcounter = 0;


} // ProcessingThread constructor

ProcessingThread::~ProcessingThread()
{
} // ProcessingThread destructor

void ProcessingThread::run()
{
    char c;
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
        printf("size of imageBuffer: %d\n", imageBuffer->getSizeOfImageBuffer());fflush(stdout);
        // Make copy of current frame (processing will be performed on this copy)
        currentFrame.copyTo(currentFrameCopy);
        // Set ROI of currentFrameCopy
        currentFrameCopy.locateROI(frameSize,framePoint);
        currentFrameCopy.adjustROI(-currentROI.y,-(frameSize.height-currentROI.height-currentROI.y),
                                   -currentROI.x,-(frameSize.width-currentROI.width-currentROI.x));

        updateMembersMutex.lock();
        ///////////////////
        // PERFORM TASKS //
        ///////////////////
        //        if(resetROIFlag)
        //            resetROI();
        //        else if(setROIFlag)
        //            setROI();
        //        ////////////////////////////////////
        //        // PERFORM IMAGE PROCESSING BELOW //
        //        ////////////////////////////////////
        //        else
        //        {
        // //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
        //            // Grayscale conversion
        //            if(grayscaleOn)
        //                cvtColor(currentFrameCopy,currentFrameCopyGrayscale,CV_BGR2GRAY);
        //            // Smooth (in-place operations)
        //            if(smoothOn)
        //            {
        //                if(grayscaleOn)
        //                {
        //                    switch(smoothType)
        //                    {
        //                        // BLUR
        //                        case 0:
        //                            blur(currentFrameCopyGrayscale,currentFrameCopyGrayscale,Size(smoothParam1,smoothParam2));
        //                            break;
        //                        // GAUSSIAN
        //                        case 1:
        //                            GaussianBlur(currentFrameCopyGrayscale,currentFrameCopyGrayscale,Size(smoothParam1,smoothParam2),smoothParam3,smoothParam4);
        //                            break;
        //                        // MEDIAN
        //                        case 2:
        //                            medianBlur(currentFrameCopyGrayscale,currentFrameCopyGrayscale,smoothParam1);
        //                            break;
        //                    }
        //                }
        //                else
        //                {
        //                    switch(smoothType)
        //                    {
        //                        // BLUR
        //                        case 0:
        //                            blur(currentFrameCopy,currentFrameCopy,Size(smoothParam1,smoothParam2));
        //                            break;
        //                        // GAUSSIAN
        //                        case 1:
        //                            GaussianBlur(currentFrameCopy,currentFrameCopy,Size(smoothParam1,smoothParam2),smoothParam3,smoothParam4);
        //                            break;
        //                        // MEDIAN
        //                        case 2:
        //                            medianBlur(currentFrameCopy,currentFrameCopy,smoothParam1);
        //                            break;
        //                    }
        //                }
        //            }
        //            // Dilate
        //            if(dilateOn)
        //            {
        //                if(grayscaleOn)
        //                    dilate(currentFrameCopyGrayscale,currentFrameCopyGrayscale,Mat(),Point(-1,-1),dilateNumberOfIterations);
        //                else
        //                    dilate(currentFrameCopy,currentFrameCopy,Mat(),Point(-1,-1),dilateNumberOfIterations);
        //            }
        //            // Erode
        //            if(erodeOn)
        //            {
        //                if(grayscaleOn)
        //                    erode(currentFrameCopyGrayscale,currentFrameCopyGrayscale,Mat(),Point(-1,-1),erodeNumberOfIterations);
        //                else
        //                    erode(currentFrameCopy,currentFrameCopy,Mat(),Point(-1,-1),erodeNumberOfIterations);
        //            }
        //            // Flip
        //            if(flipOn)
        //            {
        //                if(grayscaleOn)
        //                    flip(currentFrameCopyGrayscale,currentFrameCopyGrayscale,flipCode);
        //                else
        //                    flip(currentFrameCopy,currentFrameCopy,flipCode);
        //            }
        //            // Canny edge detection
        //            if(cannyOn)
        //            {
        //                // Frame must be converted to grayscale first if grayscale conversion is OFF
        //                if(!grayscaleOn)
        //                    cvtColor(currentFrameCopy,currentFrameCopyGrayscale,CV_BGR2GRAY);

        //                Canny(currentFrameCopyGrayscale,currentFrameCopyGrayscale,
        //                      cannyThreshold1,cannyThreshold2,
        //                      cannyApertureSize,cannyL2gradient);
        //            }
        //  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
        //        }
        //        ////////////////////////////////////
        //        // PERFORM IMAGE PROCESSING ABOVE //
        //        ////////////////////////////////////FIRST_STATE

        //        //// Convert Mat to QImage: Show grayscale frame [if either Grayscale or Canny processing modes are ON]
        //        if(grayscaleOn||cannyOn)
        //            frame=MatToQImage(currentFrameCopyGrayscale);
        //        //// Convert Mat to QImage: Show BGR frame
        //        else
        frame=MatToQImage(currentFrameCopy);
        updateMembersMutex.unlock();

        // Update statistics
        updateFPS(processingTime);
        currentSizeOfBuffer=imageBuffer->getSizeOfImageBuffer();

//        if (decideToProcess()){
//            gameTable tempTable;
//            process(&currentFrame, &tempTable);
//        }

        emit newFrame(frame);
       // printTest();

        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        // Inform controller of new frame (QImage)
        //        QString msg;
        //        char c;
        //        msg.append("hand");
        //        msg.append(c);
        //        emit newTextMsg(msg);


    }
    qDebug() << "Stopping processing thread...";
}

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

void ProcessingThread::updateProcessingFlags(struct ProcessingFlags processingFlags)
{
    QMutexLocker locker(&updateMembersMutex);
    this->grayscaleOn=processingFlags.grayscaleOn;
    this->smoothOn=processingFlags.smoothOn;
    this->dilateOn=processingFlags.dilateOn;
    this->erodeOn=processingFlags.erodeOn;
    this->flipOn=processingFlags.flipOn;
    this->cannyOn=processingFlags.cannyOn;
} // updateProcessingFlags()

void ProcessingThread::updateProcessingSettings(struct ProcessingSettings processingSettings)
{
    QMutexLocker locker(&updateMembersMutex);
    this->smoothType=processingSettings.smoothType;
    this->smoothParam1=processingSettings.smoothParam1;
    this->smoothParam2=processingSettings.smoothParam2;
    this->smoothParam3=processingSettings.smoothParam3;
    this->smoothParam4=processingSettings.smoothParam4;
    this->dilateNumberOfIterations=processingSettings.dilateNumberOfIterations;
    this->erodeNumberOfIterations=processingSettings.erodeNumberOfIterations;
    this->flipCode=processingSettings.flipCode;
    this->cannyThreshold1=processingSettings.cannyThreshold1;
    this->cannyThreshold2=processingSettings.cannyThreshold2;
    this->cannyApertureSize=processingSettings.cannyApertureSize;
    this->cannyL2gradient=processingSettings.cannyL2gradient;
} // updateProcessingSettings()

void ProcessingThread::updateTaskData(struct TaskData taskData)
{
    QMutexLocker locker(&updateMembersMutex);
    this->setROIFlag=taskData.setROIFlag;
    this->resetROIFlag=taskData.resetROIFlag;
    this->selectionBox.x=taskData.selectionBox.left();
    this->selectionBox.y=taskData.selectionBox.top();
    this->selectionBox.width=taskData.selectionBox.width();
    this->selectionBox.height=taskData.selectionBox.height();
} // updateTaskData()

int ProcessingThread::getAvgFPS()
{
    return avgFPS;
} // getAvgFPS()

int ProcessingThread::getCurrentSizeOfBuffer()
{
    return currentSizeOfBuffer;
} // getCurrentSizeOfBuffer()

Rect ProcessingThread::getCurrentROI()
{
    return currentROI;
} // getCurrentROI();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


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

void processHand(gameTable *table,Mat *matrix, int handNum){
    Mat imageCard;
    char c;

    hand *handPtr = &table->players.at(handNum);
    for (uint j = 0; j < handPtr->cards.size(); j++){               // go over each card of the hand
        imageCard = cut_a_letter_out( *matrix, handPtr->cards.at(j) );  // cut out the char of the card from the frame
        c = extractValue(imageCard);                                // extract the char value
        handPtr->cards.at(j).value = c;                             // assign the value to the card
    }
}

int ProcessingThread::process(Mat *matrix, gameTable *table){

    cleanTable(table);
    getTableFromMat(table, matrix);

    if (table->numCards == 0){  // new table - clean the game table
        GameState.status = NEW_GAME;
        cleanTable(&(GameState.table));
    }

    // error cases - these cases are not supposed to happen
    else if ((GameState.table.numCards > table->numCards) ||                // less cards on the table
             (GameState.table.players.size() > table->players.size())       // less hands on the table
             ){
        return 0;    // don't do anything
    }

    else if (table->players.size() > 1){    // dealer and player on the table - start processing

        if (table->numCards == 2){  //first time process
            processHand(table, matrix, 0);
            processHand(table, matrix, 1);
        }

        char inv[13] = {0};
        char oldInv[13] = {0};
        char diff[13] = {0};

        // process dealer
        if (table->players.at(0).cards.size() > GameState.table.players.at(0).cards.size()){    // dealer was handed a card
            if (GameState.status == PLAYER_TURN) GameState.status = DEALER_TURN;
            processHand(table, matrix, 0);

            //copy the rest of the players to the new table
            hand *handPtr = NULL;
            for (uint j = 1; j < GameState.table.players.size(); j++){
                handPtr = &GameState.table.players.at(j);
                table->players.push_back(*handPtr);
            }
            getHandInventory(table->players.at(0), inv);
            getHandInventory(GameState.table.players.at(0), oldInv);
        }

        //process players
        else {
            if (GameState.status == NEW_GAME) GameState.status = PLAYER_TURN;
            for (uint i = 1; i < table->players.size(); i++){
                processHand(table, matrix, i);
                getHandInventory(table->players.at(i), inv);
                getHandInventory(GameState.table.players.at(i), oldInv);
            }
        }

        getDiffInventory(inv, oldInv, diff);
        updateHistory(&GameState, diff);

    }


    return 1;

    //    if (pendFlag ==  _PROCESSINGTHREAD_NEW_STATE)
//    {
//        if (pcounter ==  _PROCESSINGTHREAD_FIRST_PROCESS)
//        {
//            getTableFromMat(&newTable, matrix);
//            extractValues(&newTable);
//            pendFlag = _PROCESSINGTHREAD_CONFIRM_STATE;
//        }
//    }

//    else if (pendFlag == _PROCESSINGTHREAD_CONFIRM_STATE)
//    {
//        pendFlag = _PROCESSINGTHREAD_NEW_STATE;
//        if (pcounter == _PROCESSINGTHREAD_CONFIRM_PROCESS)
//        {
//            getTableFromMat(&confirmTable, matrix);
//            extractValues(&confirmTable);
//            if (checkDiffTables(&newTable, &confirmTable) == 0) { // they are the same - we have confirmation
////                pendFlag = NEW_STATE;
//                if (checkDiffTables(&(GameState.table), &newTable) != 0){ // something is new to the table
//                    if (checkConsistancy(GameState, newTable) == 1){ // check that the change is not an error
//                        updateGameState(&GameState, newTable); // write down what's new
//                    }
//                }
//            }
////            else {  // the confirmation was not good - try again to confirm
////                printf("unsure\n");
////                pcounter = 1;
////                pendFlag = CONFIRM_STATE;
////                newTable = confirmTable;
////            }
//        }
//    }


}//procNeeded


void ProcessingThread::updateGameText(gameState state, std::string *str){

    emit clearText();
    tableToString(state, str);
    QString msg = QString::fromStdString(*str);
    msg.toAscii();

    emit newTextMsg(msg);
    return;
}

void ProcessingThread::printTest(){
    gameTable table1, table2;
    cleanTable(&table1);
    cleanTable(&table2);

    hand hands1[4] = {0};
    hand hands2[4] = {0};
    card cards2[20] = {0};

    cards2[0].value = '2';
    cards2[1].value = 'A';
    cards2[2].value = 'K';
    cards2[3].value = 'J';
    cards2[4].value = '8';
    cards2[5].value = '7';
    cards2[6].value = '6';
    cards2[7].value = '6';

    cards2[8].value = '2';
    cards2[9].value = 'A';
    cards2[10].value = 'K';
    cards2[11].value = 'J';
    cards2[12].value = '8';
    cards2[13].value = '7';
    cards2[14].value = '6';
    cards2[15].value = '6';
    cards2[16].value = 'K';
    cards2[17].value = '6';
    cards2[18].value = '3';
    cards2[19].value = '6';

    printf("finished init. cards\n");
    // create two hands
    uint i;
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
    std::string str ="";
    updateGameText(GameState, &str);
}
