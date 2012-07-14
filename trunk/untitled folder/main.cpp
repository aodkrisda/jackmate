



#include "card_detection.h"




int main(int argc, char** argv)
{
    static const char* names[] = {  "D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0000.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0001.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0001.bmp", // bad
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0003.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0004.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0005.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0006.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0007.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0008.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0009.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0010.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0011.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0012.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0013.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0014.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0015.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0016.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0017.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0018.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0019.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0020.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0021.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0022.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0023.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0024.bmp",
									"D:\\Adi\\blackjack\\avacam\\CamSnapShots\\Cam0025.bmp",
									 0 };
	
	IplImage * Glyphs[13];
	IpVec keypoints[13];
	preLoadGlyphs(Glyphs ,keypoints);

	gameTable oldTable;
	oldTable.numCards = 0;

	for( int i = 0; i<100 != 0; i++ )
    {

        Mat image = imread(names[0+i%25], 1);
        if( image.empty() )
        {
            printf("%s%d","\n couldnt load frame num: ",i);
            continue;
        }
		//imshow("table - read", image);
		gameTable Table;
		getTableFromMat(& Table, &image);



		printf("%s%d","\n frame num: ",i);

		fill_known_cards(&Table,&oldTable,image,Glyphs, keypoints,70,20); //play with the nums


		draw_on_image(Table,image);

		for (int i=0; i<Table.players.size() ; i++)
		{
			printf("%s%d","\n		hand number: ",i);
			for (int j=0; j<Table.players[i].cards.size() ; j++)
			{
				printf("%s%d%s%c","\n			card: ",j," is:",Table.players[i].cards[j].value);
				
			}
		}

		char c = waitKey(20);
        if( (char)c == 27 )
            break;
		oldTable = Table;
			
    }

    return 0;
}

