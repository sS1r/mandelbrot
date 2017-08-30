#include "Window.hpp"

#include <SDL2/SDL.h>

Window::Window(unsigned w, unsigned h, const char* title): mandelbrotData(0)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    if(!window)
    {
	throw SDL_GetError();
    }
	
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
	throw SDL_GetError();
    }

    mandelbrot = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if(!mandelbrot)
    {
	throw SDL_GetError();
    }
    
    mandelbrotData.resize(w*h, 0);
}

Window::~Window()
{
    SDL_DestroyTexture(mandelbrot);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::insertMandelbrot(unsigned x, unsigned y, unsigned iters)
{
    if(x > getW() || y > getH())
    {
	throw "Window::insertMandelbrot: pixel outside Window";
    }
    
    unsigned i = y*getW() + x;
    mandelbrotData[i] = iters;
}


void Window::createMandelbrot(unsigned maxiters)
{
    SDL_SetRenderTarget(renderer, mandelbrot);

    for(unsigned i = 0;i < mandelbrotData.size();i++)
    {
	unsigned iters = mandelbrotData[i];
	
	if(iters == 0)
	{
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else
	{
	    SDL_SetRenderDrawColor(renderer, 255, iters*5, 0, 255);
	}

	unsigned y = i / getW();
	unsigned x = i - y * getW();
	
	SDL_RenderDrawPoint(renderer, x, y);      
    }
    
    SDL_SetRenderTarget(renderer, NULL);
}

void Window::drawMandelbrot()
{
    SDL_RenderCopy(renderer, mandelbrot, NULL, NULL);
}

void Window::update()
{
    SDL_RenderPresent(renderer);
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Window::drawPoint(unsigned int r, unsigned int g, unsigned int b, unsigned int x, unsigned int y)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Window::drawRect(unsigned r, unsigned g, unsigned b, unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = x2 - x1;
    rect.h = y2 - y1;
	
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

unsigned Window::getW() const
{
    int w = 0;
    SDL_GetWindowSize(window, &w, NULL);
    return w;
}

unsigned Window::getH() const
{
    int h = 0;
    SDL_GetWindowSize(window, NULL, &h);
    return h;
}
