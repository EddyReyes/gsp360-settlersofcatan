#include "sdl/sdl.h"
#include "game.h"

int main(int argc, char ** argv)
{
	// [INIT]
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
	int SCREEN_BPP = 32;
	// main state of the main loop
	if (SDL_Init( SDL_INIT_EVERYTHING ) != 0)
		printf( "Unable to init SDL: %s\n", SDL_GetError());
    // ensure a clean exit
    atexit(SDL_Quit);
    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(
		SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,SDL_HWSURFACE|SDL_DOUBLEBUF
		/*comment out FULLSCREEN to see console*//*|SDL_FULLSCREEN*/);
	bool running = true;
	SDL_Event e;
	Uint32 now, then = SDL_GetTicks(), passed;
	// initializes the game
	Game g;
	while(running)
	{
		// update
		now = SDL_GetTicks();
		passed = now - then;
		then = now;
		g.update(passed);
		// draw
		g.draw(screen);
		// input
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:		running = false; g.shutdown();	break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					g.shutdown();
					break;
				}
			 default: g.input(e);
			}
		}
		// throttle code
		Uint32 timer = SDL_GetTicks() + 10;
		while(!SDL_PollEvent(0) && SDL_GetTicks() < timer)
		{SDL_Delay(1);}
	}
	// cleanup
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}