#include "start.hpp"
#include "Window.hpp"
#include "eventHandler.hpp"
#include "SDLTools.hpp"
#include "cplane.hpp"

#include <iostream>
#include <complex>

void start()
{
    const unsigned WINDOW_W = 500;
    const unsigned WINDOW_H = 500;
    const unsigned ITERS = 50;
	
    std::cout << "Starting the program...\n";

    std::cout << "Window: " << WINDOW_W << "*" << WINDOW_H << std::endl;
    std::cout << "Iterations: " << ITERS << std::endl;
	
    initGraphics();
	
    Window window(WINDOW_W, WINDOW_H, "Mandelbrot");
    eventHandler eventhandler;

    ComplexRect rect(std::complex<double>(2, 2), std::complex<double>(-2, -2));
    rect.getMandelbrot(window, ITERS);
    window.createMandelbrot(ITERS);
    
    while(!eventhandler.getQuit())
    {
	eventhandler.update();
		
	if(eventhandler.getMousePressed())
	{
	    std::cout << rect.getPoint(eventhandler.getMouseX(), eventhandler.getMouseY(), window.getW(), window.getH()) << std::endl;
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
	    rect.getMandelbrot(window, ITERS);
	    window.createMandelbrot(ITERS);
	    
	    std::cout << c1 << " ---- " << c2 << std::endl; 
	}
		
	window.update();
	wait(50);
    } 
	
    window.~Window();
	
    quitGraphics();
	
    std::cout << "Exiting...\n";
}
