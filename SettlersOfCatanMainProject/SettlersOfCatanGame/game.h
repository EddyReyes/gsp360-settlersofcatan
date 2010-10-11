#pragma once

class map;

#include "player.h"
#include "map.h"
#include "menu.h"
#include "tradebank.h"
#include "SDL_music.h"
//#include "dice.h"
#include <iostream>
#include <string> 
#include <ctime>
#include <time.h>
#include <stdio.h> // printf() 

class Game
{
private:
	//turn in Numerics.
	//int overallTurn;
	// tricky turn two placeholder
	int placeHolderTurnTwo;

	//menu
	Menu m;
	static const int MENU = 0; // menu state
	void menuInput(SDL_Event & e);
	
	//game state
	int gameState;
	static const int GAME = 1; // play state
	void gameInput(SDL_Event & e);

	// timer. needed?
	Uint32 timer;
	Uint32 changeTime;

	//=======playmusic stuff
	bool playMusic;

	void Game::initGame(int const & a_numPlayers);

public:
	//sound
	Music * gameSound;
	int MainSoundQueue;

	//map
	map * underlyingBoard;

	// player
	player * p;
	int numPlayers;
	int activePlayer;

	//need these for calculating largest army/ longest road, they store the player who has them.
	player* ownerLargestArmy;
	player* ownerLongestRoad;

	Game();
	//Music * gameSound;
	void draw(SDL_Surface * screen);
	void update(int ms);
	void input(SDL_Event & e);
	void shutdown(void);
};

