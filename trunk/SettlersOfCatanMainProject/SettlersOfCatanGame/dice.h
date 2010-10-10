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
	SDL_Surface *d_background;
	SDL_Surface *diceDisplay;
	SDL_Surface *diceRoll;

	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
	void setTransparentColor(SDL_Surface * a_surface, const int & a_transparentRGB);
		
public:

	Dice();


	//The color of the font 
	SDL_Color textColor; 

	SDL_Rect frameDD[6];
	SDL_Rect frameDR[5];
	int rolls;
	int diceframe1;  
	int diceframe2; 
	int diceframe3; 
	int diceframe4;
	int diceframe5;
	
	//The font that's going to be used
	TTF_Font *font;

	void shutdownImages();
	void drawDiceScreen(SDL_Surface * screen, int dice1, int dice2);
	void loadImages();
	
	bool rollDice;
	bool randomize;
	int randomRange;
	int numDice;

};