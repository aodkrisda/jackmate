/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * MainWindow.cpp :     the highest level in the GUI architecture
 *                      initializes the controller which in turn launches
 *                      the processing and capturing threads.
 *                      MainWindow.cpp also connects the different elements on screen to
 *                      elements in the program (sets vars. and callbacks)
 *
 *
 * GUI is mainly based on qt-opencv-multithreaded (see below credits)
 */


// CREDITS:
/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* MainWindow.cpp                                                       */
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

#include "CameraConnectDialog.h"
#include "Controller.h"
#include "MainWindow.h"

// Qt header files
#include <QDebug>
// Configuration header file
#include "Config.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{  
    // Setup user interface
    setupUi(this);
    // Create controller
    controller = new Controller;
    // Save application version in QString variable
    appVersion=QUOTE(APP_VERSION);
    // Create processingSettingsDialog
    initializeTaskDataStructure();
    // Enable/disable appropriate GUI items
    setInitGUIState();
    // Initialize GUI
    initializeGUI();
    // Connect signals to slots
    signalSlotsInit();
    // Initialize flag
    isCameraConnected=false;
    // clear the text box that shows the players info.
    msgBoard->clear();
} // MainWindow constructor

MainWindow::~MainWindow()
{
    // Check if camera is connected
    if(isCameraConnected)
    {
        // Disconnect connections (4)
        disconnect(controller->processingThread,SIGNAL(newFrame(QImage)),0,0);
        // Stop processing thread
        if(controller->processingThread->isRunning())
            controller->stopProcessingThread();
        // Stop capture thread
        if(controller->captureThread->isRunning())
            controller->stopCaptureThread();
        // Clear image buffer
        controller->clearImageBuffer();
        // Check if threads have stopped
        if((controller->captureThread->isFinished())&&(controller->processingThread->isFinished()))
        {
            // Disconnect camera
            controller->disconnectCamera();
            // Delete threads
            controller->deleteCaptureThread();
            controller->deleteProcessingThread();
            // Delete image buffer
            controller->deleteImageBuffer();
        }
    }
} // MainWindow destructor

