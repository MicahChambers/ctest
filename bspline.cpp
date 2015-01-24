#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


/**
 * @brief 3rd order B-Spline, radius 2 [-2,2]
 *
 * @param x Distance from center
 *
 * @return Weight
 */
	inline
double B3kernPow(double x)
{
	switch((int)floor(x)) {
		case -2:
			return pow(2 + x,3)/6.;
		case -1:
			return (4 - 3*pow(x,2)*(2 + x))/6.;
		case 0:
			return (4 + 3*(-2 + x)*pow(x,2))/6.;
		case 1:
			return -pow(-2 + x,3)/6.;
		default:
			return 0;
	}
}

	inline
double B3kern(double x)
{
	switch((int)floor(x)) {
		case -2:
			return 4./3. + 2.*x + x*x + x*x*x/6.;
		break;
		case -1:
			return 2./3. - x*x - x*x*x/2.;
		break;
		case 0:
			return 2./3. - x*x + x*x*x/2.;
		break;
		case 1:
			return 4./3. - 2*x + x*x - x*x*x/6.;
		break;
		default:
			return 0;
		break;
	}
}

/**
 * @brief 3rd order B-Spline, variable radius (w)
 *
 * @param x Distance from center
 * @param r Radius
 *
 * @return Weight
 */
	inline
double B3kernDiv(double x, double r)
{
	return B3kern(x*2/r)*2/r;
}

int main()
{
	const int COUNT = 1000000;
	const int ndim = 3;

	cerr << "Basic Cache...";
	vector<double> cache(5*ndim);
	clock_t c = clock();

	for(size_t cc=0; cc<COUNT; cc++) {
		int ind[ndim];
		double v = 23;
		for(size_t dd=0; dd<ndim; dd++) {
			for(int ii=-2; ii<=2; ii++){
				cache[dd*5 + ii+2] = B3kern(ii+rand()/(2.*RAND_MAX));
			}
		}
		for(ind[0]=-2; ind[0]<2; ind[0]++) {
			for(ind[1]=-2; ind[0]<2; ind[0]++) {
				for(ind[2]=-2; ind[0]<2; ind[0]++) {
					double w = 1;
					for(size_t dd=0; dd<ndim; dd++)
						w *= cache[dd*5 + ind[dd]];
					v *= w;
				}
			}
		}
	}
	c = clock() - c;
	cerr << "Time: " << c << endl;

	cerr << "Non-Cached...";
	c = clock();
	for(size_t cc=0; cc<COUNT; cc++) {
		int ind[ndim];
		double v = 23;
		for(ind[0]=-2; ind[0]<2; ind[0]++) {
			for(ind[1]=-2; ind[0]<2; ind[0]++) {
				for(ind[2]=-2; ind[0]<2; ind[0]++) {
					double w = 1;
					for(size_t dd=0; dd<ndim; dd++)
						w *= B3kern(ind[dd]+rand()/(2.*RAND_MAX));
					v *= w;
				}
			}
		}
	}
	c = clock() - c;
	cerr << "Time: " << c << endl;

	cerr << "Power Cache...";
	c = clock();

	for(size_t cc=0; cc<COUNT; cc++) {
		int ind[ndim];
		double v = 23;
		for(size_t dd=0; dd<ndim; dd++) {
			for(int ii=-2; ii<=2; ii++){
				cache[dd*5 + ii+2] = B3kernPow(ii+rand()/(2.*RAND_MAX));
			}
		}
		for(ind[0]=-2; ind[0]<2; ind[0]++) {
			for(ind[1]=-2; ind[0]<2; ind[0]++) {
				for(ind[2]=-2; ind[0]<2; ind[0]++) {
					double w = 1;
					for(size_t dd=0; dd<ndim; dd++)
						w *= cache[dd*5 + ind[dd]];
					v *= w;
				}
			}
		}
	}
	c = clock() - c;
	cerr << "Time: " << c << endl;

	cerr << "Power Non-Cached...";
	c = clock();
	for(size_t cc=0; cc<COUNT; cc++) {
		int ind[ndim];
		double v = 23;
		for(ind[0]=-2; ind[0]<2; ind[0]++) {
			for(ind[1]=-2; ind[0]<2; ind[0]++) {
				for(ind[2]=-2; ind[0]<2; ind[0]++) {
					double w = 1;
					for(size_t dd=0; dd<ndim; dd++)
						w *= B3kernPow(ind[dd]+rand()/(2.*RAND_MAX));
					v *= w;
				}
			}
		}
	}
	c = clock() - c;
	cerr << "Time: " << c << endl;

	cerr << "Div Cache...";
	c = clock();

	for(size_t cc=0; cc<COUNT; cc++) {
		int ind[ndim];
		double v = 23;
		for(size_t dd=0; dd<ndim; dd++) {
			for(int ii=-2; ii<=2; ii++){
				cache[dd*5 + ii+2] = B3kernDiv(ii+rand()/(2.*RAND_MAX),3);
			}
		}
		for(ind[0]=-2; ind[0]<2; ind[0]++) {
			for(ind[1]=-2; ind[0]<2; ind[0]++) {
				for(ind[2]=-2; ind[0]<2; ind[0]++) {
					double w = 1;
					for(size_t dd=0; dd<ndim; dd++)
						w *= cache[dd*5 + ind[dd]];
					v *= w;
				}
			}
		}
	}
	c = clock() - c;
	cerr << "Time: " << c << endl;

	cerr << "Non-Cached...";
	c = clock();
	for(size_t cc=0; cc<COUNT; cc++) {
		int ind[ndim];
		double v = 23;
		for(ind[0]=-2; ind[0]<2; ind[0]++) {
			for(ind[1]=-2; ind[0]<2; ind[0]++) {
				for(ind[2]=-2; ind[0]<2; ind[0]++) {
					double w = 1;
					for(size_t dd=0; dd<ndim; dd++)
						w *= B3kernDiv(ind[dd]+rand()/(2.*RAND_MAX), 3);
					v *= w;
				}
			}
		}
	}
	c = clock() - c;
	cerr << "Time: " << c << endl;
}
