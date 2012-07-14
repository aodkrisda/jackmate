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


//processing fps rate (how often we process frames)
#define _PROCESSINGTHREAD_PFPS 30

// constants for when to process frames
#define _PROCESSINGTHREAD_FIRST_PROCESS   1
#define _PROCESSINGTHREAD_CONFIRM_PROCESS 3

// macro states for procNeeded()
#define _PROCESSINGTHREAD_NEW_STATE     0
#define _PROCESSINGTHREAD_CONFIRM_STATE   1

#include "GameLib.hpp"
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
    ProcessingThread(ImageBuffer *imageBuffer, int inputSourceWidth, int inputSourceHeight);
    ~ProcessingThread();
    void stopProcessingThread();
    int getAvgFPS();
    int getCurrentSizeOfBuffer();
    Rect getCurrentROI();
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
    // Processing flags
    bool grayscaleOn;
    bool smoothOn;
    bool dilateOn;
    bool erodeOn;
    bool flipOn;
    bool cannyOn;
    // Processing settings
    int smoothType;
    int smoothParam1;
    int smoothParam2;
    double smoothParam3;
    double smoothParam4;
    int dilateNumberOfIterations;
    int erodeNumberOfIterations;
    int flipCode;
    double cannyThreshold1;
    double cannyThreshold2;
    int cannyApertureSize;
    bool cannyL2gradient;

    //the image processing fps rate and a counter to follow it
    //int pfps;
    uint pcounter;
    int tempCounter;
    int pendFlag;
    gameTable *table;
    gameTable newTable;
    gameTable confirmTable;
    int decideToProcess();
    int process(Mat *matrix, gameTable *table);
    gameState GameState;
    void updateGameText(gameState state, std::string *str);
    void printTest();

    // Task data
    bool setROIFlag;
    bool resetROIFlag;
    Rect selectionBox;
protected:
    void run();
private slots:
    void updateProcessingFlags(struct ProcessingFlags);
    void updateProcessingSettings(struct ProcessingSettings);
    void updateTaskData(struct TaskData);
signals:
    void newFrame(const QImage &frame);

    //TODO: ADD A TEXTEDIT SIGNAL:
    void clearText();
    void newTextMsg(const QString &text);
};

#endif // PROCESSINGTHREAD_H
