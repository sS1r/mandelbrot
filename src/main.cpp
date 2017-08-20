#include <iostream>
#include <string>

#include "start.hpp"

int main(int argc, char* argv[])
{
	try
	{
		start();
	}
	catch(std::string s)
	{
		std::cout << "Error occurred: " << s << std::endl;
	}
	catch(const char* s)
	{
		std::cout << "Error occurred: " << s << std::endl;
	}
	catch(...)
	{
		std::cout << "Unknown error occurred" << std::endl;
	}
  
	return 0;
}
