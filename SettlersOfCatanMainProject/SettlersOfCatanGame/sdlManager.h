#pragma once

//#include "dv_sdlgrafix.h"
#include "game.h"
#include "sdl/sdl.h"
#include "sdl/sdl_ttf.h"
#include "stndrd.h"
#include <iostream>
#include <string> 
#include <ctime>
#include <time.h>
using namespace std;

class sdlManager
{
public:
	
	static sdlManager& getInstance() { static sdlManager pInstance; return pInstance; }
	~sdlManager(void);
	void loadImages();
	void draw(SDL_Surface *, map *);
	void shutdown();
	sdlManager(void);
private:
	SDL_Surface *background;
	SDL_Surface *hexTile;
	SDL_Surface *woodTile;
	SDL_Surface *sheepTile;
	SDL_Surface *brickTile;
	SDL_Surface *stoneTile;
	SDL_Surface *wheatTile;
	SDL_Surface *chitTile[10];
	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
};

//constructor
sdlManager::sdlManager(void)
{
	background = NULL;
	hexTile = NULL;
	woodTile = NULL;
	wheatTile = NULL;
	stoneTile = NULL;
	sheepTile = NULL;
	brickTile = NULL;
	for (int i = 0; i < 10; ++i)
	{
		chitTile[i] = NULL;
	}
}
//sdlManager destructor
sdlManager::~sdlManager(void)
{
}

//Free up SDL and font
void sdlManager::shutdown()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(hexTile);
	SDL_FreeSurface(woodTile);
	SDL_FreeSurface(wheatTile);
	SDL_FreeSurface(stoneTile);
	SDL_FreeSurface(sheepTile);
	SDL_FreeSurface(brickTile);
	for (int i = 0; i < 10; ++i)
	{
		SDL_FreeSurface(chitTile[i]);
	}
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
		if (optimizedImage != NULL)
		{
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xC0, 0xC0, 0xC0 ); //GRAYSCALE COLOR KEY ( 192, 192, 192 )
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
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
	hexTile = load_image( "Hex_One.bmp" );
	background = load_image( "background.bmp" );
	woodTile = load_image( "WoodHex.bmp" );
	wheatTile = load_image( "WheatHex.bmp" );
	stoneTile = load_image( "StoneHex.bmp" );
	sheepTile = load_image( "SheepHex.bmp" );
	brickTile = load_image( "BrickHex.bmp" );
	chitTile[0] = load_image( "chit2.bmp" );
	chitTile[1] = load_image( "chit3.bmp" );
	chitTile[2] = load_image( "chit4.bmp" );
	chitTile[3] = load_image( "chit5.bmp" );
	chitTile[4] = load_image( "chit6.bmp" );
	chitTile[5] = load_image( "chit8.bmp" );
	chitTile[6] = load_image( "chit9.bmp" );
	chitTile[7] = load_image( "chit10.bmp" );
	chitTile[8] = load_image( "chit11.bmp" );
	chitTile[9] = load_image( "chit12.bmp" );
}

void sdlManager::draw(SDL_Surface * screen, map * underlyingBoard)
{
	//CREATE A GAME STATE (IE, THIS WOULD BE PLAYSCREEN)
	SDL_FillRect(screen, 0, 0);		// draw background	
	int x = 0;

	//SDL_Rect colorCursor = {0,0,15,15};
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 64;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = 32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 96;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			x = 0;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			x = 128;
		}
		switch(underlyingBoard->myCenters[i].resource)
		{
		case WOOD:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										woodTile,
										screen,
										NULL); break;
		case WHEAT:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										wheatTile,
										screen,
										NULL); break;
		case STONE:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										stoneTile,
										screen,
										NULL); break;
		case SHEEP:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										sheepTile,
										screen,
										NULL); break;
		case BRICK:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										brickTile,
										screen,
										NULL); break;
		case 'D':		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										hexTile,
										screen,
										NULL); break;
		}
	}
	x = 0;
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 0;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = -32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 32;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			x = -64;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			x = 64;
		}
		int y = 2;
		if(underlyingBoard->myCenters[i].chitWorth >= 8){ ++y; }
		if(underlyingBoard->myCenters[i].chitWorth != 0)
		{
			apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x - 19,
							underlyingBoard->myCenters[i].y * 50 - 19,
							chitTile[underlyingBoard->myCenters[i].chitWorth - y],
							screen,
							NULL);
		}
	}

	SDL_Flip(screen);
}

		