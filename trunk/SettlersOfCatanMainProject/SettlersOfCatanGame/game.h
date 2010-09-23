#pragma once

#include "map.h"

#include "sdl/sdl.h"

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

public:
	Game();
	void draw(SDL_Surface * screen);
	void update(int ms);
	void input(SDL_Event & e);
};