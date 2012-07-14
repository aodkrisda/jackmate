/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * letter_recognition.cpp :     a library that extracts letters from a picture (using OpenSURF)
 *
 *
 */

//#ifndef LETTER_RECOGNITION_H
//#define LETTER_RECOGNITION_H

#define GLYPHS_LIB /home/oshri/Downloads/qt-opencv-multithreaded-1.20/

#include "fasthessian.h"
#include "integral.h"
#include "responselayer.h"
#include "surf.h"
#include "utils.h"
#include "surflib.h"
#include "ipoint.h"
#include <QtGui/QApplication>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h> 
#include <stdio.h> 
#include <ctime>
#include <iostream>

using namespace cv;
using namespace  std;


//Pre processing,load all 13 glyphs and find key points
void preLoadGlyphs(IplImage * Glyphs[13] ,IpVec ipts[13]);

//Given a src image, glyphes and keypoints return tne card value 
char Match(IplImage* src, IplImage * Glyphs[13],IpVec keypoints[13]);

//Clears the picture and sends to detection
char extractvalue(Mat img, IplImage * Glyphs[13],IpVec keypoints[13]);

//#endif//LETTER_RECOGNITION_H
