/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * CameraConnectDialog.hpp :     Class that customizes a Qt QDialog
 *                               this calss is run when a new game command is sent from the gui
 *                               and supplies all the details about the settings of the new game.
 *
 *
 * GUI is mainly based on qt-opencv-multithreaded (see below credits)
 */

// CREDITS:
/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* CameraConnectDialog.h                                                */
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

#ifndef CAMERACONNECTDIALOG_H
#define CAMERACONNECTDIALOG_H

#include "ui_CameraConnectDialog.h"

class CameraConnectDialog : public QDialog, private Ui::CameraConnectDialog
{
    Q_OBJECT

public:
    CameraConnectDialog(QWidget *parent = 0);
    void setDeviceNumber();
    void setImageBufferSize();
    int getDeviceNumber();
    int getImageBufferSize();
    int getNumDecks();
    int getCardsType();
    int isMockups();
private:
    int deviceNumber;
    int imageBufferSize;
};

#endif // CAMERACONNECTDIALOG_H
