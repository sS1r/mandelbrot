#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

bool mandelbrot(double real, double imag, unsigned iter); //Returns true if complex number [real] + i*[imag] is part of the Mandelbrot set, otherwise returns false

bool mandelbrot(std::complex<double> c, unsigned iter);

#endif
