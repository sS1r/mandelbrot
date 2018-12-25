#include "start.hpp"
#include "Window.hpp"
#include "eventHandler.hpp"
#include "SDLTools.hpp"
#include "cplane.hpp"

#include <iostream>
#include <complex>
#include <cstdlib>

void start()
{
    const unsigned WINDOW_W = 500;
    const unsigned WINDOW_H = 500;
    const char* WINDOW_TITLE = "Mandelbrot";
    const unsigned ITERS = 50;
	
    std::cout << "Starting the program..." << std::endl;
    std::cout << "Window: " << WINDOW_W << "*" << WINDOW_H << std::endl;
    std::cout << "Iterations: " << ITERS << std::endl;
	
    initGraphics();
    atexit(quitGraphics);
	
    Window window(WINDOW_W, WINDOW_H, WINDOW_TITLE);
    eventHandler eventhandler;

    ComplexRect rect(std::complex<double>(2, 2), std::complex<double>(-2, -2));
    std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), ITERS);
	window.createMandelbrot(mandelbrotdata);
	    
    while(!eventhandler.getQuit())
    {
		eventhandler.update();
			
		if(eventhandler.getMousePressed())
		{
			//std::cout << rect.getPoint(eventhandler.getMouseX(), eventhandler.getMouseY(), window.getW(), window.getH()) << std::endl;
		}
	
		window.clear();	
		window.drawMandelbrot();
		
		if(eventhandler.getMousePressed())
		{
			window.drawRect(0, 0, 255, eventhandler.getDragX(), eventhandler.getDragY(), eventhandler.getMouseX(), eventhandler.getMouseY());
		}
			
		if(eventhandler.getMouseReleased())
		{
			std::complex<double> c1 = rect.getPoint(eventhandler.getDragX(), eventhandler.getDragY(), window.getW(), window.getH());
			std::complex<double> c2 = rect.getPoint(eventhandler.getMouseX(), eventhandler.getMouseY(), window.getW(), window.getH());

			rect.update(c2, c1);
			
			mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), ITERS);
			window.createMandelbrot(mandelbrotdata);
			
			std::cout << c1 << " ---- " << c2 << std::endl; 
		}
			
		window.update();
		wait(50);
    } 
	
    std::cout << "Exiting..." << std::endl;
}
