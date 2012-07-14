/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * main.cpp :     the file that launchs the Qt GUI files
 *
 * GUI is mainly based on qt-opencv-multithreaded (see below credits)
 */

//CREDITS:

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

#include "MainWindow.h"
#include <unistd.h>

// Qt header files
#include <QtGui/QApplication>

#define X_INITIAL 0
#define Y_INITIAL 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(QUOTE(APP_VERSION));

    QPixmap pix(qApp->applicationDirPath() + "/glyphs/splash.gif");
    QSplashScreen splash(pix);
    splash.show();
    //a.processEvents();
    sleep(3);

    MainWindow w;
    w.show();
    splash.finish(&w);
    // Set the initial screen position of the main window
    w.setGeometry(X_INITIAL, Y_INITIAL, w.width(), w.height());
    return a.exec();
} // main()
