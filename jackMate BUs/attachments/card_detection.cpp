// this is a library for detecting the card locations

#include "D:\\Adi\\blackjack\\openCV\\OpenCV2.2\\include\\opencv2\\core\\core.hpp"
#include "D:\\Adi\\blackjack\\openCV\\OpenCV2.2\\include\\opencv2\\imgproc\\imgproc.hpp"
#include "D:\\Adi\\blackjack\\openCV\\OpenCV2.2\\include\\opencv2\\highgui\\highgui.hpp"

#include <vector>
#include <deque>
#include <iostream>
#include <math.h>
#include <string.h>
#include "GameLib.hpp"

using namespace cv;
using namespace std;

#define _card_detection_LETTER_PRECENT 0.17 // this is a value to determin how big the letter precentage of a card is. 0.16 for normal cards
#define _card_detection_SAME_HAND_FACTOR 1.5 //this is the factor for how far away 2 cards still count as same hand, mesured in card size, and mesured between card centers


#define _card_detection_thresh 50
#define _card_detection_N 11 //thes are values for the square_detection (sensativity and size of loop) originaly: thresh = 50, N = 11;


// square detections
// #############################################################################

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
void findSquares( const Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();
    
    Mat pyr, timg, gray0(image.size(), CV_8U), gray;
    
    // down-scale and upscale the image to filter out the noise

    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;
    
    // find squares in every color plane of the image
	//debug:    
	//for( int c = 0; c < 3; c++ )
	int c = 2;
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);
        
        // try several threshold levels
        for( int l = 0; l < _card_detection_N; l++ )
		//int l = 1; //testing
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, _card_detection_thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/_card_detection_N;
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;
            
            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
                
                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.05 ) //0.3
                        squares.push_back(approx);
                }
            }
        }
    }
}

// square filtering (statisticly)
// #############################################################################

// this is a helper function to determen which point is "bigger", y is ordered then x. 
//return 1 for p1 is bigger, 0 for eq, -1 for p2


// not needed ?
bool eq_points(Point p1,Point p2)
{
	if (p1.y == p2.y) 
			return (p1.x < p2.x);
	else
			return (p1.y < p2.y);
}

//compare which hand is first on y axis then x
bool eq_hands(hand c1,hand c2)
{
	if (c1.center.y == c2.center.y) 
			return (c1.center.x < c2.center.x);
	else
			return (c1.center.y < c2.center.y);
}

bool eq_points_by_y(Point p1,Point p2)
{
	return (p1.y < p2.y);
}

bool eq_points_by_x(Point p1,Point p2)
{
	return (p1.x < p2.x);
}

void sort_points_of_square(vector<Point>& square)
{
	//sort(square.begin(),square.begin()+4,eq_points);

	//this sorts the points by 1 2
	//							3 4
	sort(square.begin(),square.begin()+4,eq_points_by_y);
	sort(square.begin(),square.begin()+2,eq_points_by_x);
	sort(square.begin()+2,square.begin()+4,eq_points_by_x);
}

void sortSquares(vector<vector<Point> >& squares )
{
	for(size_t i=0; i<squares.size() ;i++)
		sort_points_of_square(squares[i]);
	
}

int size_of_square(vector<Point>& square)
{
	int size =  (int)(sqrt( (double)  ((square[1].x-square[0].x)*(square[1].x-square[0].x)  +   (square[1].y-square[0].y)*(square[1].y-square[0].y))  )*
				 sqrt( (double)  ((square[2].x-square[0].x)*(square[2].x-square[0].x)  +   (square[2].y-square[0].y)*(square[2].y-square[0].y))  )   );
	return size;
}

