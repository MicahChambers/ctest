#include "plot.h"
#include "tga.h"

#include <cmath>
#include <cassert>

/**
 * @brief Creates a TGA file with the x and y values plotted from x and y
 *
 * @param filename	output file name *.tga
 * @param x			x values of each point
 * @param y			y values of each point
 */
void writePlot(std::string filename, const std::vector<double>& x, 
		const std::vector<double>& y, int ysize)
{
	int XSIZE = x.size();
	double yres = 0;

	double xrange[2] = {x[0], x[0]};
	double yrange[2] = {y[0], y[0]};

	//find min and max values of x and y, 
	//also find the maximum distance between adjacent values of y
	for(int ii = 1 ; ii < x.size(); ii++) {
		xrange[0] = std::min(x[ii], xrange[0]);
		xrange[1] = std::max(x[ii], xrange[1]);
		yrange[0] = std::min(y[ii], yrange[0]);
		yrange[1] = std::max(y[ii], yrange[1]);
		yres = std::max(yres, y[ii]-y[ii-1]);
	}
	
	//set the ysize so that there are no gaps in the line
	if(ysize < 0) {
		ysize = (yrange[1]-yrange[0])/yres;
	}

	std::vector<double> image(x.size()*ysize, 0);
	for(int ii = 0 ; ii < x.size(); ii++) {
		int ypos = ysize*(y[ii]-yrange[0])/(yrange[1]-yrange[0]+.1);
		image[ypos*x.size() + ii] = 1;
	}

	writeTGA(filename, image, ysize, XSIZE); 
}

/**
 * @brief Creates a TGA file with the x and y values plotted based
 * on the input function.
 *
 * @param filename	output file name *.tga
 * @param xrange	min and max x values (start and stop points)
 * @param xres		resolution (density) of xpoints. Ouptut size is range/res
 */
void writePlot(std::string filename, double(*f)(double), 
		double xrange[2], double xres, int ysize)
{
	
	std::vector<double> x((xrange[1]-xrange[0])/xres, 0);
	std::vector<double> y(x.size(), 0);

	double xv = xrange[0];
	for(int ii = 0 ; ii < x.size(); ii++) {
		y[ii] = f(xv);
		x[ii] = xv;

		xv += xres;
	}

	writePlot(filename, x, y, ysize);
}
