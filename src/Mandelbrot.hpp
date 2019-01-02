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

		// Resize by raw complex coordinates
		void resize(std::complex<double> topright, std::complex<double> bottomleft);

		// Resize by two pixel plane points forming a rectangle
		void resize(unsigned x1, unsigned y1, unsigned x2, unsigned y2, unsigned w, unsigned h);

		// Set other values
		void setIters(unsigned iters);
		void setStyle(RenderStyle style);

		// Fundamental mandelbrot calculation function
		static unsigned mandelbrot(std::complex<double> c, unsigned maxiter);

		// Computes the Mandelbrot data vector for a W*H sized window
		std::vector<unsigned> getMandelbrot(unsigned W, unsigned H);

	private:

		// The current complex plane
		ComplexRect rect;

		// Mandelbrot information
		std::vector<unsigned> _mandelbrotdata;

		// Max iterations in the mandelbrot calculations
		unsigned _maxiters;

		// Thread count for the mandelbrot calculation
		unsigned _threads;

		// Rendering style
		RenderStyle _style;
};

#endif
