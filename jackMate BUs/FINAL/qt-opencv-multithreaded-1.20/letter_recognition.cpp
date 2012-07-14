/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * letter_recognition.cpp :     a library that extracts letters from a picture (using OpenSURF)
 *
 *
 */

#include "letter_recognition.h"


void preLoadGlyphs(IplImage * Glyphs[13] ,IpVec ipts[13]){///home/oshri/Downloads/qt-opencv-multithreaded-1.20/
          //load all 13 glyphs
    printf("glyph   0\n ");fflush(stdout);

    Glyphs[0] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardA.png");
      surfDetDes(Glyphs[0], ipts[0], false, 2, 2, 2, 0.001f);//, 2, 2, 2, 0.001f
      Glyphs[1] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card2.png");
      surfDetDes(Glyphs[1], ipts[1], false, 2, 1, 0, 0.000001f);//, 2, 1, 1, 0.000001f
      Glyphs[2] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card3.png");
      surfDetDes(Glyphs[2], ipts[2], false, 2, 2, 2, 0.000001f);//, 3, 2, 1, 0.0001f
      Glyphs[3] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card4.png");
      surfDetDes(Glyphs[3], ipts[3], false, 3, 2, 1, 0.000001f);
      Glyphs[4] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card5.png");
      surfDetDes(Glyphs[4], ipts[4], false, 4, 3, 0, 0.00000001f); // , 4, 3, 0, 0.000001f
      Glyphs[5] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card6.png");
      surfDetDes(Glyphs[5], ipts[5], false, 3, 1, 2, 0.0001f);
      Glyphs[6] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card7.png");
      surfDetDes(Glyphs[6], ipts[6], false, 3, 0, 3, 0.0001f);
      Glyphs[7] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card8.png");
      surfDetDes(Glyphs[7], ipts[7], false, 4, 2, 0, 0.000001f);
      Glyphs[8] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card9.png");
      surfDetDes(Glyphs[8], ipts[8], false, 3, 1, 2, 0.0001f);
      Glyphs[9] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card10.png");
      surfDetDes(Glyphs[9], ipts[9], false, 2, 0, 0, 0.000001f);
      Glyphs[10] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardJ.png");
      surfDetDes(Glyphs[10], ipts[10], false, 4, 2, 0, 0.000001f); // , 4, 1, 0, 0.000001f
      Glyphs[11] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardQ.png");
      surfDetDes(Glyphs[11], ipts[11], false, 2, 2, 0, 0.000001f);
      Glyphs[12] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardK.png");
      surfDetDes(Glyphs[12], ipts[12], false, 2, 2, 1, 0.000001f); //, 1, 2, 1, 0.000001f


  Glyphs[0] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardA.png");
  Glyphs[1] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card2.png");
  Glyphs[2] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card3.png");
  Glyphs[3] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card4.png");
  Glyphs[4] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card5.png");
  Glyphs[5] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card6.png");
  Glyphs[6] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card7.png");
  Glyphs[7] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card8.png");
  Glyphs[8] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card9.png");
  Glyphs[9] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/card10.png");
  Glyphs[10] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardJ.png");
  Glyphs[11] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardQ.png");
  Glyphs[12] = cvLoadImage("/home/oshri/Downloads/qt-opencv-multithreaded-1.20/cardK.png");
  printf("all glyphs\n ");

 // cvDestroyWindow("Glyphs");
  printf("\n");
}


