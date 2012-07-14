/* JackMate  11.9.2011, By Ricki Naim-Biran, Adi Zarfaty, Oshri Shmuel.
 *
 * Card_detection.cpp :     a library of functions implementing the computer vision part of the workshop
 *                          composed of functions to recognize cards on screen and extracting the cards values
 *
 *
 */


#include "card_detection.h"

#define _card_detection_SAME_HAND_FACTOR 1.35 //this is the factor for how far away 2 cards still count as same hand, mesured in card size, and mesured between card centers
#define _card_detection_BORDER_FACTOR 0.5 // this is a factor for how far the letter is from the top corner

#define _card_detection_thresh 50
#define _card_detection_N 11 //thes are values for the square_detection (sensativity and size of loop) originaly: thresh = 50, N = 11;
float _card_detection_LETTER_PRECENT = 0.5; //0.16 normal cars, 0.56 big cards:::: this is a value to determin how big the letter precentage of a card is. 0.16 for normal cards


void set_letter_prec(float val){
    _card_detection_LETTER_PRECENT = val;
}


// replacement for cv::pointploytest
// sq points are sorted like this:     0 1
//		                       2 3
int is_point_in_square(Point P, vector<Point> sq){
    Point top_inter,
            left_inter,
            right_inter,
            bottom_inter; // intersection points of the crossing lines with the square

    // find intersection points with L02, L13
    int x02;
    if (sq[0].x == sq[2].x){
        x02 = sq[0].x;
    }
    else {
        double m02 = ((double)(sq[0].y - sq[2].y)) / ((double)(sq[0].x - sq[2].x));
        x02 = (int) ( ( (double)(P.y - sq[0].y) / (double)(m02) ) + sq[0].x );
    }
    int x13;
    if (sq[1].x == sq[3].x){
        x13 = sq[1].x;
    }
    else {
        double m13 = ((double)(sq[1].y - sq[3].y)) / ((double)(sq[1].x - sq[3].x));
        x13 = (int) ( ( (double)(P.y - sq[1].y) / (double)(m13) ) + sq[1].x );
    }
    if ((P.x - x13)*(P.x - x02) > 0){
        return 0;
    }

    //now check y

    int y01;
    if (sq[0].y == sq[1].y){
        y01 = sq[0].y;
    }
    else {
        double m01 = ((double)(sq[0].y - sq[1].y)) / ((double)(sq[0].x - sq[1].x));
        y01 = (int) ( sq[0].y + m01*(P.x - sq[0].x) );
    }
    int y23;
    if (sq[2].y == sq[3].y){
        y23 = sq[2].y;
    }
    else {
        double m23 = ((double)(sq[2].y - sq[3].y)) / ((double)(sq[2].x - sq[3].x));
        y23 = (int) ( sq[2].y + m23*(P.x - sq[2].x) );
    }
    if ((P.y - y01)*(P.y - y23) > 0){
        return 0;
    }
    return 1;

}




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
    
    // find squares in the blue color plane of the image
    int c = 2; //work only on blue channel
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        //add contrast
        gray0.convertTo(gray0 , CV_8U, 2 , 0 );

        
        // try several threshold levels
        for( int l = 0; l < _card_detection_N; l++ )
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
                    if( maxCosine < 0.06 )
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

