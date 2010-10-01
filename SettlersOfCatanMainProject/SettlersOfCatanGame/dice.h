#pragma once

#include "sdl/sdl.h"
#include "sdl/sdl_ttf.h"
#include <iostream>
#include <string> 
#include <ctime>
#include <time.h>
using namespace std;

class Dice
{
	int counterDR;
	int counterDD;
	int counterS;
	int random();

	//Instructions
	SDL_Surface *message;
	//The dice	
	SDL_Surface *background;
	SDL_Surface *diceDisplay;
	SDL_Surface *diceRoll;

	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
		
public:

	Dice();
	
	//The font that's going to be used
	TTF_Font *font;

	void shutdownImages();
	void draw(SDL_Surface * screen);
	void loadImages();
	
	bool rollDice;
	bool randomize;
	int randomRange;
	int numDice;

};