// D:\\Adi\\blackjack\\visual_projects\\OpenSURFcpp\\src\\


#include "fasthessian.h"
#include "integral.h"
#include "responselayer.h"
#include "surf.h"
#include "utils.h"
#include "surflib.h"
//#include "kmeans.h"
#include "ipoint.h"


#include "C:\\Program Files\\OpenCV2.2\\include\\opencv2\\imgproc\\imgproc.hpp" 
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\cv.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\cvaux.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\cxcore.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\highgui.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv2\\core\\core.hpp"
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h> 
#include <stdio.h> 
#include <ctime>
#include <iostream>

using namespace cv;
using namespace  std;

//load all 13 glyphs
void preLoadGlyphs(IplImage * Glyphs[13] ,IpVec ipts[13]);

//given an image of a card returns it's value 
char Match(IplImage* src, IplImage * Glyphs[13],IpVec keypoints[13]);

//cleans the image,finds key points and send it to Match
char extractvalue(Mat img, IplImage * Glyphs[13],IpVec keypoints[13]);

