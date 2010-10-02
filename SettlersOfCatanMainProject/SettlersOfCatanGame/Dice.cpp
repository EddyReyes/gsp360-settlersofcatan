#include "dice.h"
#include <ctime>


//dice constructor
Dice::Dice(void)
{
	diceDisplay = NULL;
	diceRoll = NULL;

	textColor.r = 255;//yellowish text for now 255,255,9
	textColor.g = 255;
	textColor.b = 9;

	message = NULL;
	font = NULL;

	rolls = 0;
	diceframe1 = 0;  
	diceframe2 = 0; 
	diceframe3 = 0; 
	diceframe4 = 0;
	diceframe5 = 0;

	counterDR = 0;
	counterDD = 0;
	counterS = 0;

	numDice = 2;

	rollDice = false;
	randomize = false;
	randomRange = 6;
}

void Dice::shutdownImages()
{
	SDL_FreeSurface(diceDisplay);
	SDL_FreeSurface(diceRoll);
	SDL_FreeSurface(message);
	TTF_CloseFont(font);
}

//function to load images
SDL_Surface* Dice::load_image( std::string filename ) 
{ 
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	
	//Load the image
	loadedImage = SDL_LoadBMP( filename.c_str() ); 

	//If nothing went wrong in loading the image
	if( loadedImage != NULL ) 
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
		if (optimizedImage != NULL)
		{
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xC0, 0xC0, 0xC0 ); //GRAYSCALE COLOR KEY ( 192, 192, 192 )
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	} 
//Return the optimized image
return optimizedImage;
}

void Dice::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* clip = NULL) 
{ 
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;


	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset ); 
}
//Image Loader
void Dice::loadImages()
{
	/*background = load_image( "background.bmp" );*/
	diceDisplay = load_image( "dice_display.bmp" );
	diceRoll = load_image( "dice_roll.bmp" );

	//Open the font
	font = TTF_OpenFont( "SNAP.TTF", 18);

	//set transparency: image then color
	setTransparentColor(diceRoll, 0xFFFFFF);
	setTransparentColor(diceDisplay, 0xFFFFFF);

	//setTransparentColor(/*name of image to make transparent*/, 0x000000);
	
	//initialize values for frames
	//frameDD Dice display

		frameDD[0].x = 0; //50 is the width of each frame
		frameDD[0].y = 0;
		frameDD[0].w = 50;
		frameDD[0].h = 50;

		frameDD[1].x = 50; //50 is the width of each frame
		frameDD[1].y = 0;
		frameDD[1].w = 50;
		frameDD[1].h = 50;

		frameDD[2].x = 100; //50 is the width of each frame
		frameDD[2].y = 0;
		frameDD[2].w = 50;
		frameDD[2].h = 50;

		frameDD[3].x = 150; //50 is the width of each frame
		frameDD[3].y = 0;
		frameDD[3].w = 50;
		frameDD[3].h = 50;

		frameDD[4].x = 200; //50 is the width of each frame
		frameDD[4].y = 0;
		frameDD[4].w = 50;
		frameDD[4].h = 50;

		frameDD[5].x = 250; //50 is the width of each frame
		frameDD[5].y = 0;
		frameDD[5].w = 50;
		frameDD[5].h = 50;

		//---------------------------------------------------
		//frames for frameDR Dice Rolls
		frameDR[0].x = 0; //50 is the width of each frame
		frameDR[0].y = 0;
		frameDR[0].w = 50;
		frameDR[0].h = 50;

		frameDR[1].x = 50; //50 is the width of each frame
		frameDR[1].y = 0;
		frameDR[1].w = 50;
		frameDR[1].h = 50;

		frameDR[2].x = 100; //50 is the width of each frame
		frameDR[2].y = 0;
		frameDR[2].w = 50;
		frameDR[2].h = 50;

		frameDR[3].x = 150; //50 is the width of each frame
		frameDR[3].y = 0;
		frameDR[3].w = 50;
		frameDR[3].h = 50;

		frameDR[4].x = 200; //50 is the width of each frame
		frameDR[4].y = 0;
		frameDR[4].w = 50;
		frameDR[4].h = 50;
	
}

