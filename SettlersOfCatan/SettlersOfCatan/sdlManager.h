//SDLMANAGER

#pragma once

#include "sdl/sdl.h"
#include "sdl/sdl_ttf.h"
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
	void draw(SDL_Surface *);
	void shutdown();

	bool rollDice;
	bool randomize;
	int randomRange;
	int numDice;
	
private:

	sdlManager(void);

	//The background pic
	SDL_Surface *background;
	
	//The dice
	SDL_Surface *diceDisplay;
	SDL_Surface *diceRoll;

	//next image goes here
	//SDL_Surface *placeNextImageHere;

	//Instructions
	SDL_Surface *message;

	//The font that's going to be used
	TTF_Font *font;

	int counterDR;
	int counterDD;
	int counterS;

	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
	int random();
};