void MainWindow::connectToCamera()
{
    // Create dialog
    cameraConnectDialog = new CameraConnectDialog(this);
    // PROMPT USER:
    // If user presses OK button on dialog, connect to camera; else do nothing
    if(cameraConnectDialog->exec()==1)
    {
        // Set private member variables in cameraConnectDialog to values in dialog
        cameraConnectDialog->setDeviceNumber();
        cameraConnectDialog->setImageBufferSize();
        // Store image buffer size in local variable
        imageBufferSize=cameraConnectDialog->getImageBufferSize();
        // Store device number in local variable
        deviceNumber=cameraConnectDialog->getDeviceNumber();
        // Connect to camera
        if((isCameraConnected=controller->connectToCamera(deviceNumber,imageBufferSize)))
        {
            // Create connection between processing thread (emitter) and GUI thread (receiver/listener)
            connect(controller->processingThread,SIGNAL(newFrame(QImage)),this,SLOT(updateFrame(QImage)),Qt::UniqueConnection);
            connect(controller->processingThread,SIGNAL(clearMsgText()),this->msgBoard,SLOT(clear()),Qt::UniqueConnection);
            connect(controller->processingThread,SIGNAL(newTextMsg(const QString)),this->msgBoard,SLOT(append(const QString)),Qt::UniqueConnection);
            connect(controller->processingThread,SIGNAL(clearHistBoard()),this->historyBoard,SLOT(clear()),Qt::UniqueConnection);
            connect(controller->processingThread, SIGNAL(updateHistBoard(QString)), this->historyBoard, SLOT(append(QString)), Qt::UniqueConnection);

            // Create connections (3) between GUI thread (emitter) and processing thread (receiver/listener)
            qRegisterMetaType<struct ProcessingFlags>("ProcessingFlags");
           // connect(this,SIGNAL(newProcessingFlags(struct ProcessingFlags)),controller->processingThread,SLOT(updateProcessingFlags(struct ProcessingFlags)),Qt::UniqueConnection);

            qRegisterMetaType<struct TaskData>("TaskData");
          //  connect(this,SIGNAL(newTaskData(struct TaskData)),controller->processingThread,SLOT(updateTaskData(struct TaskData)),Qt::UniqueConnection);
            // Set data to defaults in processingThread
            emit newProcessingFlags(processingFlags);
            emit newTaskData(taskData);
            // Setup imageBufferBar in main window with minimum and maximum values
            imageBufferBar->setMinimum(0);
            imageBufferBar->setMaximum(imageBufferSize);
            // Enable/disable appropriate menu items
            connectToCameraAction->setDisabled(true);
            disconnectCameraAction->setDisabled(false);
            //processingMenu->setDisabled(false);
            // Enable "Clear Image Buffer" push button in main window
            clearImageBufferButton->setDisabled(false);
            // Get input stream properties
            sourceWidth=controller->captureThread->getInputSourceWidth();
            sourceHeight=controller->captureThread->getInputSourceHeight();
            // Set text in labels in main window
            deviceNumberLabel->setNum(deviceNumber);
            cameraResolutionLabel->setText(QString::number(sourceWidth)+QString("x")+QString::number(sourceHeight));
            /*
            QThread::IdlePriority               0	scheduled only when no other threads are running.
            QThread::LowestPriority             1	scheduled less often than LowPriority.
            QThread::LowPriority                2	scheduled less often than NormalPriority.
            QThread::NormalPriority             3	the default priority of the operating system.
            QThread::HighPriority               4	scheduled more often than NormalPriority.
            QThread::HighestPriority            5	scheduled more often than HighPriority.
            QThread::TimeCriticalPriority	6	scheduled as often as possible.
            QThread::InheritPriority            7	use the same priority as the creating thread. This is the default.
            */
            // Start capturing frames from camera
            controller->captureThread->start(QThread::IdlePriority);
            // Start processing captured frames
            controller->processingThread->start();
            this->deckShuffledAction->setEnabled(1);
            this->actionSet_black->setEnabled(1);

            //connect events from

            connect(this->deckShuffledAction, SIGNAL(triggered()), controller->processingThread, SLOT(deckShuffled()));
            connect(this->actionSet_black, SIGNAL(triggered()), controller->processingThread, SLOT(setBlack()));

            controller->processingThread->setNumDecks(cameraConnectDialog->getNumDecks());

            if (cameraConnectDialog->isMockups()){
                  set_letter_prec(0.49);
            }
            else {
                  set_letter_prec(0.158);
            }

        }
        // Display error dialog if camera connection is unsuccessful
        else
            QMessageBox::warning(this,"ERROR:","Could not connect to camera.");
    }
} // connectToCamera()

void MainWindow::disconnectCamera()
{
    // Check if camera is connected
    if(controller->captureThread->isCameraConnected())
    {

        disconnect(this->deckShuffledAction, SIGNAL(triggered()), controller->processingThread, SLOT(deckShuffled()));
        disconnect(this->actionSet_black, SIGNAL(triggered()), controller->processingThread, SLOT(setBlack()));
        disconnect(controller->processingThread,SIGNAL(newFrame(QImage)),0,0);
        // Stop processing thread
        if(controller->processingThread->isRunning())
            controller->stopProcessingThread();
        // Stop capture thread
        if(controller->captureThread->isRunning())
            controller->stopCaptureThread();
        // Clear image buffer
        controller->clearImageBuffer();
        // Check if threads have stopped
        if((controller->captureThread->isFinished())&&(controller->processingThread->isFinished()))
        {
            // Disconnect camera
            controller->disconnectCamera();
            // Reset flag
            isCameraConnected=false;
            // Delete threads
            controller->deleteCaptureThread();
            controller->deleteProcessingThread();
            // Delete image buffer
            controller->deleteImageBuffer();
            // Enable/Disable appropriate menu items
            connectToCameraAction->setDisabled(false);
            disconnectCameraAction->setDisabled(true);
            deckShuffledAction->setDisabled(false);
            actionSet_black->setDisabled(false);
            // Set GUI in main window
            frameLabel->setText("No camera connected.");
            imageBufferBar->setValue(0);
            imageBufferLabel->setText("[000/000]");
            captureRateLabel->setText("");
            processingRateLabel->setText("");
            deviceNumberLabel->setText("");
            cameraResolutionLabel->setText("");
            roiLabel->setText("");
            mouseCursorPosLabel->setText("");
            clearImageBufferButton->setDisabled(true);
        }
        // Display error dialog
        else
            QMessageBox::warning(this,"ERROR:","Thread(s) could not be stopped. Camera was not disconnected.");
    }
    // Display error dialog
    else
        QMessageBox::warning(this,"ERROR:","Camera already disconnected.");
} // disconnectCamera()