// sorts the points of the square as so:   0-----1      1-----3
//                                         |     |  ==> |     |
//                                         2-----3      0-----2
// (rotates if the card is sideways)
void straightSquares(vector<vector<Point> > * squares){
    for(int i=0; i<squares->size() ; i++){
        vector<Point> square = squares->at(i);

        Point min_y;
        if(square[0].y < square[1].y)
            min_y = square[0];
        else
            min_y = square[1];

        //calc zlaot
        int side_01 = (square[0].x-square[1].x)*(square[0].x-square[1].x) + (square[0].y-square[1].y)*(square[0].y-square[1].y);
        int side_02 = (square[0].x-square[2].x)*(square[0].x-square[2].x) + (square[0].y-square[2].y)*(square[0].y-square[2].y);

        if (side_02 < side_01){ // the card is laying sideways
            if ((min_y.x == square[1].x) && (min_y.y == square[1].y)){
                Point temp_rect[4];
                temp_rect[0] = square[0];
                temp_rect[1] = square[1];
                temp_rect[2] = square[2];
                temp_rect[3] = square[3];

                square[0] = temp_rect[1];
                square[1] = temp_rect[3];
                square[2] = temp_rect[0];
                square[3] = temp_rect[2];

            } else if ((min_y.x == square[0].x) && (min_y.y == square[0].y)){
                Point temp_rect[4];
                temp_rect[0] = square[0];
                temp_rect[1] = square[1];
                temp_rect[2] = square[2];
                temp_rect[3] = square[3];

                square[0] = temp_rect[2];
                square[1] = temp_rect[0];
                square[2] = temp_rect[3];
                square[3] = temp_rect[1];
            }
        }
        squares->at(i) = square;
    }
}

