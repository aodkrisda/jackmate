/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * letter_recognition.cpp :     a library that extracts letters from a picture (using OpenSURF)
 *
 *
 */

#include "letter_recognition.h"
#include <QtGui/QApplication>

//Pre processing,load all 13 glyphs and find key points
void preLoadGlyphs(IplImage * Glyphs[13] ,IpVec ipts[13]){
    //load all 13 glyphs


//    std::string str = qApp->applicationDirPath().toStdString();
//    char * writable = new char[str.size() + 1];
//    std::copy(str.begin(), str.end(), writable);
//    writable[str.size()] = '\0';)

    Glyphs[0] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardA.png").c_str());
    //Detect and describe interest points for each Glyph
    surfDetDes(Glyphs[0], ipts[0], false, 2, 2, 2, 0.001f);//, 2, 2, 2, 0.001f
    Glyphs[1] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card2.png").c_str());
    surfDetDes(Glyphs[1], ipts[1], false, 2, 1, 0, 0.000001f);// 2, 1, 1, 0.000001f
    Glyphs[2] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card3.png").c_str());
    surfDetDes(Glyphs[2], ipts[2], false, 2, 2, 2, 0.000001f);// 3, 2, 1, 0.0001f
    Glyphs[3] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card4.png").c_str());
    surfDetDes(Glyphs[3], ipts[3], false, 3, 2, 1, 0.000001f);
    Glyphs[4] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card5.png").c_str());
            surfDetDes(Glyphs[4], ipts[4], false, 4, 3, 0, 0.00000001f); // 4, 3, 0, 0.000001f
    Glyphs[5] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card6.png").c_str());
    surfDetDes(Glyphs[5], ipts[5], false, 3, 1, 2, 0.0001f);
    Glyphs[6] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card7.png").c_str());
    surfDetDes(Glyphs[6], ipts[6], false, 3, 0, 3, 0.0001f);
    Glyphs[7] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card8.png").c_str());
    surfDetDes(Glyphs[7], ipts[7], false, 4, 2, 0, 0.000001f);
    Glyphs[8] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card9.png").c_str());
    surfDetDes(Glyphs[8], ipts[8], false, 3, 1, 2, 0.0001f);
    Glyphs[9] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card10.png").c_str());
    surfDetDes(Glyphs[9], ipts[9], false, 2, 0, 0, 0.000001f);
    Glyphs[10] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardJ.png").c_str());
    surfDetDes(Glyphs[10], ipts[10], false, 4, 2, 0, 0.000001f); // , 4, 1, 0, 0.000001f
    Glyphs[11] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardQ.png").c_str());
    surfDetDes(Glyphs[11], ipts[11], false, 2, 2, 0, 0.000001f);
    Glyphs[12] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardK.png").c_str());
    surfDetDes(Glyphs[12], ipts[12], false, 2, 2, 1, 0.000001f); //, 1, 2, 1, 0.000001f



    Glyphs[0] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardKA.png").c_str());
    Glyphs[1] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card2.png").c_str());
    Glyphs[2] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card3.png").c_str());
    Glyphs[3] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card4.png").c_str());
    Glyphs[4] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card5.png").c_str());
    Glyphs[5] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card6.png").c_str());
    Glyphs[6] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card7.png").c_str());
    Glyphs[7] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card8.png").c_str());
    Glyphs[8] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card9.png").c_str());
    Glyphs[9] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/card10.png").c_str());
    Glyphs[10] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardJ.png").c_str());
    Glyphs[11] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardQ.png").c_str());
    Glyphs[12] = cvLoadImage((qApp->applicationDirPath().toStdString() + "/glyphs/cardK.png").c_str());
}

//Given a src image, glyphes and it's keypoints return tne card value 
char Match(IplImage* src, IplImage * Glyphs[13],IpVec keypoints[13])
{

    // Declare Ipoints
    IpPairVec matches;
    IpVec ref_ipts;
    int allMatches[13]; //number of matches in each glyph


    IplImage *img =src;
    if (img == NULL) error("Need to load reference image in order to run matching procedure");
    CvPoint src_corners[4] = {{0,0}, {img->width,0}, {img->width, img->height}, {0, img->height}};
    CvPoint dst_corners[4];
    // Extract reference object Ipoints
    surfDetDes(img, ref_ipts, false, 4, 2, 1, 0.000001f); //, 4, 2, 1, 0.000001f)


    // Main capture loop
    for(int i=0;i<13;i++)
    {
        // overview on all 13 cards
        img = Glyphs[i];

        // Fill match vector
        getMatches(keypoints[i],ref_ipts,matches); //Populate matches with matched ipts
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

    }

    int matchCard = -1;
    int temp = 1;
    for(int i=0;i<13;i++) // find the glyph with the maximum matches to the src image
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

//Clears the picture and sends to detection
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
    lo_diff=10;// Maximal lower brightness/color difference between the currently observed pixel
    //and one of its neighbors in the image
    up_diff=60; //Maximal upper brightness/color difference between the currently observed pixel
    //and one of its neighbors in the image
    floodColor = CV_RGB( 255, 255, 255 ); //set the flood color to white

    //load original image
    newImg = new IplImage (img);

    //convet to gray scale
    IplImage *im_gray = cvCreateImage(cvGetSize(newImg),IPL_DEPTH_8U,1);
    cvCvtColor(newImg,im_gray,CV_RGB2GRAY);
    IplImage* img_bw = cvCreateImage(cvGetSize(im_gray),IPL_DEPTH_8U,1);
    newImg = im_gray;
    //continue flood fill

    //Painting the white border
    floodSeed=cvPoint(0,0); //flooding start from pixel(0,0)
    //Flood and Fill from pixel(0, 0) with white color in the given range
    cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                 CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);

    int temp_w = newImg->width-1; //the image width
    if (temp_w < 0)
        temp_w = 0;
    int temp_h = newImg->height-1; // the image height
    if (temp_h < 0)
        temp_h = 0;

    //Start Flood&Fill in 4 other points
    floodSeed=cvPoint(temp_w,0); //Upper right corner
    cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                 CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);

    floodSeed=cvPoint(0,temp_h); // Bottem left corner
    cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                 CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);

    floodSeed=cvPoint(temp_w,temp_h); // Bottom right corner
    cvFloodFill( newImg, floodSeed, floodColor, CV_RGB( lo_diff, lo_diff, lo_diff ),
                 CV_RGB( up_diff, up_diff, up_diff ), &comp, 8, NULL);



    /// Initialize arguments for the border size
    top = (int) (0.7*newImg->height);
    bottom = (int) (0.7*newImg->height);
    left = (int) (0.7*newImg->width);
    right = (int) (0.7*newImg->width);

    //Convert from IplImage to CvMAt//
    Mat dstM;
    Mat mtx(newImg);

    //Add contrast
    dstM.convertTo(dstM , CV_8U, 2 , 0 );

    //Inlarging the image border
    value = Scalar( rng.uniform(255, 255), rng.uniform(255, 255), rng.uniform(255, 255) );
    copyMakeBorder( newImg, dstM, top, bottom, left, right, IPL_BORDER_CONSTANT, value ); 


    //Convert back to IplImage and send to Match
    IplImage* imgIp = new IplImage(dstM);
    char c = Match(imgIp, Glyphs,keypoints);

    cvReleaseImage( &newImg );
    return c;

}
