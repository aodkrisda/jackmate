// this is a library for detecting the card locations

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <vector>
#include <iostream>
#include <math.h>
#include <string.h>
//#include "GameLib.hpp"

using namespace cv;
using namespace std;


//consts



Mat cut_a_letter_out(Mat master, card my_card);



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

void getTableFromMat(gameTable * Table, Mat* capimg);