//this sorts the points by 0 1
//                         1 1
void sort_points_of_square(vector<Point>& square)
{

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

// this filters the output of findSquares
void filterSquares(vector<vector<Point> >& all_squares)
{
    vector<int> sizes;
    vector<int> median_sizes;
    int median;
    vector<vector<Point> > squares;

    vector<Point> selected_centers;
    vector<vector<Point> > original_squares, valid_squares;
    Point p1;
    bool bad_sq;

    if (all_squares.size()==0) // empty
        return;



    // size filter
    for (size_t i=0; i<all_squares.size();i++)
    {
        int size = size_of_square(all_squares[i]);
        //filter too big and too small sq
        if ((size < 60000) && (size > 2500)){
            sizes.push_back(size);
            median_sizes.push_back(size);
            original_squares.push_back(all_squares[i]);
        }
    }

    // frotection for median /2
    if (original_squares.size()==0){ // empty
        all_squares = original_squares;
        return;
    }

    sort(median_sizes.begin(),median_sizes.end());
    median = median_sizes[(int)median_sizes.size()/2];

    for (size_t i=0; i<original_squares.size();i++)
    {
        if ((sizes[i]< (median*1.5)) && (sizes[i]> (median*0.75))){
            squares.push_back(original_squares[i]);
        }
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

            if (is_point_in_square(selected_centers[j],squares[i]) )
            {
                bad_sq = 1;

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

    all_squares = valid_squares;

}


vector<vector<Point> > get_card_letters(vector<vector<Point> > cards)
{
    vector<vector<Point> > chars;
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


//helper func for the DFS - this checks if 2 cards are close enough to be in same hand.
int is_same_hand(int card_height, int card_width, card card1, card card2){
    if ( ( abs(card1.center.x - card2.center.x) < (card_width * _card_detection_SAME_HAND_FACTOR) ) &&
         ( abs(card1.center.y - card2.center.y) < (card_height * _card_detection_SAME_HAND_FACTOR) )   )
        return 1;
    else
        return 0;
}

// fills a table pointer with the squares detected information
void getTableFromMat(gameTable * Table, Mat* capimg,int * avr_card_h, int * avr_card_w){
    vector<vector<Point> > squares;
    vector<vector<Point> > letters;
    vector<card> card_pool; //all the cards on the table.
    int cards_height =0; // this will store the avarage cards H & W, so it will be used by is_same_hand();
    int cards_width =0;
    *avr_card_h = 0;
    *avr_card_w = 0;

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
    straightSquares(&squares);


    //produce a "card" type
    for (int i=0; i<squares.size() ;i++){
        card new_card;
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


        vector<Point> letter_rect_temp = letter_rect;
        letter_rect_temp[0].x = letter_rect[0].x;
        letter_rect_temp[0].y = letter_rect[0].y;

        letter_rect_temp[1].x = letter_rect[0].x + ( (letter_rect[1].x - letter_rect[0].x)*_card_detection_LETTER_PRECENT );
        letter_rect_temp[1].y = letter_rect[0].y + ( (letter_rect[1].y - letter_rect[0].y)*_card_detection_LETTER_PRECENT );

        letter_rect_temp[2].x = letter_rect[0].x + ( (letter_rect[2].x - letter_rect[0].x)*_card_detection_LETTER_PRECENT );
        letter_rect_temp[2].y = letter_rect[0].y + ( (letter_rect[2].y - letter_rect[0].y)*_card_detection_LETTER_PRECENT );

        letter_rect_temp[3].x = letter_rect[0].x + ( (letter_rect[3].x - letter_rect[0].x)*_card_detection_LETTER_PRECENT );
        letter_rect_temp[3].y = letter_rect[0].y + ( (letter_rect[3].y - letter_rect[0].y)*_card_detection_LETTER_PRECENT );

        Point offset;

        double diag = _card_detection_LETTER_PRECENT/5.5;
        offset.x = (int) ((1-diag)*letter_rect[0].x + diag*middle.x) - letter_rect[0].x;
        offset.y = (int) ((1-diag)*letter_rect[0].y + diag*middle.y) - letter_rect[0].y;


        for (int j = 0; j < 4; j++){
            letter_rect_temp[j].x = (letter_rect_temp[j].x + offset.x);
            letter_rect_temp[j].y = (letter_rect_temp[j].y + offset.y);
        }


        new_card.rect = squares.at(i);
        new_card.letter = letter_rect_temp;
        new_card.color = 0;
        new_card.value = 'N'; //default non

        card_pool.push_back(new_card);
    }

    if (card_pool.size() != 0){
        cards_height = (int)(cards_height/card_pool.size());
        cards_width  = (int)(cards_width/card_pool.size());
    }

    *avr_card_h = cards_height* _card_detection_SAME_HAND_FACTOR;
    *avr_card_w = cards_width* _card_detection_SAME_HAND_FACTOR;

    //// divide card_pool to hands
    // (BFS)


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



// #############################################################################
// the function draws all the squares in the image (hand)
void drawSquares_cards( Mat *image, const vector<card> cards,int color )
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
        polylines(*image, &p , &n, 1, true, Scalar((((color+1)*20)%200)+40,  (((color+3)*51)%200)  ,(((color+4)*103)%200)), 6, CV_AA);


        //letter line
        vector<Point>letter_shape;

        letter_shape.push_back(cards[i].letter[0]);
        letter_shape.push_back(cards[i].letter[1]);
        letter_shape.push_back(cards[i].letter[3]);
        letter_shape.push_back(cards[i].letter[2]); //sort the dots to make a square not a hour-glass
        const Point* p2 = &letter_shape[0];
        polylines(*image, &p2 , &n, 1, true, Scalar(0,0,255), 1, CV_AA);

        char text[2];
        text[0] = cards[i].value;
        text[1] = '\0';
        putText(*image, text, cards[i].center,FONT_HERSHEY_SIMPLEX,1,cvScalar(0,255,0),2,8,false);

    }
}

void draw_on_image(gameTable Table, Mat *image){
    //draw the line hands for the players
    for (int i=0 ; i< Table.players.size() ; i++)
        drawSquares_cards(image, Table.players.at(i).cards ,Table.players.at(i).numHand);
}


Mat cut_a_letter_out(Mat master, card my_card){

    IplImage *img1 = new IplImage(master);
    /* sets the Region of Interest */

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

    return img2;
}




char send_to_recognition(card curCard,Mat image,IplImage * Glyphs[13], IpVec keypoints[13]){
    Mat newImgSmall = cut_a_letter_out(image, curCard);
    Mat newImg;


    resize(newImgSmall, newImg, Size(newImgSmall.cols*2,newImgSmall.rows*2),0,0,INTER_NEAREST);

    char c = extractvalue(newImg,Glyphs,keypoints);

    return c;
}



void fill_known_cards(gameTable * curTab, gameTable* prevTab, Mat image,IplImage * Glyphs[13], IpVec Keypoints[13],int hand_diff,int card_diff){ //diff is tolerance for location change in pixels
    for (int i=0; i< curTab->players.size(); i++){
        int got_hand_val = 0;
        for (int j=0; (!got_hand_val &&  j< prevTab->players.size() ) ; j++) {
            // if the hands are in the same location
            if ( (abs(curTab->players[i].center.x - prevTab->players[j].center.x) < hand_diff) && (abs(curTab->players[i].center.y - prevTab->players[j].center.y) < hand_diff) ){
                //compare the cards
                got_hand_val = 1;
                for(int k = 0; k < curTab->players[i].cards.size() ; k++){
                    int got_card_val = 0;
                    for(int n = 0; (!got_card_val && (n < prevTab->players[j].cards.size()) ) ; n++){
                        //if the cards are in the same place - copy
                        if ( (abs(curTab->players[i].cards[k].center.x - prevTab->players[j].cards[n].center.x) < card_diff) && (abs(curTab->players[i].cards[k].center.y - prevTab->players[j].cards[n].center.y) < card_diff) ){
                            char value = prevTab->players[j].cards[n].value; //copy prev value
                            if (value != 'N'){
                                curTab->players[i].cards[k].value = value;
                                got_card_val = 1;
                            }
                        }
                    }
                    if (!got_card_val){
                        curTab->players[i].cards[k].value = send_to_recognition(curTab->players[i].cards[k],image,Glyphs,Keypoints);
                    }

                }
            }
        }
        //after loop for hand check
        //if did not find a matching hand - send the cards to recognition
        if (!got_hand_val){
            for(int k = 0; k < curTab->players[i].cards.size() ; k++){
                curTab->players[i].cards[k].value = send_to_recognition(curTab->players[i].cards[k],image,Glyphs,Keypoints);
            }
        }
    }
}

int is_frame_empty(Mat matimg,float level){

    IplImage* img = new IplImage(matimg);
    IplImage* gray = cvCreateImage( cvGetSize(img), 8, 1 );

    CvHistogram *hist;
    int hist_size = 256;
    float range[]={0,256};
    float* ranges[] = { range };

    float max_value = 0.0;
    float min_value = 0.0;

    /* Convert the image to gray */
    cvCvtColor(img,gray,CV_RGB2GRAY);

    /* Create a 1-D Array to hold the histogram */
    hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

    /* Calculate histogram of the Image and store it in the array */
    cvCalcHist( &gray, hist, 0, NULL );

    /* Find the minimum and maximum values of the histogram */
    cvGetMinMaxHistValue( hist, &min_value, &max_value, 0, 0 );


    if (max_value > level)
        return 1;
    else
        return 0;


}

float setBlackCalib(Mat matimg){

    IplImage* img = new IplImage(matimg);
    IplImage* gray = cvCreateImage( cvGetSize(img), 8, 1 );

    CvHistogram *hist;
    int hist_size = 256;
    float range[]={0,256};
    float* ranges[] = { range };

    float max_value = 0.0;
    float min_value = 0.0;

    /* Convert the image to gray */
    cvCvtColor(img,gray,CV_RGB2GRAY);

    /* Create a 1-D Array to hold the histogram */
    hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

    /* Calculate histogram of the Image and store it in the array */
    cvCalcHist( &gray, hist, 0, NULL );

    /* Find the minimum and maximum values of the histogram */
    cvGetMinMaxHistValue( hist, &min_value, &max_value, 0, 0 );


    return max_value-1000;


}


int is_dealer_in_same_location(gameTable * curTab, gameTable* prevTab,int avr_card_h,int avr_card_w){ //diff is tolerance for location change in pixels

    if ((curTab->players.size() < 1) || (prevTab->players.size() < 1)) {
        return 1;
    }

    // if the hands are in the same location
    if ( (abs(curTab->players[0].center.x - prevTab->players[0].center.x) < (avr_card_w)) && (abs(curTab->players[0].center.y - prevTab->players[0].center.y) < (avr_card_h) ))
        return 1;
    else
        return 0;

}

