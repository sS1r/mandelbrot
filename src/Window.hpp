#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <string>

#include <SDL2/SDL.h>

//Class for window management
//Since this is a very simple program, we add all the rendered textures/objects
//in this class and just simply call "Window::render()" to render everything.
//
//It also takes care of coloring and creating all the rendered elements.
class Window
{
public:
	Window();
	~Window();

	//Initializes SDL2 related stuff
	void init(unsigned w, unsigned h, const char* title);

	//Displays the rendered pixels
	void update();

	//Creates mandelbrot texture
	//Arguments: mandelbrotData -- vector containing the iteration counts
	void createMandelbrot(const std::vector<unsigned>& mandelbrotData, unsigned maxiters);

	//Draws a rectangle from (x1, y1) to (x2, y2)
	void createRect(unsigned x1, unsigned y1, unsigned x2, unsigned y2);

	//Hides the rectangle
	void hideRect();

	//Draws mandelbrot texture
	void drawMandelbrot();

	//Draws the zoom rectangle
	void drawRect();

	//Draw some helper lines
	void drawHelper();

	//Fill the window with white color
	void clear();

	//Renders everything and updates the display
	void render();

	//Get width/height
	unsigned getW() const;
	unsigned getH() const;

	//Saves the mandelbrot texture to PNG
	void saveMandelbrotToPNG(std::string filename);

private:

	SDL_Texture* mandelbrot;

	bool rectVisible;
	SDL_Rect zoomRect;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif
