#include "eventHandler.hpp"

#include <SDL2/SDL.h>

eventHandler::eventHandler(): mouseX(0), mouseY(0), _increaseIters(false), _decreaseIters(false), mousePressed(false), quit(false)
{
  
}

eventHandler::~eventHandler()
{
  
}

void eventHandler::update()
{
	SDL_Event e;

	mouseReleased = false;
	_increaseIters = false;
	_decreaseIters = false;
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(e.button.button == SDL_BUTTON_LEFT)
			{		  
				mousePressed = true;
				dragX = e.button.x;
				dragY = e.button.y;
			}
		}
		else if(e.type == SDL_MOUSEBUTTONUP)
		{
			if(e.button.button == SDL_BUTTON_LEFT)
			{		  
				mousePressed = false;
				mouseReleased = true;
			}									
		}
		else if(e.type == SDL_MOUSEMOTION)
		{
			mouseX = e.motion.x;
			mouseY = e.motion.y;
		}
		else if(e.type == SDL_KEYDOWN)
		{
			if(e.key.keysym.sym == SDLK_UP)
			{
				_increaseIters = true;
			}
			if(e.key.keysym.sym == SDLK_DOWN)
			{
				_decreaseIters = true;
			}
		}
	}
}

int eventHandler::getMouseX()
{
	return mouseX;
}

int eventHandler::getMouseY()
{
	return mouseY;
}

int eventHandler::getDragX()
{
	return dragX;
}

int eventHandler::getDragY()
{
	return dragY;
}

bool eventHandler::increaseIters()
{
	return _increaseIters;
}	

bool eventHandler::decreaseIters()
{
	return _decreaseIters;
}	

bool eventHandler::getMousePressed()
{
	return mousePressed;
}

bool eventHandler::getMouseReleased()
{
	return mouseReleased;
}

bool eventHandler::getQuit()
{
	return quit;
}
