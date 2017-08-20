#include "SDLTools.hpp"

#include <SDL2/SDL.h>

void initGraphics()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw SDL_GetError();
	}
}

void quitGraphics()
{
	SDL_Quit();
}

void wait(unsigned ms)
{
	SDL_Delay(ms);
}
