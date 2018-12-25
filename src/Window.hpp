#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

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

    //Creates mandelbrot texture
    //Arguments: mandelbrotData -- vector containing the iteration counts 
    void createMandelbrot(const std::vector<unsigned>& mandelbrotData);

    //Draws mandelbrot texture
    void drawMandelbrot();
    
    //Colors a pixel with red, green and blue at (x, y)
    void drawPoint(unsigned r, unsigned g, unsigned b, unsigned x, unsigned y); 

    //Draws a rectangle from (x1, y1) to (x2, y2)
    void drawRect(unsigned r, unsigned g, unsigned b, unsigned x1, unsigned y1, unsigned x2, unsigned y2);
  
    //Get width/height
    unsigned getW() const;
    unsigned getH() const;
	
private:
   
    SDL_Texture* mandelbrot;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
};
       
#endif