void filterSquares(vector<vector<Point> >& original_squares)
{
	vector<int> sizes;
	vector<int> median_sizes;
	int median;
	vector<vector<Point> > squares;


	vector<Point> selected_centers;
	vector<vector<Point> > valid_squares;
	Point p1;
	bool bad_sq;

	if (original_squares.size()==0) // empty
		return;



	// size filter
	for (size_t i=0; i<original_squares.size();i++)
	{
		sizes.push_back(size_of_square(original_squares[i]));
		median_sizes.push_back(size_of_square(original_squares[i]));
	}

	sort(median_sizes.begin(),median_sizes.end());
	median = median_sizes[(int)median_sizes.size()/2];
	
	for (size_t i=0; i<original_squares.size();i++)
	{
		if ((sizes[i]< (median*1.5)) && (sizes[i]> (median*0.75)) )
			squares.push_back(original_squares[i]);
	}
	// position filter
	if (squares.size()==0) // empty
		return;

	valid_squares.push_back(squares[0]);
	p1.x = (squares[0][0].x + squares[0][1].x + squares[0][2].x + squares[0][3].x)/4;
	p1.y = (squares[0][0].y + squares[0][1].y + squares[0][2].y + squares[0][3].y)/4;

	selected_centers.push_back(p1);

	for (size_t i=1; i<squares.size();i++)
	{
		bad_sq = 0;
		for (size_t j=0;(!bad_sq) && (j<selected_centers.size()) ;j++)
			//if a square i includes point j
			if (((squares[i][0].x < selected_centers[j].x)&&(squares[i][3].x > selected_centers[j].x))  &&   ((squares[i][0].y < selected_centers[j].y)&&(squares[i][3].y > selected_centers[j].y))   )
			{
				bad_sq = 1;
				//this is new
				if (size_of_square(squares[i])>size_of_square(valid_squares[j]))
				{
					//re-set the valid square as the bigger one
					selected_centers[j].x = (squares[i][0].x + squares[i][1].x + squares[i][2].x + squares[i][3].x)/4;
					selected_centers[j].y = (squares[i][0].y + squares[i][1].y + squares[i][2].y + squares[i][3].y)/4;
					
					for (int t=0; t<4; t++)
					{
						valid_squares[j][t].x = squares[i][t].x;
						valid_squares[j][t].y = squares[i][t].y;
					}
				}
			}

		if (!bad_sq)
		{
			valid_squares.push_back(squares[i]);
			Point p2;
			p2.x = (squares[i][0].x + squares[i][1].x + squares[i][2].x + squares[i][3].x)/4;
			p2.y = (squares[i][0].y + squares[i][1].y + squares[i][2].y + squares[i][3].y)/4;
			selected_centers.push_back(p2);
		}

	}		

	original_squares = valid_squares; 
	
}

//this is the "cutting" lib
//replaced by gettablefrommat
vector<vector<Point>> get_card_letters(vector<vector<Point>> cards)
{
	vector<vector<Point>> chars;
	vector<Point> rect;

	for (int i=0; i< cards.size() ; i++)
	{
		rect = cards[i];
		rect[1].x = rect[0].x + ( (rect[1].x - rect[0].x)*_card_detection_LETTER_PRECENT );
		rect[1].y = rect[0].y + ( (rect[1].y - rect[0].y)*_card_detection_LETTER_PRECENT );

		rect[2].x = rect[0].x + ( (rect[2].x - rect[0].x)*_card_detection_LETTER_PRECENT );
		rect[2].y = rect[0].y + ( (rect[2].y - rect[0].y)*_card_detection_LETTER_PRECENT );

		rect[3].x = rect[0].x + ( (rect[3].x - rect[0].x)*_card_detection_LETTER_PRECENT );
		rect[3].y = rect[0].y + ( (rect[3].y - rect[0].y)*_card_detection_LETTER_PRECENT );

		chars.push_back(rect);
	}

	return chars;
}




// %%%%%%%%
// 

//helper func for the DFS - this checks if 2 cards are close enough to be in same hand.
int is_same_hand(int card_height, int card_width, card card1, card card2){
	if ( ( abs(card1.center.x - card2.center.x) < (card_width * _card_detection_SAME_HAND_FACTOR) ) &&
		 ( abs(card1.center.y - card2.center.y) < (card_height * _card_detection_SAME_HAND_FACTOR) )   )
		 return 1;
	else
		 return 0;
}


