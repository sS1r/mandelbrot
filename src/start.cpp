#include "start.hpp"
#include "Window.hpp"
#include "eventHandler.hpp"
#include "SDLTools.hpp"
#include "cplane.hpp"
#include "inputReader.hpp"

#include <iostream>
#include <complex>
#include <cstdlib>
#include <thread>

const unsigned WINDOW_W = 500;
const unsigned WINDOW_H = 500;
const char* WINDOW_TITLE = "Mandelbrot";
unsigned ITERS = 50;

static Window window;
static eventHandler eventhandler;
static ComplexRect rect(std::complex<double>(0.8, 1.2), std::complex<double>(-1.6, -1.2));

void start()
{
	std::cout << "Starting the program..." << std::endl;
	std::cout << "Window: " << WINDOW_W << "*" << WINDOW_H << std::endl;
	std::cout << "Iterations: " << ITERS << std::endl;

	initGraphics();
	atexit(quitGraphics);

	window.init(WINDOW_W, WINDOW_H, WINDOW_TITLE);

	std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), ITERS);
	window.createMandelbrot(mandelbrotdata);

	std::thread inputreader(&InputReader::readConsole, &glbInputReader);
	inputreader.detach();

	bool quit = false;
	while(!quit)
	{
		getInput();
		quit = update();
		render();

		wait(50);
	}

	glbInputReader.close();
	while(glbInputReader.running())
	{
		wait(10);
	}
	
	std::cout << "Exiting..." << std::endl;
}

bool update()
{
	if(eventhandler.getMousePressed())
	{
		window.createRect(eventhandler.getDragX(), eventhandler.getDragY(), eventhandler.getMouseX(), eventhandler.getMouseY());
	}
	else
	{
		window.hideRect();
	}

	if(eventhandler.getMouseReleased())
	{
		std::complex<double> c1 = rect.getPoint(eventhandler.getDragX(), eventhandler.getDragY(), window.getW(), window.getH());
		std::complex<double> c2 = rect.getPoint(eventhandler.getMouseX(), eventhandler.getMouseY(), window.getW(), window.getH());

		rect.update(c2, c1);

		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), ITERS);
		window.createMandelbrot(mandelbrotdata);
	}
	
	if(eventhandler.decreaseIters())
	{
		ITERS -= 10;
		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), ITERS);
		window.createMandelbrot(mandelbrotdata);
	}
	else if(eventhandler.increaseIters())
	{
		ITERS += 10;
		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), ITERS);
		window.createMandelbrot(mandelbrotdata);
	}
	
	return eventhandler.getQuit();
}

void getInput()
{
	eventhandler.update();
}

void render()
{
	window.render();
}
