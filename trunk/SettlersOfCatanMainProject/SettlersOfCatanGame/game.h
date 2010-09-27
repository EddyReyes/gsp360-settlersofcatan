#pragma once

#include "player.h"
#include "map.h"
#include "sdl/sdl.h"
#include "random.h"
#include "sdlManager.h"

//static sdlManager& sdlMgr = sdlManager::getInstance();

struct Vector
{
	float x, y;
	Vector():x(0),y(0){}
	void set(float x, float y){this->x = x; this->y = y;}
};

class Game
{
private:
	//map
	map underlyingBoard;

	// player
	player player[4];
	Vector playerSize;
	Vector playerLocation;
	Vector playerVelocity;
	float speed;
	
	// color board
	int colorW, colorH;
	Uint32 ** colors;
	Uint32 timer;
	Uint32 changeTime;
	void randomizeColors();

	//sdlManager
	sdlManager sdlMgr;

public:
	Game();
	void draw(SDL_Surface * screen);
	void update(int ms);
	void input(SDL_Event & e);
};

void Game::randomizeColors()
{
	for(int h = 0; h < colorH; ++h)
	{
		for(int w = 0; w < colorW; ++w)
		{
			colors[h][w] = randomColor();
		}
	}
}

Game::Game()
{
	playerSize.set(10, 10);
	playerLocation.set(10, 10);
	speed = 20;

	underlyingBoard.initializeCenters();
	sdlMgr.loadImages();

	colorW = 15;
	colorH = 8;
	colors = new Uint32 * [colorH];
	for(int i = 0; i < colorH; ++i)
		colors[i] = new Uint32[colorW];

	randomizeColors();
	changeTime = 5000;
	timer = 0;
}

void Game::draw(SDL_Surface * screen)
{
	sdlMgr.draw(screen, &underlyingBoard);
	//SDL_FillRect(screen, 0, 0);			// black screen

	//SDL_Rect colorCursor = {0,0,15,15};
	//for (int i = 0; i < 19; ++i)
	//{
	//	colorCursor.x = underlyingBoard.myCenters[i].x * (400 / 9) - 64;
	//	colorCursor.y = underlyingBoard.myCenters[i].y * 50 - 55;
	//	SDL_FillRect(screen, &colorCursor, -1);
	//}
	///*
	//SDL_Rect colorCursor = {0,0,15,15};
	//for(int h = 0; h < colorH; ++h)
	//{
	//	for(int w = 0; w < colorW; ++w)
	//	{
	//		colorCursor.x = w * 20;
	//		colorCursor.y = h * 20;
	//		SDL_FillRect(screen, &colorCursor, colors[h][w]);
	//	}
	//}
	//*/

	//SDL_Rect drawRect = {
	//	(short)playerLocation.x,
	//	(short)playerLocation.y,
	//	(short)playerSize.x, 
	//	(short)playerSize.y
	//};
	//SDL_FillRect(screen, &drawRect, -1);	// white player box
	//SDL_Flip(screen);
}
void Game::update(int ms)
{
	Vector move;
	move.x = playerVelocity.x * ms / 1000;
	move.y = playerVelocity.y * ms / 1000;
	playerLocation.x += move.x;
	playerLocation.y += move.y;

	timer += ms;

	if(timer >= changeTime)
	{
		timer -= changeTime;
		randomizeColors();
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
		case SDLK_UP:	playerVelocity.y -= speed;	break;
		case SDLK_DOWN:	playerVelocity.y += speed;	break;
		case SDLK_LEFT:	playerVelocity.x -= speed;	break;
		case SDLK_RIGHT:playerVelocity.x += speed;	break;
		case SDLK_d:{	printf("d button works!\n");} break;
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
