#ifndef CPLANE_HPP
#define CPLANE_HPP

#include <complex>

//This class implements a rectangular piece on a complex plane
class ComplexRect
{
public:
	ComplexRect(std::complex<double> topright, std::complex<double> bottomleft); //Ctor
	~ComplexRect(); //Dtor

	//Returns a complex point on this plane at pixel coordinates (x,y) when the plane is stretched to fit a h*w pixel plane
	std::complex<double> getPoint(unsigned x, unsigned y, unsigned w, unsigned h);

	//Updates the rect's size
	void update(std::complex<double> top_right, std::complex<double> bottom_left);
private:
	std::complex<double> topright;
	std::complex<double> bottomleft;
};

#endif
