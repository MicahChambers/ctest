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

	double a = 1.2;
	std::complex<double> b(1.2,1);
	std::complex<double> c(1.2,0);
	cerr << "Complex Conjugate of " << a << "=" << std::conj(a) << endl;
	cerr << "Complex Conjugate of " << b << "=" << std::conj(b) << endl;
	cerr << "Complex Conjugate of " << c << "=" << std::conj(c) << endl;
	return 0;
}
