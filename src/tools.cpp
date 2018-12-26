#include <ctime>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

#include "tools.hpp"

bool fileExists(std::string filename)
{
	std::ifstream file(filename);
	if(file)
	{
		return true;
	}
	return false;
}

void writeToFile(std::string filename, std::complex<double> topright, std::complex<double> bottomleft)
{
	std::ifstream checkfile(filename);
	if(!checkfile)
	{
		std::ofstream file(filename);
		if(file)
		{
			file << topright.real() << std::endl;
			file << topright.imag() << "i"	<< std::endl;
			file << std::endl;

			file << bottomleft.real() << std::endl;
			file << bottomleft.imag() << "i" << std::endl;
			file << std::endl;
		}
	}
}

void readFromFile(std::string filename, std::complex<double> &topright, std::complex<double> &bottomleft)
{
	std::ifstream file(filename);
	unsigned count = 0;

	while(file)
	{
		std::string s;
		file >> s;

		if(!s.empty())
		{
			double number = std::stod(s);
			switch(count)
			{
				case 0:
					topright.real(number);
				case 1:
					topright.imag(number);
				case 2:
					bottomleft.real(number);
				case 3:
					bottomleft.imag(number);
			}
			count++;
		}
	}
}

std::string genFileName()
{
	//Get local time
	time_t rawtime = 0;
	time(&rawtime);

	//Convert the time into a tm structure
	struct tm* timeinfo;
	timeinfo = localtime(&rawtime);

	//Extract time values
	int year = timeinfo->tm_year + 1900;
	int mon = timeinfo->tm_mon + 1;
	int day = timeinfo->tm_mday;
	int hour = timeinfo->tm_hour;
	int min = timeinfo->tm_min;

	//Generate timestamp string
	char timestamp[13];
	sprintf(timestamp, "%02d%02d%02d_%02d%02d", year, mon, day, hour, min);

	//Constant filename string variables
	const char* end = "Mandelbrot";
	const char* fileext = ".png";

	//Create base filename
	std::string filenameBase = timestamp + std::string("_") + end;
	std::string filename = filenameBase + fileext;

	//Find a usable filename if the file already exists
	unsigned count = 0;
	std::ostringstream oss;

	while(fileExists(filename))
	{
		oss << filenameBase << "_" << std::setw(4) << std::setfill('0') << count << fileext;
		filename = oss.str();
		count++;
		oss.str("");
	}

	//Return the correct filename
	return filename;
}