void MainWindow::about()
{
    QMessageBox::information(this,"About",QString("JackMate Application created by\nRicki Naim-Biran\nAdi Zarfaty\nOshri Shmuel\n\nGUI Created by Nick D'Ademo\nContact: nickdademo@gmail.com\nWebsite: www.nickdademo.com\nVersion: ")+appVersion);
} // about()

void MainWindow::clearImageBuffer()
{
    controller->clearImageBuffer();
} // clearImageBuffer()


// updates the frame on screen
void MainWindow::updateFrame(const QImage &frame)
{
    // Show [number of images in buffer / image buffer size] in imageBufferLabel in main window
    imageBufferLabel->setText(QString("[")+QString::number(controller->processingThread->getCurrentSizeOfBuffer())+
                              QString("/")+QString::number(imageBufferSize)+QString("]"));
    // Show percentage of image bufffer full in imageBufferBar in main window
    imageBufferBar->setValue(controller->processingThread->getCurrentSizeOfBuffer());
    // Show processing rate in captureRateLabel in main window
    captureRateLabel->setNum(controller->captureThread->getAvgFPS());
    captureRateLabel->setText(captureRateLabel->text()+" fps");
    // Show processing rate in processingRateLabel in main window
    processingRateLabel->setNum(controller->processingThread->getAvgFPS());
    processingRateLabel->setText(processingRateLabel->text()+" fps");
    // Show ROI information in roiLabel in main window
    roiLabel->setText(QString("(")+QString::number(controller->processingThread->getCurrentROI().x)+QString(",")+
                      QString::number(controller->processingThread->getCurrentROI().y)+QString(") ")+
                      QString::number(controller->processingThread->getCurrentROI().width)+
                      QString("x")+QString::number(controller->processingThread->getCurrentROI().height));
    // Display frame in main window
    frameLabel->setPixmap(QPixmap::fromImage(frame));
} // updateFrame()


//updates the mouse cursor on the screen
void MainWindow::updateMouseCursorPosLabel()
{
    // Update mouse cursor position in mouseCursorPosLabel in main window
    mouseCursorPosLabel->setText(QString("(")+QString::number(frameLabel->getMouseCursorPos().x())+
                                 QString(",")+QString::number(frameLabel->getMouseCursorPos().y())+
                                 QString(")"));
} // updateMouseCursorPosLabel()


void MainWindow::initializeTaskDataStructure()
{
    taskData.setROIFlag=false;
    taskData.resetROIFlag=false;
} // initializeTaskDataStructure()

void MainWindow::initializeGUI()
{
    // Enable/disable appropriate menu items
    connectToCameraAction->setDisabled(false);
    disconnectCameraAction->setDisabled(true);
} // initializeGUI()

void MainWindow::setInitGUIState()
{
    // Set GUI in main window

    frameLabel->setText("No camera connected.");
    imageBufferBar->setValue(0);
    imageBufferLabel->setText("[000/000]");
    captureRateLabel->setText("");
    processingRateLabel->setText("");
    deviceNumberLabel->setText("");
    cameraResolutionLabel->setText("");
    roiLabel->setText("");
    mouseCursorPosLabel->setText("");
    clearImageBufferButton->setDisabled(true);
} // setInitGUIState()

void MainWindow::signalSlotsInit()
{
    connect(connectToCameraAction, SIGNAL(triggered()), this, SLOT(connectToCamera()));
    connect(disconnectCameraAction, SIGNAL(triggered()), this, SLOT(disconnectCamera()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(clearImageBufferButton, SIGNAL(released()), this, SLOT(clearImageBuffer()));
} // signalSlotsInit()
