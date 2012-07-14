
#include "card_detection.h"



// DEBUG: display functions - should be outside
// #############################################################################

const char* wndname = "Square Detection Demo"; //DEBUG - just for display//

// the function draws all the squares in the image
void drawSquares_cards( Mat& image, const vector<card> cards,int color )
{
    for( size_t i = 0; i < cards.size(); i++ )
    {

        int n = cards[i].rect.size();
		vector<Point>card_shape;

		card_shape.push_back(cards[i].rect[0]);
		card_shape.push_back(cards[i].rect[1]);
		card_shape.push_back(cards[i].rect[3]);
		card_shape.push_back(cards[i].rect[2]); //sort the dots to make a square not a hour-glass
		const Point* p = &card_shape[0];
		polylines(image, &p , &n, 1, true, Scalar((((color+1)*47)%255),  (((color+3)*51)%255)  ,(((color+4)*87)%255)), 2, CV_AA);


		//letter line
		vector<Point>letter_shape;

		letter_shape.push_back(cards[i].letter[0]);
		letter_shape.push_back(cards[i].letter[1]);
		letter_shape.push_back(cards[i].letter[3]);
		letter_shape.push_back(cards[i].letter[2]); //sort the dots to make a square not a hour-glass
		const Point* p2 = &letter_shape[0];
		polylines(image, &p2 , &n, 1, true, Scalar(0,0,255), 1, CV_AA);
		
    }
}

void draw_on_image(gameTable Table, Mat image){
	//draw the line hands for the players
		for (int i=0 ; i< Table.players.size() ; i++)
			drawSquares_cards(image, Table.players.at(i).cards ,Table.players.at(i).numHand);

		//refresh display
		imshow(wndname, image);
}

//this could be faster if not converting to IPLIMAGE
Mat cut_a_letter_out(Mat master, card my_card){

	IplImage *img1 = new IplImage(master);
/* sets the Region of Interest
   Note that the rectangle area has to be __INSIDE__ the image */

	int x = min(my_card.letter[0].x,my_card.letter[2].x);
	int y = min(my_card.letter[0].y,my_card.letter[1].y);
	int width = max(my_card.letter[1].x,my_card.letter[3].x) - x;
	int height = max(my_card.letter[2].y,my_card.letter[3].y) - y;
	cvSetImageROI(img1, cvRect(x , y,width , height ));
 
/* create destination image
   Note that cvGetSize will return the width and the height of ROI */
	IplImage *img2 = cvCreateImage(cvGetSize(img1),
                               img1->depth,
                               img1->nChannels);
 
/* copy subimage */
	cvCopy(img1, img2, NULL);

/* always reset the Region of Interest */
	cvResetImageROI(img1);

	Mat mtx(img2);
	//imshow("inside conc", img2);

	return img2;
}



int main(int argc, char** argv)
{
    static const char* names[] = {  "D:\\Adi\\blackjack\\visual_projects\\samples\\pic1.png",
									"D:\\Adi\\blackjack\\visual_projects\\samples\\pic2.png", 
									"D:\\Adi\\blackjack\\visual_projects\\samples\\pic3.png",
									"D:\\Adi\\blackjack\\visual_projects\\samples\\pic4.png", 
									"pic5.png", "pic6.png", 0 };
    namedWindow( wndname, 1 );
    
	for( int i = 0; i<100 != 0; i++ )
    {
        Mat image = imread(names[2+(i%4)], 1);
        if( image.empty() )
        {
            cout << "Couldn't load " << names[i] << endl;
            continue;
        }

		gameTable Table;
		getTableFromMat(& Table, &image);


		draw_on_image(Table,image);
		printf("%s%d","\n frame num: ",i);

		Mat letter = cut_a_letter_out(image, Table.players[0].cards[0]);
		imshow("letter", letter);
		

		char c = waitKey();
        if( (char)c == 27 )
            break;
			
    }

    return 0;
}
