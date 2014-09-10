#include <complex>
#include <iostream>

using namespace std;

int main()
{
	for(double alpha = 0; alpha < 4; alpha+=.1) {
		std::complex<double> i(0,1);
		std::complex<double> Calpha = sqrt(1.-i/tan(alpha));
		cerr << alpha << " -> " << Calpha << endl;
	}
	return 0;
}
