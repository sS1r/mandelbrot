#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <complex>

#include "cplane.hpp"

class Mandelbrot
{
	public:

		// How the plot will be rendered
		enum RenderStyle
		{
			STYLE_HEAT = 1,
			STYLE_COLD = 2
		};

		// Construct new
		Mandelbrot(std::complex<double> topright, std::complex<double> bottomleft);

		// Set different values
		setPosition(std::complex<double> _topright, std::complex<double> _bottomleft);
		setIters(unsigned iters);
		setStyle(RenderStyle style);

		// Fundamental mandelbrot calculation function
		static unsigned mandelbrot(std::complex<double> c, unsigned maxiter);

	private:

		// The current complex plane
		ComplexRect rect;

		// Mandelbrot information
		std::vector<unsigned> _mandelbrotdata;

		// Max iterations in the mandelbrot calculations
		unsigned _iters;

		// Thread count for the mandelbrot calculation
		unsigned _threads;

		// Rendering style
		RenderStyle _style;
};

#endif
