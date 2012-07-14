/*#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv2\\core\\core.hpp"
using namespace cv;
using namespace  std;
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h> 
#include <stdio.h> 
#include "fasthessian.h"
#include "integral.h"
#include "responselayer.h"
#include "surf.h"
#include "utils.h"
#include "surflib.h"
#include "kmeans.h"
#include "ipoint.h"
#include <ctime>
#include <iostream>
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv2\\imgproc\\imgproc.hpp" 
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\cv.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\cvaux.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\cxcore.h"
#include "C:\\Program Files\\OpenCV2.2\\include\\opencv\\highgui.h"



//-------------------------------------------------------


int mainMatch(void)
{
  // Initialise capture device
  CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
  if(!capture) error("No Capture");

  // Declare Ipoints and other stuff
  IpPairVec matches;
  IpVec ipts, ref_ipts;
  int allMatches[13];
  //load all 13 glyphs
  IplImage * Glyphs[13];
  Glyphs[0] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\cardA.png"); 
  Glyphs[1] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card2.png"); 
  Glyphs[2] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card3.png"); 
  Glyphs[3] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card4.png"); 
  Glyphs[4] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card5.png"); 
  Glyphs[5] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card6.png"); 
  Glyphs[6] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card7.png"); 
  Glyphs[7] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card8.png"); 
  Glyphs[8] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card9.png"); 
  Glyphs[9] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card10.png"); 
  Glyphs[10] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\cardJ.png"); 
  Glyphs[11] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\cardQ.png"); 
  Glyphs[12] = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\cardK.png"); 
  
  
  // This is the reference object we wish to find in video frame
  // Replace the line below with IplImage *img = cvLoadImage("imgs/object.jpg"); 
  // where object.jpg is the planar object to be located in the video
  IplImage *img = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card2.png"); 
  if (img == NULL) error("Need to load reference image in order to run matching procedure");
  CvPoint src_corners[4] = {{0,0}, {img->width,0}, {img->width, img->height}, {0, img->height}};
  CvPoint dst_corners[4];

  // Extract reference object Ipoints
  surfDetDes(img, ref_ipts, false, 4, 4, 2, 0.00001f);
  drawIpoints(img, ref_ipts);
  showImage(img);

  // Create a window 
  cvNamedWindow("OpenSURF", CV_WINDOW_AUTOSIZE );
  
  // Main capture loop
  for(int i=0;i<13;i++)
  {
    // Grab frame from the capture source
    //img = cvQueryFrame(capture);
	//img = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\card2side.png"); 
	  img = Glyphs[i];
     
    // Detect and describe interest points in the frame
    surfDetDes(img, ipts, false, 4, 4, 2, 0.00001f);

    // Fill match vector
    getMatches(ipts,ref_ipts,matches);
	allMatches[i]=matches.size();
    
    // This call finds where the object corners should be in the frame
    if (translateCorners(matches, src_corners, dst_corners))
    {
      // Draw box around object
      for(int i = 0; i < 4; i++ )
      {
        CvPoint r1 = dst_corners[i%4];
        CvPoint r2 = dst_corners[(i+1)%4];
        cvLine( img, cvPoint(r1.x, r1.y),
          cvPoint(r2.x, r2.y), cvScalar(255,255,255), 3 );
      }

      for (unsigned int i = 0; i < matches.size(); ++i)
        drawIpoint(img, matches[i].first);
    }

    // Draw the FPS figure
    drawFPS(img);

    // Display the result
    cvShowImage("OpenSURF", img);

    // If ESC key pressed exit loop
    if( (cvWaitKey(10) & 255) == 27 ) break;
  }
  int matchCard = -1;
  int temp = allMatches[0];
  for(int i=0;i<13;i++)
	  if(temp<=allMatches[i]){
		  temp = allMatches[i];
		  matchCard=i;
	  }
	  matchCard++;
	  printf("%d",matchCard);

		  
  // Release the capture device
  cvReleaseCapture( &capture );
  cvDestroyWindow( "OpenSURF" );
  return 0;
}









int main1()
{
	/// Global Variables  
    int top, bottom, left, right; 
    Scalar value; 
	IplImage* newImg = NULL;
	IplImage* ffImg = NULL;
	RNG rng(12345); 
//flood and fill parameters
int lo_diff, up_diff; //the low and up flood randge which can be adjusted
CvConnectedComp comp;
CvPoint floodSeed; //the original pixel where the flood begins
CvScalar floodColor;
lo_diff=20;
up_diff=20;
floodColor = CV_RGB( 255, 255, 255 ); //set the flood color to red
cvNamedWindow("src", 1);
cvNamedWindow("newImage",1);
//load original image
newImg = cvLoadImage("C:\\Users\\ricki naim\\Desktop\\opensurf\\OpenSURFcpp\\imgs\\find2bigdif1.png" ,1);
cvShowImage( "src", newImg );

//convet to B&W
IplImage *im_gray = cvCreateImage(cvGetSize(newImg),IPL_DEPTH_8U,1);
cvCvtColor(newImg,im_gray,CV_RGB2GRAY);
IplImage* img_bw = cvCreateImage(cvGetSize(im_gray),IPL_DEPTH_8U,1);
cvThreshold(im_gray, img_bw, 210, 255, CV_THRESH_BINARY); 
newImg = img_bw;
//continue flood fill



//make a copy of the original image
//ffImg=cvCloneImage( newImg );
floodSeed=cvPoint(0,0); //flooding start from pixel(60, 60)
//Flood and Fill from pixel(60, 60) with color red and the flood range of (-8, +8)
cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);

/// Initialize arguments for the filter 
	top = (int) (0.7*newImg->height);
	bottom = (int) (0.7*newImg->height); 
	left = (int) (0.7*newImg->width);
	right = (int) (0.7*newImg->width); 
	//convert from IplImage to CvMAt
	/*CvMat *dstMat = cvCreateMat(newImg->height,newImg->width,CV_32FC3 );
	cvConvert( newImg, dstMat );*/
	/*Mat dstM;
	
	Mat mtx(newImg);

	value = Scalar( rng.uniform(255, 255), rng.uniform(255, 255), rng.uniform(255, 255) ); 
    copyMakeBorder( newImg, dstM, top, bottom, left, right, IPL_BORDER_CONSTANT, value ); 

	//cvShowImage( "flood&fill", ffImg );
	imshow("newImage", dstM);
	cvWaitKey(0);




//cleanning
cvDestroyWindow( "src" );
cvDestroyWindow( "newImage" );
cvReleaseImage( &newImg );
cvReleaseImage( &ffImg );
return 0;
}
*/











 
 
