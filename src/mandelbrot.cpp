#include <complex>

#include "mandelbrot.hpp"

bool mandelbrot(double real, double imag, unsigned iter)
{
	std::complex<double> c(real, imag);
	std::complex<double> z1(0, 0);
	std::complex<double> z2(0, 0);
	
	for(unsigned int i = 0;i < iter;i++)
	{
		z2 = z1*z1 + c;
		if(norm(z2) >= 2)
		{
			return false;
		}
		z1 = z2;
	}
	return true;
}

bool mandelbrot(std::complex<double> c, unsigned iter)
{
	std::complex<double> z1(0, 0);
	std::complex<double> z2(0, 0);
	
	for(unsigned int i = 0;i < iter;i++)
	{
		z2 = z1*z1 + c;
		if(norm(z2) >= 2)
		{
			return false;
		}
		z1 = z2;
	}
	return true;
}
