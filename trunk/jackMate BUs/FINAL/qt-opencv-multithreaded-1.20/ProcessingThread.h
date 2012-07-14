/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * ProcessingThread.hpp :        a thread class that works with the capture thread through the image buffer
 *                               it gets a feed of frames and makes all the process needed to
 *                               show information on the screen - cv, text, probability calculations etc.
 *
 *
 * GUI is mainly based on qt-opencv-multithreaded (see below credits)
 */


// CREDITS:
/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* ProcessingThead.h                                                    */
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

#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#pragma once

//processing fps rate (how often we process frames)
#define _PROCESSINGTHREAD_PFPS 30

// constants for when to process frames
#define _PROCESSINGTHREAD_FIRST_PROCESS   1
#define _PROCESSINGTHREAD_CONFIRM_PROCESS 3

// macro states for procNeeded()
#define _PROCESSINGTHREAD_NEW_STATE     0
#define _PROCESSINGTHREAD_CONFIRM_STATE   1

#include "GameLib.hpp"
#include "card_detection.h"

#include "Structures.h"

// Qt header files
#include <QThread>
#include <QtGui>
// OpenCV header files
#include <opencv/highgui.h>

using namespace cv;

class ImageBuffer;

class ProcessingThread : public QThread
{
    Q_OBJECT

public:
    ProcessingThread(ImageBuffer *imageBuffer, int inputSourceWidth, int inputSourceHeight);    // constructor
    ~ProcessingThread();                                                                        // destruc.
    void stopProcessingThread();
    int getAvgFPS();
    int getCurrentSizeOfBuffer();
    Rect getCurrentROI();
    void setNumDecks(int numDecks);
    void setBettingUnits(int units);
    void setCardsType(int cardsType);
    void setWinCount(int n);
    void setGameCount(int n);
private:
    void updateFPS(int);
    void setROI();
    void resetROI();
    ImageBuffer *imageBuffer;
    volatile bool stopped;
    int inputSourceWidth;
    int inputSourceHeight;
    int currentSizeOfBuffer;
    Mat currentFrameCopy;
    Mat currentFrameCopyGrayscale;
    Rect originalROI;
    Rect currentROI;
    QImage frame;
    QTime t;
    int processingTime;
    QQueue<int> fps;
    int fpsSum;
    int sampleNo;
    int avgFPS;
    QMutex stoppedMutex;
    QMutex updateMembersMutex;
    Size frameSize;
    Point framePoint;

    //the image processing fps rate and a counter to follow it
    //int pfps;
    uint pcounter;
    int tempCounter;
    int pendFlag;
    gameTable *table;
    gameTable newTable;
    int SetBlackFlag;
    float blackVal;
    int gameCount;
    int winCount;

    int decideToProcess();
    int process(Mat *matrix);
    gameState GameState;
    void updateGameText(char inv[]);
    void writeHistory();

    //SURF_Params surfParams;
    IplImage * Glyphs[13];
    IpVec keypoints[13];
    void processHand(gameTable *table,Mat *matrix, int handNum);


    // Task data
    bool setROIFlag;
    bool resetROIFlag;
    Rect selectionBox;
protected:
    void run();
private slots:
//    void updateProcessingFlags(struct ProcessingFlags);
//    void updateProcessingSettings(struct ProcessingSettings);
//    void updateTaskData(struct TaskData);
signals:
    void newFrame(const QImage &frame);
    void clearMsgText();
    void newTextMsg(const QString &text);
    void clearHistBoard();
    void updateHistBoard(const QString &text);
public slots:
    void deckShuffled();
    void setBlack();
};

#endif // PROCESSINGTHREAD_H
