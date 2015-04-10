#include <cmath>
#include <limits>
#include <cstdlib>

#include <iostream>
using namespace std;


/**
 * @brief Returns the inverse of the error function, which is useful for
 * gaussian CDF
 *
 * @param z Values in [-1,1], where -1 -> -inf, 1 -> inf
 *
 * @return Inverse error value
 */
double erfinv(double z)
{
	if(z < -1 || z > 1) return std::numeric_limits<double>::signaling_NaN();
	if(z == -1) return -std::numeric_limits<double>::infinity();
	if(z == 1) return std::numeric_limits<double>::infinity();

	const size_t ORDER = 10;
	double Chist[ORDER];
	double ret = 0;
	double ck = 0;
	Chist[0] = 1;
	Chist[1] = 1;
	for(size_t kk=2; kk<ORDER; kk++) {
		ck = 0;
		for(size_t mm=0; mm<kk; mm++)
			ck += Chist[mm]*Chist[kk-1-mm]/((mm+1)*(2*mm+1));
		Chist[kk] = ck;
	}

	for(size_t kk=0; kk<ORDER; kk++)
		ret += pow(z*sqrt(M_PI)/2., 2*kk+1)*Chist[kk]/(2*kk+1);

	return ret;
}

int main()
{
	const size_t TESTS = 20;
	for(size_t ii=0; ii<TESTS; ii++) {
		double v = 2*(rand()/(double)RAND_MAX-0.5);
		double iv = erfinv(v);
		double fiv = erf(iv);
		cerr<<"v: "<<v <<", iv: "<<iv<<", fiv: "<<fiv<<endl;
	}
}
