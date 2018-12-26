#include "Window.hpp"

#include <SDL2/SDL.h>

Window::Window(): mandelbrot(nullptr), rectVisible(false), zoomRect{0, 0, 0, 0}, window(nullptr), renderer(nullptr)
{

}

Window::~Window()
{
	if(mandelbrot) SDL_DestroyTexture(mandelbrot);
	if(renderer) SDL_DestroyRenderer(renderer);
	if(window) SDL_DestroyWindow(window);
}

void Window::init(unsigned w, unsigned h, const char* title)
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
}

void Window::createMandelbrot(const std::vector<unsigned>& mandelbrotData)
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

void Window::createRect(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
	rectVisible = true;

	zoomRect.x = x1;
	zoomRect.y = y1;
	zoomRect.w = x2 - x1;
	zoomRect.h = y2 - y1;
}

void Window::hideRect()
{
	rectVisible = false;
}

void Window::drawRect()
{
	if(rectVisible)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(renderer, &zoomRect);
	}
}

void Window::render()
{
	clear();
	drawMandelbrot();
	drawRect();
	update();
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

