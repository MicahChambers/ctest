#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double a = NAN;
	double b = 1;

	cerr << a << " vs " << b << endl;
	cerr << a << "==" << b << "=" << (a==b) << endl;
	cerr << a << "!=" << b << "=" << (a!=b) << endl;
	cerr << a << "<=" << b << "=" << (a<=b) << endl;
	cerr << a << "<"  << b << "=" << (a<b ) << endl;
	cerr << a << ">"  << b << "=" << (a>b ) << endl;
	cerr << a << ">=" << b << "=" << (a>=b) << endl;

	return 0;
}
