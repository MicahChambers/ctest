#include <iostream>
#include "plot.h"

using namespace std;

/* Linear Kernel Sampling */
double linKern(double x, double a)
{
	return fabs(1-fmin(1,fabs(x/a)))/a;
}

/* Linear Kernel Sampling */
double dLinKern(double x, double a)
{
	if(x < -a || x > a)
		return 0;
	if(x < 0)
		return 1/a;
	else
		return -1/a; 
}

int main()
{
	double npoints = 100;
	std::vector<double> x(npoints);
	std::vector<double> y(npoints);

	for(int64_t ii=0 ; ii<npoints; ii++) {
		x[ii] = (ii-npoints/2.)/(npoints/4.);
	}

	// unit width
	for(int64_t ii=0 ; ii<npoints; ii++) {
		y[ii] = linKern(x[ii], 1);
	}

	writePlot("width1.tga", x, y);
	for(int64_t ii=0 ; ii<npoints; ii++) {
		y[ii] = dLinKern(x[ii], 1);
	}

	writePlot("dwidth1.tga", x, y);
	
	// 1.5 width
	for(int64_t ii=0 ; ii<npoints; ii++) {
		y[ii] = linKern(x[ii], 1.5);
	}
	writePlot("widthextra.tga", x, y);
	
	for(int64_t ii=0 ; ii<npoints; ii++) {
		y[ii] = dLinKern(x[ii], 1.5);
	}
	writePlot("dwidthextra.tga", x, y);
	
	// half width
	for(int64_t ii=0 ; ii<npoints; ii++) {
		y[ii] = linKern(x[ii], 0.5);
	}
	writePlot("widthhalf.tga", x, y);
	
	for(int64_t ii=0 ; ii<npoints; ii++) {
		y[ii] = dLinKern(x[ii], 0.5);
	}
	writePlot("dwidthhalf.tga", x, y);

	// radius 1
	cerr << "Radius 1 sums " << endl;
	for(size_t ii=0; ii < 10; ii++) {
		double point = 4*(double)rand()/(double)RAND_MAX-2;

		double sum = 0;
		for(int64_t rr=round(point)-1; rr<=round(point)+1; rr++) {
			sum += linKern(rr-point, 1);
		}
		cerr << sum << endl;
	}
	
	// radius 2
	cerr << "Radius 2 sums " << endl;
	for(size_t ii=0; ii < 10; ii++) {
		double point = 4*(double)rand()/(double)RAND_MAX-2;

		double sum = 0;
		for(int64_t rr=round(point)-2; rr<=round(point)+2; rr++) {
			sum += linKern(rr-point, 2);
		}
		cerr << sum << endl;
	}
	
}
