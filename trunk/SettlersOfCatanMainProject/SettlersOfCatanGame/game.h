#pragma once

#include "player.h"
#include "map.h"
#include "menu.h"


class Game
{
private:
	//map
	map underlyingBoard;
	
	//game state
	int gameState;
	static const int GAME = 1;
	void gameInput(SDL_Event & e);
	
	//menu
	Menu m;
	static const int MENU = 0;
	void menuInput(SDL_Event & e);
	
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
	void shutdown(void);
};

