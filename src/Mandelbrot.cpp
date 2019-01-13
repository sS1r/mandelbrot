#include "Mandelbrot.hpp"

#include <thread>
#include <iostream>

Mandelbrot::Mandelbrot(std::complex<double> topright, std::complex<double> bottomleft): rect(topright, bottomleft), _mandelbrotdata(), _maxiters(50), _threads(1), _style(STYLE_HEAT)
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

void Mandelbrot::resize(std::complex<double> topright, std::complex<double> bottomleft)
{
	rect.resize(topright, bottomleft);
}

void Mandelbrot::resize(unsigned x1, unsigned y1, unsigned x2, unsigned y2, unsigned w, unsigned h)
{
	// First we define what is the top right and bottom left corner based on points (x1, y1) and (x2, y2)
	unsigned topright_x1 = x1 > x2 ? x1 : x2;
	unsigned topright_y1 = y1 < y2 ? y1 : y2;
	unsigned bottomleft_x1 = x1 < x2 ? x1 : x2;
	unsigned bottomleft_y1 = y1 > y2 ? y1 : y2;

	// Then we set the corner points and resize
	std::complex<double> topright = rect.getPoint(topright_x1, topright_y1, w, h);
	std::complex<double> bottomleft = rect.getPoint(bottomleft_x1, bottomleft_y1, w, h);

	resize(topright, bottomleft);
}

void Mandelbrot::setIters(unsigned maxiters)
{
	_maxiters = maxiters;
}

void Mandelbrot::setThreads(unsigned threads)
{
	_threads = threads;
}

void Mandelbrot::setStyle(RenderStyle style)
{
	_style = style;
}

unsigned Mandelbrot::getIters() const
{
	return _maxiters;
}

unsigned Mandelbrot::getThreads() const
{
	return _threads;
}

Mandelbrot::RenderStyle Mandelbrot::getStyle() const
{
	return _style;
}

std::vector<unsigned> Mandelbrot::getMandelbrot(unsigned W, unsigned H)
{
	_mandelbrotdata.clear();
	_mandelbrotdata.resize(H*W);

	std::vector<std::thread> thread_v;

	//Loop for thread running mandelbrot
	auto mandelbrotloop = [W, H, this](unsigned start, unsigned end) -> void
	{
		for(unsigned i = start;i < end;i++)
		{
			unsigned x = i % W;
			unsigned y = i / W;
			unsigned iters = Mandelbrot::mandelbrot(rect.getPoint(x, y, W, H), _maxiters);
			_mandelbrotdata[i] = iters;
		}
	};

	unsigned start = 0;
	unsigned end = 0;
	unsigned length = H*W / _threads;

	for(unsigned i = 0;i < _threads;i++)
	{
		if(i != _threads - 1)
		{
			end = start + length;
		}
		else
		{
			end = H*W;
		}
		thread_v.push_back(std::thread(mandelbrotloop, start, end));
		start = end;
	}

	for(auto &t : thread_v)
	{
		t.join();
	}

	return _mandelbrotdata;
}

std::ostream& operator<<(std::ostream &out, const Mandelbrot &m)
{
	out << "Iterations: " << m.getIters() << std::endl;
	out << "Threads: " << m.getThreads() << std::endl;
	out << m.rect;

	return out;
}
