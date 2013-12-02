#include <iostream>
#include <cmath>

using std::cerr;
using std::endl;

double lanczosKern(double x, double a)
{
	const double PI = acos(-1);
	if(x == 0)
		return 1;
	return a*sin(PI*x)*sin(PI*x/a)/(PI*PI*x*x);
}

int main()
{
	for(int a = 1 ; a < 4; a ++) {
		cerr << "a: " << a << endl;
		for(double ii = -a; ii <= a; ii+=.5) {
			cerr << "\t" << ii << ", " << lanczosKern(ii, a) << endl;
		}
		cerr << endl;
	}
}
