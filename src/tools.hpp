#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <complex>

//Checks if the file exists
bool fileExists(std::string filename);

//Write complex coordinates to a file
void writeToFile(std::string filename, std::complex<double> topright, std::complex<double> bottomleft);

//Read complex coordinates from a file
void readFromFile(std::string filename, std::complex<double> &topright, std::complex<double> &bottomleft);

//Generates a file name for the Mandelbrot image
std::string genFileName();

#endif
