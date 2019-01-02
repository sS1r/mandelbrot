#include "cplane.hpp"
#include "Mandelbrot.hpp"

#include <thread>
#include <iostream>

ComplexRect::ComplexRect(std::complex<double> topright, std::complex<double> bottomleft): topright(topright), bottomleft(bottomleft)
{
	//Empty
}

ComplexRect::~ComplexRect()
{
	//Empty
}

std::complex<double> ComplexRect::getPoint(unsigned x, unsigned y, unsigned w, unsigned h) const
{
	if(x > w || y > h)
	{
		throw "ComplexRect::getPoint: pixel point (x, y) outside pixel plane.";
	}
	if(w == 0 || h == 0)
	{
		throw "ComplexRect::getPoint: pixel plane width or height zero.";
	}

	double width = (topright - bottomleft).real();
	double height = (topright - bottomleft).imag();

	double real = topright.real() - width * (double(w - x) - 0.5) / double(w);
	double imag = topright.imag() - height * (double(h - y) - 0.5) / double(h);

	return std::complex<double>(real, imag);
}

std::vector<unsigned> ComplexRect::getMandelbrot(unsigned W, unsigned H, unsigned maxiters, int threads) const
{

	std::vector<unsigned> ret;
	ret.resize(H*W, 0);

	std::vector<std::thread> thread_v;

	//Loop for thread running mandelbrot
	auto mandelbrotloop = [W, H, maxiters, this](unsigned start, unsigned end, std::vector<unsigned>& ret) -> void
	{
		for(unsigned i = start;i < end;i++)
		{
			unsigned x = i % W;
			unsigned y = i / W;
			unsigned iters = Mandelbrot::mandelbrot(getPoint(x, y, W, H), maxiters);
			ret[i] = iters;
		}
	};

	unsigned start = 0;
	unsigned end = 0;
	unsigned length = H*W / threads;
	for(int i = 0;i < threads;i++)
	{
		if(i != threads - 1)
		{
			end = start + length;
		}
		else
		{
			end = H*W;
		}
		thread_v.push_back(std::thread(mandelbrotloop, start, end, std::ref(ret)));
		start = end;
	}

	for(auto &t : thread_v)
	{
		t.join();
	}

	return ret;

	/*for(unsigned i = 0;i < W;i++)
	{
		for(unsigned j = 0;j < H;j++)
		{
			unsigned iters = mandelbrot(getPoint(i, j, W, H), maxiters);
			ret[i + j*W] =	iters;
		}
	}*/

}

void ComplexRect::update(std::complex<double> top_right, std::complex<double> bottom_left)
{
	topright = top_right;
	bottomleft = bottom_left;
}
