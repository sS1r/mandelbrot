#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

//Returns 0  if complex number [real] + i*[imag] is part of the Mandelbrot set, otherwise returns the number of iterations used (from 1 to maxiter)
unsigned mandelbrot(std::complex<double> c, unsigned maxiter); 

#endif
