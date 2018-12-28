#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <string>
#include <mutex>
#include <atomic>

//Object for reading input from command line
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
	
	private:
	
		// For communication
		int iters;
		bool reset;
		bool terminate;
		
		//For internal operation
		bool _running;
		
		//Internal buffer and a mutex for async input hax
		std::string _input;
		std::mutex _mutex;
		
		//Reads from std::cin
		void _readstdin();
};

//Global input reader
extern InputReader glbInputReader;

#endif
