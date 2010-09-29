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


void apply_surface(
		int x, int y,SDL_Surface* source, 
		SDL_Surface* destination, 
		SDL_Rect *clip);

public:
Menu(){}
void Menu::loadImage()
{
	//splash = load_image( "splash.bmp" );
	//menuScreen = load_image("menuScreen.bmp");
	background = load_image( "background.bmp" );
}

	void draw(SDL_Surface * screen)
	{
	
	}

};