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
	/*SDL_Surface *background;
	SDL_Surface *menuScreen;*/

	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);

public:
	void Dice::shutdownImages();
	void Dice::draw(SDL_Surface * screen);
	void Dice::loadImages();
	Dice();
	~Dice();
	


};