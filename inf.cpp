#include <cmath>
#include <iostream>

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

}
