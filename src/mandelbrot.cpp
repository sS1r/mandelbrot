#include <complex>

#include "mandelbrot.hpp"

unsigned mandelbrot(std::complex<double> c, unsigned maxiter)
{
	std::complex<double> z(0, 0);
	
	for(unsigned int i = 1;i <= maxiter;i++)
	{
		z = z*z + c;
		if(norm(z) >= 2)
		{
			return i;
		}
	}
	return 0;
}
