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