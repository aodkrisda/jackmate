/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * Card_detection.cpp :     a library of functions implementing the computer vision part of the workshop
 *                          composed of functions to recognize cards on screen and extracting the cards values
 *
 *
 */

#ifndef CARD_DETECTION_H
#define CARD_DETECTION_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>

#include <vector>
#include <deque>
#include <iostream>
#include <math.h>
#include <string.h>
#include "GameLib.hpp"
#include "letter_recognition.h"

using namespace cv;
using namespace std;

//consts


void set_letter_prec(float val);


// square detections
// #############################################################################

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( Point pt1, Point pt2, Point pt0 );

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
void findSquares( const Mat& image, vector<vector<Point> >& squares );

// square filtering (statisticly)
// #############################################################################

// this is a helper function to determen which point is "bigger", y is ordered then x. 
//return 1 for p1 is bigger, 0 for eq, -1 for p2

// not needed
bool eq_points(Point p1,Point p2);

bool eq_points_by_y(Point p1,Point p2);

bool eq_points_by_x(Point p1,Point p2);

void sort_points_of_square(vector<Point>& square);

void sortSquares(vector<vector<Point> >& squares );

int size_of_square(vector<Point>& square);

void filterSquares(vector<vector<Point> >& original_squares);

int is_same_hand(int card_height, int card_width, card card1, card card2);

//this is the "cutting" lib
vector<vector<Point> > get_card_letters(vector<vector<Point> > cards);



// DEBUG: display functions - should be outside
// #############################################################################


// the function draws all the squares in the image
void drawSquares_cards( Mat& image, const vector<card> cards,int color );

void draw_on_image(gameTable Table, Mat *image);

//this could be faster if not converting to IPLIMAGE
Mat cut_a_letter_out(Mat master, card my_card);


void fill_known_cards(gameTable * curTab, gameTable* prevTab, Mat image,IplImage * Glyphs[13], IpVec Keypoints[13],int hand_diff,int card_diff);

void getTableFromMat(gameTable * Table, Mat* capimg,int * avr_card_h,int * avr_card_w);

int is_frame_empty(Mat matimg, float f);//depricated

float setBlackCalib(Mat matrix);//depricated


float is_frame_empty2(Mat matimg, float level);
 float setBlackCalib2(Mat matimg);

 int is_dealer_in_same_location(gameTable * curTab, gameTable* prevTab,int avr_card_h,int avr_card_w);


#endif//CARD_DETECTION_H





