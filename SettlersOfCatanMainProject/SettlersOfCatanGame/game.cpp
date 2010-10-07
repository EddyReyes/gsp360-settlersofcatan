#include "game.h"
#include "map.h"
#include "sdl/sdl.h"
#include "SDL_music.h"
#include "menu.h"
#include <ctime>

Game::Game()
{	
	//gameSound = new Music();
	gameState = Game::MENU;
	underlyingBoard = new map();
	underlyingBoard->initializeCenters();
	underlyingBoard->loadImages();
	m.loadImages();
	changeTime = 5000;
	timer = 0;
	placeHolderTurnTwo = 0;
	srand((unsigned int)time(0));
	rand();
	ownerLargestArmy = NULL;
	ownerLongestRoad = NULL;

	wheatactive = 0;
	stoneactive = 0;
	brickactive = 0;
	woodactive = 0;
	sheepactive = 0;
	
	wheattrader = 0;
	stonetrader = 0;
	bricktrader = 0;
	woodtrader = 0;
	sheeptrader = 0;
	
	playerNumber = 0;
}

void Game::initGame(int const & a_numPlayers)
{
	numPlayers = a_numPlayers;
	p = new player[numPlayers];
	activePlayer = 0;
	for (int i = 0; i < numPlayers; ++i)
	{
		p[i].ID = i;
	}
}
void Game::shutdown(void)
{
	underlyingBoard->shutdownImages();
	m.shutdownImages();
}

void Game::draw(SDL_Surface * screen)
{
	switch(gameState)
	{
	case Game::MENU:
					
		SDL_FillRect(screen, 0, 0);
		m.draw(screen);
		SDL_Flip(screen);

		break;

	case Game::GAME:
		//printf("We are INSIDE the game!!!\n");

		SDL_FillRect(screen, 0, 0);
		underlyingBoard->draw(screen, this);
		SDL_Flip(screen);

		break;
	}

}
void Game::update(int ms)
{
	timer += ms;

	if(timer >= changeTime)
	{
		timer -= changeTime;
	}
	switch(gameState)
	{
	case Game::MENU:
		break;
	case Game::GAME:
		if(underlyingBoard->mapState == map::ENDTURN)		
		{
			activePlayer++;
			if (underlyingBoard->overallTurn == 2)
			{
				placeHolderTurnTwo++;
				activePlayer = 0;
			}
			if (activePlayer >= numPlayers)
			{
				activePlayer = 0;
				underlyingBoard->overallTurn++;
			}
			if (underlyingBoard->overallTurn == 2)
			{
				if (placeHolderTurnTwo > (numPlayers - 1))
				{
					underlyingBoard->overallTurn++;
					underlyingBoard->mapState = map::MAP;
				}
				else
				{
					activePlayer = (numPlayers - 1) - placeHolderTurnTwo;
					underlyingBoard->mapState = map::TURNTWOSETTLEMENT;
				}
			}
			else if (underlyingBoard->overallTurn == 1)
			{
				underlyingBoard->mapState = map::TURNONESETTLEMENT;
			}

			if (underlyingBoard->overallTurn >= 3)
			{
				underlyingBoard->dice1 = rand() % 6 + 1;
				underlyingBoard->dice2 = rand() % 6 + 1;
				while ((underlyingBoard->dice1 + underlyingBoard->dice2 == 7) && (underlyingBoard->overallTurn < 6))
				{
					underlyingBoard->dice1 = rand() % 6 + 1;
					underlyingBoard->dice2 = rand() % 6 + 1;
				}
				if (underlyingBoard->dice1 + underlyingBoard->dice2 == 7)
				{
					underlyingBoard->mapState = map::SETTHETHIEF;
				}
				else
				{
					underlyingBoard->mapState = map::BEGINTURN;
				}
			}
		}


		break;
	}
}

void Game::menuInput(SDL_Event & e)
{
	////////
	////this will be moving into menu
	switch(e.type)
	{
	case SDL_KEYDOWN:
		int num = 0;
		switch(e.key.keysym.sym)
		{
		case SDLK_3:	num = 3;	break;
		case SDLK_4:	num = 4;	break;
		}
		if(num >= 3)
		{
			initGame(num);
			gameState = Game::GAME;
		}
		break;
	}/////////////////////////////////
}
//Mouse controls/mouse down condition
bool mouse_down = false;

//if on Game object(s) condition
bool on_object = false;

void Game::gameInput(SDL_Event & e)
{
	underlyingBoard->handleInput(e, this);
}
void Game::input(SDL_Event & e)
{
	switch(gameState)
	{
	case Game::MENU:
		menuInput(e);
		break;
	case Game::GAME:
		gameInput(e);
		break;
	}
}