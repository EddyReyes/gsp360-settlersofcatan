#pragma once

#include "player.h"
#include "map.h"
#include "sdl/sdl.h"


class Game
{
private:
	//map
	map underlyingBoard;

	// player
	player player[4];
	
	// timer? needed?
	Uint32 timer;
	Uint32 changeTime;


public:
	Game();
	void draw(SDL_Surface * screen);
	void update(int ms);
	void input(SDL_Event & e);
};

