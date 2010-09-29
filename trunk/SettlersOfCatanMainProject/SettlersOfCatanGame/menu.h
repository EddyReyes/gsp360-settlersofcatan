#pragma once
#include "sdl/SDL_ttf.h"
#include "dv_sdlgrafix.h"
#include "sdl/sdl.h"
#include <iostream>
#include <ctime>

class Menu
{
private:
	SDL_Surface *background;
	//SDL_Surface *splash;

	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);

public:
	void Menu::shutdownImages();
	void Menu::draw(SDL_Surface * screen);
	void Menu::loadImages();
Menu(){}
	


};