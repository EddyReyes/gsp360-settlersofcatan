#include "game.h"
#include "map.h"
#include "sdl/sdl.h"
#include "menu.h"

Game::Game()
{
	gameState = Game::MENU;
	underlyingBoard.initializeCenters();
	underlyingBoard.loadImages();
	m.loadImages();
	changeTime = 5000;
	timer = 0;
	placeHolderTurnTwo = 0;
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
	underlyingBoard.shutdownImages();
	m.shutdownImages();
}

void Game::draw(SDL_Surface * screen)
{
	switch(gameState)
	{
	case Game::MENU:

		//printf("The Menu Screen goes here!!!\n");

		SDL_FillRect(screen, 0, 0);
		m.draw(screen);
		SDL_Flip(screen);

		break;
	case Game::GAME:
		//printf("We are INSIDE the game!!!\n");
		
		SDL_FillRect(screen, 0, 0);
		underlyingBoard.draw(screen, &p[activePlayer]);
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
		if(underlyingBoard.mapState == map::ENDTURN)
		{
			if (underlyingBoard.overallTurn == 2)
			{
				placeHolderTurnTwo++;
				activePlayer = 0;
			}
			cout << "placeHolderTurnTwo is " << placeHolderTurnTwo << endl;
			activePlayer++;
			if (activePlayer >= numPlayers)
			{
				activePlayer = 0;
				underlyingBoard.overallTurn++;
			}
			cout << "placeHolderTurnTwo is " << placeHolderTurnTwo << endl;
			cout << "Overall turn is " << underlyingBoard.overallTurn << endl;

			if (underlyingBoard.overallTurn == 2)
			{
				if (placeHolderTurnTwo > (numPlayers - 1))
				{
					underlyingBoard.overallTurn++;
					underlyingBoard.mapState = map::MAP;
				}
				else
				{
					activePlayer = (numPlayers - 1) - placeHolderTurnTwo;
					underlyingBoard.mapState = map::TURNTWOSETTLEMENT;
				}
			}
			else if (underlyingBoard.overallTurn == 1)
			{
				underlyingBoard.mapState = map::TURNONESETTLEMENT;
			}
			else
			{
				underlyingBoard.mapState = map::BEGINTURN;
				cout << "A WHOLE NEW WORLD! TURN " << underlyingBoard.overallTurn << endl;
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
		/*case SDLK_1:	num = 1;	break;
		case SDLK_2:	num = 2;	break;*/
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
	underlyingBoard.handleInput(e, &p[activePlayer]);
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