char Match(IplImage* src, IplImage * Glyphs[13],IpVec keypoints[13])
{

  // Declare Ipoints and other stuff
  IpPairVec matches;
  IpVec ref_ipts;
  int allMatches[13];





  IplImage *img =src;
  if (img == NULL) error("Need to load reference image in order to run matching procedure");
  CvPoint src_corners[4] = {{0,0}, {img->width,0}, {img->width, img->height}, {0, img->height}};
  CvPoint dst_corners[4];
  // Extract reference object Ipoints
  surfDetDes(img, ref_ipts, false, 4, 2, 1, 0.000001f); //, 4, 2, 1, 0.000001f)
  // this was not bad - missed 3, 7 ======= , 5, 6, 2, 0.0000001f);
  // working but the 3 ====== , 5, 6, 1, 0.0001f);

  // best so far ! ======= , 5, 4, 1, 0.001f);
  // and down , 5, 6, 2, 0.000001f);

  // better , 5, 3, 1, 0.001f); maybe 530
  // , 5, 3, 2, 0.000001f);

  //, 4, 3, 0, 0.000001f);
  //, 5, 3, 2, 0.000001f); just 7=3

  //, 4, 3, 0, 0.000001f);
  //, 4, 2, 1, 0.000001f); too fine A=10

  //, 4, 3, 1, 0.000001f);
  //, 4, 2, 1, 0.000001f); 6=9 not bad, slow


  //drawIpoints(img, ref_ipts);
  //cvShowImage("OpenSURF", img);
  //waitKey(20);

  // Create a window

  // Main capture loop
  for(int i=0;i<13;i++)
  {
    // overview on all 13 cards
          img = Glyphs[i];



    // Fill match vector
    getMatches(keypoints[i],ref_ipts,matches);
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
    //drawFPS(img);

    // Display the result
    //cvShowImage("OpenSURF", img);
        //waitKey(20);
  }
 // cvDestroyWindow("OpenSURF");
  int matchCard = -1;
  int temp = 1;
  for(int i=0;i<13;i++)
          if(temp<=allMatches[i]){
                  temp = allMatches[i];
                  matchCard=i;
          }
          matchCard++;
          if (matchCard==1) return 'A';
          else if (matchCard==2) return '2';
          else if (matchCard==3) return '3';
          else if (matchCard==4) return '4';
          else if (matchCard==5) return '5';
          else if (matchCard==6) return '6';
          else if (matchCard==7) return '7';
          else if (matchCard==8) return '8';
          else if (matchCard==9) return '9';
          else if (matchCard==10) return 'T';
          else if (matchCard==11) return 'J';
          else if (matchCard==12) return 'Q';
          else if (matchCard==13) return 'K';
          return 'N';

}


char extractvalue(Mat img, IplImage * Glyphs[13],IpVec keypoints[13])
{
    int top, bottom, left, right; 
    Scalar value; 
        IplImage* newImg = NULL;
        RNG rng(12345);


        //flood and fill parameters
        int lo_diff, up_diff; //the low and up flood randge which can be adjusted
        CvConnectedComp comp;
        CvPoint floodSeed; //the original pixel where the flood begins
        CvScalar floodColor;
        lo_diff=10; //worked for big:14
        up_diff=60; //worked for big:255
        floodColor = CV_RGB( 255, 255, 255 ); //set the flood color to red
        //cvNamedWindow("src", 1);
        //load original image
        newImg = new IplImage (img);
        //cvShowImage( "src", newImg );

        //convet to B&W
        IplImage *im_gray = cvCreateImage(cvGetSize(newImg),IPL_DEPTH_8U,1);
        cvCvtColor(newImg,im_gray,CV_RGB2GRAY);
        IplImage* img_bw = cvCreateImage(cvGetSize(im_gray),IPL_DEPTH_8U,1);
        newImg = im_gray;
        //continue flood fill

        //PAINTING THE BLACK BORDER
                //make a copy of the original image
                floodSeed=cvPoint(0,0); //flooding start from pixel(60, 60)
                //Flood and Fill from pixel(60, 60) with color red and the flood range of (-8, +8)
                cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                                                                                CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);
                int temp_w = newImg->width-1;
                if (temp_w < 0)
                        temp_w = 0;
                int temp_h = newImg->height-1;
                if (temp_h < 0)
                        temp_h = 0;

                floodSeed=cvPoint(temp_w,0);
                //Flood and Fill from pixel(60, 60) with color red and the flood range of (-8, +8)
                cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                                                                                CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);

                floodSeed=cvPoint(0,temp_h);
                //Flood and Fill from pixel(60, 60) with color red and the flood range of (-8, +8)
                cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                                                                                CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);
                floodSeed=cvPoint(temp_w,temp_h);
                //Flood and Fill from pixel(60, 60) with color red and the flood range of (-8, +8)
                cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                                                                                CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);




        //B&W convert
        //cvThreshold(newImg, img_bw, 150, 255, CV_THRESH_BINARY);

        //newImg = img_bw;


        /// Initialize arguments for the filter
        top = (int) (0.7*newImg->height);
        bottom = (int) (0.7*newImg->height);
        left = (int) (0.7*newImg->width);
        right = (int) (0.7*newImg->width);

        //convert from IplImage to CvMAt//
        Mat dstM;
        Mat mtx(newImg);

        // add contrast
        dstM.convertTo(dstM , CV_8U, 2 , 0 );

        //inlarging the image border
        value = Scalar( rng.uniform(255, 255), rng.uniform(255, 255), rng.uniform(255, 255) );
    copyMakeBorder( newImg, dstM, top, bottom, left, right, IPL_BORDER_CONSTANT, value ); 


        //matching + converting back to IplImage
        IplImage* imgIp = new IplImage(dstM);

        //cvShowImage( "flood&fill", imgIp );
        //waitKey(20);
        char c = Match(imgIp, Glyphs,keypoints);





        //cleanning
        //cvDestroyWindow( "src" );
        //cvDestroyWindow( "newImage" );
        cvReleaseImage( &newImg );
        return c;

}