void getTableFromMat(gameTable * Table, Mat* capimg){
	vector<vector<Point> > squares;
	vector<vector<Point> > letters;
	vector<card> card_pool; //all the cards on the table.
	int cards_height =0; // this will store the avarage cards H & W, so it will be used by is_same_hand();
	int cards_width =0;

	if (capimg==NULL){
		cout << "Couldn't load img: getTableFromMat" << endl;
		return;
	}
	Mat image = *capimg;
	if( image.empty() )
        {
            cout << "Couldn't load img: getTableFromMat" << endl;
            return;
        }

	Table->numCards = 0; //reset the card num

	//find & filter the squares to find the cards
	findSquares(image, squares);
	sortSquares(squares);
	filterSquares(squares);


	//produce a "card" type
	for (int i=0; i<squares.size() ;i++){
		card new_card; //need to zero this ?
		vector<Point> letter_rect;

		letter_rect = squares.at(i);
		//letter_rect is still the whole card here, just simpler reading
		Point middle;
		middle.x = (letter_rect[0].x +letter_rect[1].x +letter_rect[2].x +letter_rect[3].x)/4;
		middle.y = (letter_rect[0].y +letter_rect[1].y +letter_rect[2].y +letter_rect[3].y)/4;
		new_card.center = middle;
		//summing the card sizes to get an avarege
		cards_height = cards_height + (int) (std::sqrt(static_cast<double>(letter_rect[2].x-letter_rect[0].x)*(letter_rect[2].x-letter_rect[0].x)
											 + (letter_rect[2].y-letter_rect[0].y)*(letter_rect[2].y-letter_rect[0].y) ));

		cards_width = cards_width + (int) (std::sqrt(static_cast<double>(letter_rect[1].x-letter_rect[0].x)*(letter_rect[1].x-letter_rect[0].x)
											 + (letter_rect[1].y-letter_rect[0].y)*(letter_rect[1].y-letter_rect[0].y) ));
		
		//cut the letter out
		letter_rect[1].x = letter_rect[0].x + ( (letter_rect[1].x - letter_rect[0].x)*_card_detection_LETTER_PRECENT );
		letter_rect[1].y = letter_rect[0].y + ( (letter_rect[1].y - letter_rect[0].y)*_card_detection_LETTER_PRECENT );

		letter_rect[2].x = letter_rect[0].x + ( (letter_rect[2].x - letter_rect[0].x)*_card_detection_LETTER_PRECENT );
		letter_rect[2].y = letter_rect[0].y + ( (letter_rect[2].y - letter_rect[0].y)*_card_detection_LETTER_PRECENT );

		letter_rect[3].x = letter_rect[0].x + ( (letter_rect[3].x - letter_rect[0].x)*_card_detection_LETTER_PRECENT );
		letter_rect[3].y = letter_rect[0].y + ( (letter_rect[3].y - letter_rect[0].y)*_card_detection_LETTER_PRECENT );

		new_card.rect = squares.at(i);
		new_card.letter = letter_rect;
		new_card.color = 0;
		new_card.value = 'n'; //default non

		card_pool.push_back(new_card);
	}
	
	cards_height = (int)(cards_height/card_pool.size());
	cards_width  = (int)(cards_width/card_pool.size());

	//// divide card_pool to hands


	for (int i=0; i<card_pool.size(); i++)
	{
		if (card_pool.at(i).color == 0) //if we have a card undetected yet
		{
			deque<card> deq;
			hand newHand;
			newHand.numHand = i; //set a hand number
			newHand.center.x=0;
			newHand.center.y=0;
			card_pool.at(i).color = 1;
			deq.push_back(card_pool.at(i));
			while (!deq.empty())
			{
				card cur_card;
				cur_card = deq.front();
				deq.pop_front();
				Table->numCards = Table->numCards + 1; //add it to the card count
				newHand.cards.push_back(cur_card); //add it to the hand
				newHand.center.x= cur_card.center.x + newHand.center.x; //sum the centers to avrage later.
				newHand.center.y= cur_card.center.y + newHand.center.y;
				for (int j=0; j<card_pool.size(); j++) //find nieghbors
					if ((card_pool.at(j).color == 0) && (is_same_hand(cards_height,cards_width, cur_card, card_pool.at(j))) )
					{
						card_pool.at(j).color = 1;
						deq.push_back(card_pool.at(j));
					}
			}
			newHand.center.x = newHand.center.x / newHand.cards.size();
			newHand.center.y = newHand.center.y / newHand.cards.size();
			Table->players.push_back(newHand);

		}
		//else -continue find a new undiscoverd node
	}

	//sort the hands by where they are. y first then x.
	sort(Table->players.begin(),Table->players.end(),eq_hands);




}

/*
 function breadthFirstSearch (Start, Goal) { 
     enqueue(Queue,Start)
     while notEmpty(Queue)) {
         Node := dequeue(Queue)
         if Node = Goal {
             return Node
         }
         for each Child in Expand(Node) {
             if notVisited(Child) {
                 setVisited(Child)
                 enqueue(Queue, Child)
             }
         }
     }



*/