#ifndef PLOT_H
#define PLOT_H

#include "tga.h"
#include <vector>
#include <list>
#include <cmath>
#include <string>

/**
 * @brief Creates a TGA file with the x and y values plotted from x and y
 *
 * @param filename	output file name *.tga
 * @param x			x values of each point
 * @param y			y values of each point
 */
void writePlot(std::string filename, const std::vector<double>& x, 
		const std::vector<double>& y, int ysize = -1);

/**
 * @brief Creates a TGA file with the x and y values plotted based
 * on the input function.
 *
 * @param filename	output file name *.tga
 * @param xrange	min and max x values (start and stop points)
 * @param xres		resolution (density) of xpoints. Ouptut size is range/res
 */
void writePlot(std::string filename, double(*f)(double), 
		double xrange[2], double xres, int ysize = -1);

namespace NPLINTERNAL {
template <typename T>
void writePlot(double xmin, double xres, int xsize, 
		std::list<std::vector<double>>* xf, std::list<std::vector<double>>* yf,
		T arg)
{
	xf->push_back(std::vector<double>());
	yf->push_back(std::vector<double>());
	xf->back().resize(xsize);
	yf->back().resize(xsize);

	double xval = xmin;
	for(int ii = 0 ; ii < xsize; ii++) {
		yf->back()[ii] = arg(xval);
		xf->back()[ii] = xval;

		xval += xres;
	}
}

template <typename T, typename... Targs>
void writePlot(double xmin, double xres, int xsize, 
		std::list<std::vector<double>>* xf, std::list<std::vector<double>>* yf,
		T arg, Targs... Fargs)
{
	xf->push_back(std::vector<double>());
	yf->push_back(std::vector<double>());
	xf->back().resize(xsize);
	yf->back().resize(xsize);

	double xval = xmin;
	for(int ii = 0 ; ii < xsize; ii++) {
		yf->back()[ii] = arg(xval);
		xf->back()[ii] = xval;

		xval += xres;
	}

	writePlot(xmin, xres, xsize, xf, yf, Fargs...);
}
}

template <typename... Targs>
void writePlot(std::string filename, double xrange[2], double xres, Targs... Fargs)
{
	std::list<std::vector<double>> xfuncs;
	std::list<std::vector<double>> yfuncs;
	int xsize = (xrange[1]-xrange[0])/xres;

	//this fills xfuncs, yfuncs
	NPLINTERNAL::writePlot(xrange[0], xres, xsize, &xfuncs, &yfuncs, Fargs...);

	double yrange[2] = {INFINITY, -INFINITY};

	//find min and max values of x and y, 
	//also find the maximum distance between adjacent values of y
	double yres = -INFINITY;
	auto ity = yfuncs.begin();
	for( ; ity != yfuncs.end(); ity++) {
		yrange[0] = std::min((*ity)[0], yrange[0]);
		yrange[1] = std::max((*ity)[0], yrange[1]);
		for(int ii = 1 ; ii < xsize; ii++) {
			yres = std::max(yres, std::abs((*ity)[ii]-(*ity)[ii-1]));
			yrange[0] = std::min((*ity)[ii], yrange[0]);
			yrange[1] = std::max((*ity)[ii], yrange[1]);
		}
	}
	
	//set the ysize so that there are no gaps in the line
	int ysize = (yrange[1]-yrange[0])/yres;

	std::vector<double> image(xsize*ysize, 0);
	ity = yfuncs.begin();
	double brightness = 1;
	for( ; ity != yfuncs.end(); ity++) {
		for(int ii = 0 ; ii < xsize; ii++) {
			int ypos = ysize*((*ity)[ii]-yrange[0])/(yrange[1]-yrange[0]+.1);
			image[ypos*xsize + ii] = brightness;
		}
		brightness++;
	}

	writeTGA(filename, image, ysize, xsize); 
}

#endif

