//#include "game.h"
//#include "random.h"
//
//
//void Game::randomizeColors()
//{
//	for(int h = 0; h < colorH; ++h)
//	{
//		for(int w = 0; w < colorW; ++w)
//		{
//			colors[h][w] = randomColor();
//		}
//	}
//}
//
//Game::Game()
//{
//	playerSize.set(10, 10);
//	playerLocation.set(10, 10);
//	speed = 20;
//
//	colorW = 15;
//	colorH = 8;
//	colors = new Uint32 * [colorH];
//	for(int i = 0; i < colorH; ++i)
//		colors[i] = new Uint32[colorW];
//
//	randomizeColors();
//	changeTime = 5000;
//	timer = 0;
//}
//
//void Game::draw(SDL_Surface * screen)
//{
//	SDL_FillRect(screen, 0, 0);			// black screen
//
//	SDL_Rect colorCursor = {0,0,15,15};
//	for(int h = 0; h < colorH; ++h)
//	{
//		for(int w = 0; w < colorW; ++w)
//		{
//			colorCursor.x = w * 20;
//			colorCursor.y = h * 20;
//			SDL_FillRect(screen, &colorCursor, colors[h][w]);
//		}
//	}
//
//	SDL_Rect drawRect = {
//		(short)playerLocation.x,
//		(short)playerLocation.y,
//		(short)playerSize.x, 
//		(short)playerSize.y
//	};
//	SDL_FillRect(screen, &drawRect, -1);	// white player box
//	SDL_Flip(screen);
//}
//void Game::update(int ms)
//{
//	Vector move;
//	move.x = playerVelocity.x * ms / 1000;
//	move.y = playerVelocity.y * ms / 1000;
//	playerLocation.x += move.x;
//	playerLocation.y += move.y;
//
//	timer += ms;
//
//	if(timer >= changeTime)
//	{
//		timer -= changeTime;
//		randomizeColors();
//	}
//}
//void Game::input(SDL_Event & e)
//{
//	switch(e.type)
//	{
//	case SDL_KEYDOWN:
//		switch(e.key.keysym.sym)
//		{
//		case SDLK_UP:	playerVelocity.y -= speed;	break;
//		case SDLK_DOWN:	playerVelocity.y += speed;	break;
//		case SDLK_LEFT:	playerVelocity.x -= speed;	break;
//		case SDLK_RIGHT:playerVelocity.x += speed;	break;
//		}
//	}
//}
