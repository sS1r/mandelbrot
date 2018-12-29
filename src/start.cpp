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


const unsigned UPDATE_RATE = 60; //This is also the FPS

const unsigned WINDOW_W = 500;
const unsigned WINDOW_H = 500;
const char* WINDOW_TITLE = "Mandelbrot";

const unsigned DEFAULT_ITERS = 50;
const std::complex<double> DEFAULT_TOPRIGHT(0.8, 1.2);
const std::complex<double> DEFAULT_BOTTOMLEFT(-1.6, -1.2);

static Window window;
static eventHandler eventhandler;
static ComplexRect rect(DEFAULT_TOPRIGHT, DEFAULT_BOTTOMLEFT);
unsigned iters = DEFAULT_ITERS;

void start()
{
	std::cout << "Starting mandelbrot..." << std::endl;
	std::cout << "Window: " << WINDOW_W << "*" << WINDOW_H << std::endl;
	std::cout << std::endl;

	initGraphics();
	atexit(quitGraphics);

	window.init(WINDOW_W, WINDOW_H, WINDOW_TITLE);

	std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), iters);
	window.createMandelbrot(mandelbrotdata);

	std::thread inputreader(&InputReader::readConsole, &glbInputReader);
	inputreader.detach();

	bool quit = false;
	unsigned timer = getTicks();

	while(!quit)
	{
		getInput();
		quit = update();
		render();

		while(getTicks() - timer < 1000.0f / UPDATE_RATE)
		{
			wait(1000.0f / UPDATE_RATE * 0.2f);
		}
		timer = getTicks();
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

		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), iters);
		window.createMandelbrot(mandelbrotdata);
	}

	if(eventhandler.decreaseIters())
	{
		iters -= 10;
		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), iters);
		window.createMandelbrot(mandelbrotdata);
	}
	else if(eventhandler.increaseIters())
	{
		iters += 10;
		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), iters);
		window.createMandelbrot(mandelbrotdata);
	}

	if(glbInputReader.getReset())
	{
		rect.update(DEFAULT_TOPRIGHT, DEFAULT_BOTTOMLEFT);
		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), iters);
		window.createMandelbrot(mandelbrotdata);
	}

	int tmp_iters = glbInputReader.getIters();
	if(tmp_iters != 0)
	{
		iters = tmp_iters;
		std::vector<unsigned> mandelbrotdata = rect.getMandelbrot(window.getH(), window.getW(), iters);
		window.createMandelbrot(mandelbrotdata);
	}

	// Quit can occur either by
	// (1) A quit event (e.g. the graphics window is closed)
	// (2) Input reader stops running (e.g. quit command is received)
	return eventhandler.getQuit() || !glbInputReader.running();
}

void getInput()
{
	eventhandler.update();
}

void render()
{
	window.render();
}
