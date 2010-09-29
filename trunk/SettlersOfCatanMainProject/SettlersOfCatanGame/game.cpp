#include "game.h"
#include "map.h"
#include "sdl/sdl.h"


Game::Game()
{
	underlyingBoard.initializeCenters();
	underlyingBoard.loadImages();
	changeTime = 5000;
	timer = 0;
}

void Game::draw(SDL_Surface * screen)
{
	SDL_FillRect(screen, 0, 0);
	underlyingBoard.draw(screen);
	SDL_Flip(screen);
}
void Game::update(int ms)
{
	timer += ms;

	if(timer >= changeTime)
	{
		timer -= changeTime;
	}
}

//Mouse controls/mouse down condition
bool mouse_down = false;

//if on Game object(s) condition
bool on_object = false;

void Game::input(SDL_Event & e)
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
		case SDLK_d:{printf("d button works!\n");
					
					/*	sdlMgr.apply_surface(400,600,
										woodTile,
										screen,
										NULL); break;*/
					
					
					
					} break;
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
