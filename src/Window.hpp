#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

//Class for window management
class Window
{
public:
	Window(unsigned w, unsigned h, const char* title);
	~Window();

	//Displays the rendered pixels
	void update();

	//Fill the window with white color
	void clear();
  
        //Colors a pixel with red, green and blue at (x, y)
	void drawPoint(unsigned r, unsigned g, unsigned b, unsigned x, unsigned y); 

	//Draws a rectangle from (x1, y1) to (x2, y2)
	void drawRect(unsigned r, unsigned g, unsigned b, unsigned x1, unsigned y1, unsigned x2, unsigned y2);
  
	//Get width/height
	unsigned getW();
	unsigned getH();
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
       
#endif
