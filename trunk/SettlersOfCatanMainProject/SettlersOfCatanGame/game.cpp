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
}

void Game::initGame(int const & a_numPlayers)
{
	numPlayers = a_numPlayers;
	p = new player[numPlayers];
	activePlayer = 0;
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

		printf("The Menu Screen goes here!!!\n");

		SDL_FillRect(screen, 0, 0);
		m.draw(screen);
		SDL_Flip(screen);

		break;
	case Game::GAME:
		printf("We are INSIDE the game!!!\n");
		
		SDL_FillRect(screen, 0, 0);
		underlyingBoard.draw(screen);
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
		printf("I am in the loop\n");

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
		case SDLK_1:	num = 1;	break;
		case SDLK_2:	num = 2;	break;
		case SDLK_3:	num = 3;	break;
		case SDLK_4:	num = 4;	break;
		}
		if(num > 0)
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
	switch(e.type)
	{
	
		case SDL_KEYDOWN:

		switch(e.key.keysym.sym)
		{
		
		case SDLK_UP:	//playerVelocity.y -= speed;	
			break;
		case SDLK_DOWN:	//playerVelocity.y += speed;	
			break;
		case SDLK_LEFT:	//playerVelocity.x -= speed;	
			break;
		case SDLK_RIGHT://playerVelocity.x += speed;	
			break;
		case SDLK_d:{printf("d button works!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");} 
			break;

		case SDL_MOUSEBUTTONDOWN: //Mouse button pressed
			{
				if (SDL_BUTTON_LEFT)//LEFT CLICK
				{
					//mouse_down = true;   
					break;
				}
				if(SDL_BUTTON_RIGHT ) 
				{
					//mouse_down = true;   
					break;
				}
				break;
			}
			//CHECK BUTTON
		case SDL_MOUSEBUTTONUP:
			//MOUSE UP LET ME KNOW
			{
				if (SDL_BUTTON_LEFT)//LEFT button up
				{
					break;
				}
				if(SDL_BUTTON_RIGHT )//right button up 
				{
					break;
				}
				break;
			}			
		case SDL_MOUSEMOTION:
			{
				if(mouse_down && on_object)
				{	
					break;
				}
			}
			break;
		}
	}
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
