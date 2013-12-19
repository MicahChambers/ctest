#include <cmath>
#include "plot.h"

using namespace std;

double foo(double x)
{
	return pow(sin(x)+cos(x), 4);
}

int main(int argc, char** argv)
{
	if(argc != 5) 
		return -1;

	double(*f1)(double) = sin;
	double(*f2)(double) = cos;
	double(*f3)(double) = foo;

	double xrange[2] = {-10, 10};
	writePlot(argv[1], sin, xrange, .1);
	writePlot(argv[2], sin, xrange, .01);
	writePlot(argv[3], cos, xrange, .01, 100);
	writePlot(argv[4], xrange, .01, f1, f2, f3);

}

