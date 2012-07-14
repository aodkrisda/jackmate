/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * CameraConnectDialog.cpp :     Class that customizes a Qt QDialog
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
/* CameraConnectDialog.cpp                                              */
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

// Qt header files
#include <QtGui>
// Configuration header file
#include "Config.h"

CameraConnectDialog::CameraConnectDialog(QWidget *parent) : QDialog(parent)
{
    // Setup dialog
    setupUi(this);
    // deviceNumberEdit (device number) input string validation
    QRegExp rx1("[0-9]\\d{0,2}"); // Integers 0 to 999
    QRegExpValidator *validator1 = new QRegExpValidator(rx1, 0);
    deviceNumberEdit->setValidator(validator1);
    // imageBufferSizeEdit (image buffer size) input string validation
    QRegExp rx2("[0-9]\\d{0,2}"); // Integers 0 to 999
    QRegExpValidator *validator2 = new QRegExpValidator(rx2, 0);
    imageBufferSizeEdit->setValidator(validator2);
    // Set imageBufferSizeEdit to default value
    imageBufferSizeEdit->setText(QString::number(DEFAULT_IMAGE_BUFFER_SIZE));
    // Initially set deviceNumber and imageBufferSize to defaults
    deviceNumber=-1;
    imageBufferSize=DEFAULT_IMAGE_BUFFER_SIZE;

    QRegExp rx3("[1-8]"); // Integers 1 to 8
    QRegExpValidator *validator3 = new QRegExpValidator(rx3, 0);
    numDecksInput->setValidator(validator3);

} // CameraConnectDialog constructor

void CameraConnectDialog::setDeviceNumber()
{
    // "Any available camera"
    if(anyCameraButton->isChecked())
        deviceNumber=-1;
    // "Device number"
    else
    {
        // Set device number to default (any available camera) if field is blank
        if(deviceNumberEdit->text().isEmpty())
        {
            QMessageBox::warning(this->parentWidget(), "WARNING:","Device Number field blank.\nAutomatically set to 'any available camera'.");
            deviceNumber=-1;
        }
        // User-specified camera
        else
            deviceNumber=deviceNumberEdit->text().toInt();
    }
} // setDeviceNumber()

void CameraConnectDialog::setImageBufferSize()
{
    // Set image buffer size to default if field is blank
    if(imageBufferSizeEdit->text().isEmpty())
    {
        QMessageBox::warning(this->parentWidget(), "WARNING:","Image Buffer Size field blank.\nAutomatically set to default value.");
        imageBufferSize=DEFAULT_IMAGE_BUFFER_SIZE;
    }
    // Set image buffer size to default if field is zero
    else if(imageBufferSizeEdit->text().toInt()==0)
    {
        QMessageBox::warning(this->parentWidget(), "WARNING:","Image Buffer Size cannot be zero.\nAutomatically set to default value.");
        imageBufferSize=DEFAULT_IMAGE_BUFFER_SIZE;;
    }
    // Use image buffer size specified by user
    else
        imageBufferSize=imageBufferSizeEdit->text().toInt();
} // setImageBufferSize()

int CameraConnectDialog::getDeviceNumber()
{
    return deviceNumber;
} // getDeviceNumber()

int CameraConnectDialog::getImageBufferSize()
{
    return imageBufferSize;
} // getImageBufferSize()

// returns the number of decks entered by the user: if the number of decks is not in 1...8 set it to 1 as default
int CameraConnectDialog::getNumDecks(){
    int numd = this->numDecksInput->text().toInt();
    if (numd > 8 || numd < 1){
        return 1;
    }
    else {
        return numd;
    }
}

// return 0 for mock-ups, 1 for real cards
int CameraConnectDialog::getCardsType(){
    if (this->mockUpRadio->isChecked()){
        return 0;
    }
    else {
        return 1;
    }
}


int CameraConnectDialog::isMockups(){
    if (this->mockUpRadio->isChecked()){
        return 1;
    }
    else {
        return 0;
    }

}
