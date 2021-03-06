#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <string>
#include <mutex>

#include "Mandelbrot.hpp"

//Class for reading input from command line
//Contains thread hackery that allows async input
class InputReader
{
	public:
		InputReader();

		//Reads input from command line
		void readConsole();

		//Closes the prompt and the thread
		void close();

		//Is the reader and thread running?
		bool running();

		//Is the reset command given
		bool getReset();

		//Is the iters command given
		int getIters();

		//Is the style command given
		int getStyle();

		//Is the status command given
		bool getStatus();

		//Is the save command given
		bool getSave();

		//Print the mandelbrot status in a controlled manner
		void printStatus(const Mandelbrot &mandelbrot);

	private:

		// For communication
		int iters;
		int style;
		bool reset;
		bool save;
		bool status;

		//For internal operation
		bool _quit;
		bool _running;
		std::string _input;
		std::mutex _mutex;

		//Reads from std::cin and forwards writes to the internal string buffer
		void _readstdin();
};

//Global input reader
extern InputReader glbInputReader;

#endif
