#pragma once

#include "player.h"
#include "map.h"
#include "menu.h"
#include "tradebank.h"


class Game
{
private:
	//turn in Numerics.
	//int overallTurn;
	// tricky turn two placeholder
	int placeHolderTurnTwo;

	//map
	map underlyingBoard;
	
	//game state
	int gameState;
	static const int GAME = 1; // play state
	void gameInput(SDL_Event & e);
	
	//menu
	Menu m;
	static const int MENU = 0; // menu state
	void menuInput(SDL_Event & e);
	
	// player
	int numPlayers;
	int activePlayer;
	player * p;
	
	// timer. needed?
	Uint32 timer;
	Uint32 changeTime;

	TradeBank tradebank;


	void Game::initGame(int const & a_numPlayers);

public:
	Game();
	void draw(SDL_Surface * screen);
	void update(int ms);
	void input(SDL_Event & e);
	void shutdown(void);
};

