#include "Mandelbrot.hpp"

Mandelbrot::Mandelbrot(std::complex<double> topright, std::complex<double> bottomleft): rect(topright, bottomleft), _mandelbrotdata(), _iters(50), _threads(1), _style(STYLE_HEAT)
{

}

unsigned Mandelbrot::mandelbrot(std::complex<double> c, unsigned maxiter)
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
