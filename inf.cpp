#include <cmath>
#include <iostream>
#include <limits>
#include <complex>

using namespace std;

int main()
{
	float fone = 1.0/0.0;
	float ftwo = INFINITY;
	cout << fone << endl << ftwo << endl;
	fone = -1.0/0.0;
	ftwo = -INFINITY;
	cout << fone << endl << ftwo << endl;

	double done = 1.0/0.0;
	double dtwo = INFINITY;
	cout << done << endl << dtwo << endl;
	done = -1.0/0.0;
	dtwo = -INFINITY;
	cout << done << endl << dtwo << endl;

	int a = std::numeric_limits<int>::infinity();
	double b = std::numeric_limits<double>::infinity();
	std::complex<double> c = std::numeric_limits<std::complex<double>>::infinity();

	cerr << a << " vs " << b << " vs " << c << endl;
}
