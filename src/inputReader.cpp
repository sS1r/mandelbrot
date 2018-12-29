#include "inputReader.hpp"

#include <iostream>
#include <sstream>
#include <thread>


InputReader glbInputReader;

InputReader::InputReader(): iters(0), reset(false), _quit(false), _running(false)
{

}

void InputReader::readConsole()
{
	_running = true;

	std::cout << "Type 'help' for list of commands" << std::endl;
	std::cout << std::endl;

	while(!_quit)
	{
		std::string cmd;
		std::stringstream inputss;

		_mutex.lock();
		_input.clear();
		_mutex.unlock();

		std::cout << "Mandelbrot> ";

		// Block for running the input reader thread for async input
		{
			// Start the thread
			std::thread inputreader(&InputReader::_readstdin, this);
			inputreader.detach();

			// Wait until some input is received
			while(_input.empty())
			{
				//sleep_for seems to give a better performance than yield
				//std::this_thread::yield();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}

		inputss.str(_input);
		inputss >> cmd;

		if(cmd == "help")
		{
			std::cout << "help -- show this help and exit" << std::endl;
			std::cout << "status -- view various info" << std::endl;
			std::cout << "iters N -- set maximum iterations to N" << std::endl;
			std::cout << "reset -- reset to original zoom/position" << std::endl;
			std::cout << "quit -- quits the program" << std::endl;
			std::cout << "save -- saves image with default filename" << std::endl;
		}
		else if(cmd == "status")
		{

		}
		else if(cmd == "iters")
		{
			int _iters;
			inputss >> _iters;
			if(_iters <= 0)
			{
				std::cout << "Number of iters must be greater than zero" << std::endl;
			}
			else
			{
				iters = _iters;
			}
		}
		else if(cmd == "reset")
		{
			reset = true;
		}
		else if(cmd == "quit")
		{
			_quit = true;
		}
		else
		{
			std::cout << "Command '" << cmd << "' is not valid!" << std::endl;
		}
	}

	std::cout << std::endl << std::endl;
	std::cout << "Closing the prompt..." << std::endl;

	_running = false;
}

void InputReader::close()
{
	_mutex.lock();
	_input = "quit";
	_mutex.unlock();
}

bool InputReader::running()
{
	return _running;
}

bool InputReader::getReset()
{
	if(reset)
	{
		reset = false;
		return true;
	}
	return false;
}

int InputReader::getIters()
{
	if(iters != 0)
	{
		int ret = iters;
		iters = 0;
		return ret;
	}
	return 0;
}

void InputReader::_readstdin()
{
	std::string in;
	std::getline(std::cin, in);
	if(in.empty())
	{
		in = "-";
	}

	_mutex.lock();
	_input = in;
	_mutex.unlock();
}