void Dice::drawDiceScreen(SDL_Surface * screen, int dice1, int dice2)
{
		//this is for animation through time
		static bool restartTime = true;
		static clock_t start = clock();
		float ellapseTime;

		if(restartTime)
		{
			start = clock();
			restartTime = false;
		}
		ellapseTime = (clock() - start);
		//algo for animations go here (down at if statement)
		if(ellapseTime >= 100)
		{
		ellapseTime = 0;

		
			if(rollDice == true)
			{
			//animation for dice rolling
			if(counterDR  < 3 && rolls < 12)
			{
				counterDR++;
				counterS++;
				rolls++;
			}
			
			else
			{
				counterDR = 1;
				counterS = 1;
			}

			if(rolls == 12)
			{
				counterDR = 4;
				counterS = 0;
				rollDice = false;
				rolls = 0;
			}
			}

		restartTime = true;
	
		}
		// ---- update
		// ---- render
		// clear the screen with black
		//SDL_FillRect(screen, 0, 0);

		// draw the list state to the screen buffer

		//apply_surface( 0, 0, background, screen, NULL ); 
		//apply_surface( 640, 0, background, screen, NULL );
		//apply_surface( 0, 480, background, screen, NULL );
		//apply_surface( 640, 480, background, screen, NULL );

		//draw extra sprites here

		//apply_surface(25, 350, , screen, &frameS[counterS]);

//===========================================================================================
	
		//Render the text

		/*
		message = TTF_RenderText_Solid( font, "THIS IS THE DICE GRAPHIC", textColor ); 
		apply_surface( 100, 50, message, screen, NULL ); 

		message = TTF_RenderText_Solid( font, "UP & DOWN = Random Range from 1 to 6", textColor );
		apply_surface( 100, 75, message, screen, NULL );

		message = TTF_RenderText_Solid( font, "LEFT & RIGHT = Number of dice from 1 to 5", textColor );
		apply_surface( 100, 100, message, screen, NULL );

		message = TTF_RenderText_Solid( font, "SPACE = Roll dice", textColor );
		apply_surface( 100, 125, message, screen, NULL );

		message = TTF_RenderText_Solid( font, "ESC = To exit", textColor );
		apply_surface( 100, 150, message, screen, NULL );
		*/

		int totalDice = dice1+dice2;
		switch(totalDice)
		{
			case 2: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 2." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 3: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 3." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 4: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 4." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 5: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 5." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 6: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 6." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 7: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 7." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 8: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 8." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 9: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 9." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 10: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 10." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 11: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 11." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
			case 12: message = TTF_RenderText_Solid( font, "YOU HAVE ROLLED A 12." , textColor );
		apply_surface( 100, 150, message, screen, NULL ); cout << " ROLLED A SOMETHING!" << endl;break;
		}

		if (message != NULL)
		{
			cout << "MESSAGE IS NOT NULL" << endl;
		}


//===========================================================================================


 
		if(randomize == true)
		{
			diceframe1 = random();
			diceframe2 = random();
			diceframe3 = random();
			diceframe4 = random();
			diceframe5 = random();
		}

		/*
		if(rollDice == false)
		{
			apply_surface( 100, 250, diceDisplay, screen, &frameDD[diceframe1]);
			apply_surface( 200, 250, diceDisplay, screen, &frameDD[diceframe2]);
		}
		*/
		int spacing = 100;
		apply_surface( 100, 250, diceDisplay, screen, &frameDD[dice1-1]);
		apply_surface( 200, 250, diceDisplay, screen, &frameDD[dice2-1]);
		//apply_surface( 100+(spacing * 0), 325, diceDisplay, screen, &frameDD[dice1 - 1]);
		//apply_surface( 100+(spacing * 1), 325, diceDisplay, screen, &frameDD[dice2 - 1]);
		//cout << "APPLIED THE DICE" << endl;
		//randomize = false;
}
int Dice::random()
{
	srand(time(0));
	rand();
	return rand() % randomRange;

	/*
	// our initial starting seed is 5323
	static unsigned int nSeed = 5323;

	// Take the current seed and generate a new value 
	// from it. Due to our use of large constants and 
	// overflow, it would be very hard for someone to
	// predict what the next number is going to be from 
	// the previous one.
	nSeed = (8253729 * nSeed + 2396403);

	// return a value between 0 and 32767
	return nSeed  % randomRange;
	*/
}

		
void Dice::setTransparentColor(SDL_Surface * a_surface, const int & a_transparentRGB)
{
	Uint32 colorkey = SDL_MapRGB( a_surface->format, 	//Map the color key
		0xff & (a_transparentRGB), 
		0xff & (a_transparentRGB >> 8), 
		0xff & (a_transparentRGB >> 16));
	SDL_SetColorKey( a_surface, SDL_SRCCOLORKEY, colorkey );
}