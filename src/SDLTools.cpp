#include "SDLTools.hpp"

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

unsigned getTicks()
{
	return SDL_GetTicks();
}
