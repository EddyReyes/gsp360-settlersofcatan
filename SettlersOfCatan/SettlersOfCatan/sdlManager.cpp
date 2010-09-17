#include "sdlManager.h"
#include "dv_sdlgrafix.h"

//dice frames
SDL_Rect frameDD[6];
SDL_Rect frameDR[5];

////sprite frames
//SDL_Rect frameS[6];

int rolls = 0;

int diceframe1 = 0;  
int diceframe2 = 0; 
int diceframe3 = 0; 
int diceframe4 = 0;
int diceframe5 = 0;

//The color of the font 
SDL_Color textColor = {255,255,9};//yellowish text for now


//constructor
sdlManager::sdlManager(void)
{
	background = NULL;
	
	diceDisplay = NULL;
	diceRoll = NULL;

	message = NULL;
	font = NULL;

	counterDR = 0;
	counterDD = 0;
	counterS = 0;

	numDice = 1;

	rollDice = false;
	randomize = false;
	randomRange = 6;

}
//sdlManager destructor
sdlManager::~sdlManager(void)
{
}

//Free up SDL and font
void sdlManager::shutdown()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(diceDisplay);
	SDL_FreeSurface(diceRoll);

	TTF_CloseFont(font);

	//additional sprites  
	//SDL_FreeSurface(/*space sprites name here*/);
}

//function to load images
SDL_Surface* sdlManager::load_image( std::string filename ) 
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
	} 
//Return the optimized image
return optimizedImage;
}

void sdlManager::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* clip = NULL) 
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
void sdlManager::loadImages()
{
	background = load_image( "background.bmp" );
	diceDisplay = load_image( "dice_display.bmp" );
	diceRoll = load_image( "dice_roll.bmp" );

	//Open the font
	font = TTF_OpenFont( "SNAP.ttf", 18);

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

void sdlManager::draw(SDL_Surface * screen)
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
		SDL_FillRect(screen, 0, 0);

		// draw the list state to the screen buffer
		apply_surface( 0, 0, background, screen, NULL ); 
		apply_surface( 640, 0, background, screen, NULL );
		apply_surface( 0, 480, background, screen, NULL );
		apply_surface( 640, 480, background, screen, NULL );

		//draw extra sprites here

		//apply_surface(25, 350, /*place image here to apply*/, screen, &frameS[counterS]);

//===========================================================================================
	
		//Render the text
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

//===========================================================================================


		int spacing = 100;
 
		if(randomize == true)
		{
			diceframe1 = random();
			diceframe2 = random();
			diceframe3 = random();
			diceframe4 = random();
			diceframe5 = random();
		}


		//check and draws dice
		switch(numDice)
		{
		case 1:
		//draw dice	
			if(rollDice == false)
			{
		apply_surface( 100, 250, diceDisplay, screen, &frameDD[diceframe1]);
			}
		apply_surface( 100, 325, diceRoll, screen, &frameDD[counterDR]);
		randomize = false;
		break;
		case 2:
			if(rollDice == false)
			{
			apply_surface( 100, 250, diceDisplay, screen, &frameDD[diceframe1]);
			apply_surface( 200, 250, diceDisplay, screen, &frameDD[diceframe2]);
			}
			for(int i = 0; i < 2; i++)
			{		
				
				apply_surface( 100+(spacing * i), 325, diceRoll, screen, &frameDD[counterDR]);
	
			}
			randomize = false;
			break;
		case 3:
			if(rollDice == false)
			{
			apply_surface( 100, 250, diceDisplay, screen, &frameDD[diceframe1]);
			apply_surface( 200, 250, diceDisplay, screen, &frameDD[diceframe2]);
			apply_surface( 300, 250, diceDisplay, screen, &frameDD[diceframe3]);
			}
			for(int i = 0; i < 3; i++)
			{	
			
				apply_surface( 100+(spacing * i), 325, diceRoll, screen, &frameDD[counterDR]);
	
			}
			randomize = false;
			break;
		case 4:
			if(rollDice == false)
			{
			apply_surface( 100, 250, diceDisplay, screen, &frameDD[diceframe1]);
			apply_surface( 200, 250, diceDisplay, screen, &frameDD[diceframe2]);
			apply_surface( 300, 250, diceDisplay, screen, &frameDD[diceframe3]);
			apply_surface( 400, 250, diceDisplay, screen, &frameDD[diceframe4]);
			}
			for(int i = 0; i < 4; i++)
			{
				apply_surface( 100+(spacing * i), 325, diceRoll, screen, &frameDD[counterDR]);
	
			}
			randomize = false;
			break;
		case 5:
			if(rollDice == false)
			{
			apply_surface( 100, 250, diceDisplay, screen, &frameDD[diceframe1]);
			apply_surface( 200, 250, diceDisplay, screen, &frameDD[diceframe2]);
			apply_surface( 300, 250, diceDisplay, screen, &frameDD[diceframe3]);
			apply_surface( 400, 250, diceDisplay, screen, &frameDD[diceframe4]);
			apply_surface( 500, 250, diceDisplay, screen, &frameDD[diceframe5]);
			}
			for(int i = 0; i < 5; i++)
			{
				apply_surface( 100+(spacing * i), 325, diceRoll, screen, &frameDD[counterDR]);
	
			}
			randomize = false;
			break;
		default:
			break;
		}
		// flip the screen buffer
		SDL_Flip(screen);	
}
int sdlManager::random()
{
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
}

		