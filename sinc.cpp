#include <iostream>
#include <cmath>

using std::endl;
using std::cout;

double lanczosKern(double x, double a)
{
	const double PI = acos(-1);
	if(x == 0)
		return 1;
	if(fabs(x) > a)
		return 0;
	return a*sin(PI*x/a)*sin(PI*x)/(PI*PI*x*x);
}

double dlanczosKern(double x, double a)
{
//	const double PI = acos(-1);
//	if(x == 0)
//		return 0;
//	if(fabs(x) > a)
//		return 0;
//	PI*cos(PI*x/a)*sin(PI*x)/(PI*PI*x*x) + 
//	PI*a*sin(PI*x/a)*cos(PI*x)/(PI*PI*x*x);
	return 0;
}

int main(int argc, char* argv[])
{
	int width = 3;
	double step = 0.01;
	if(argc == 2) {
		width = atoi(argv[1]);
		cout << "WinWidth: " << argv[1] << " (" << width << ")" << endl;
	} else if(argc == 3) {
		width = atoi(argv[1]);
		step = atof(argv[2]);
		cout << "WinWidth: " << argv[1] << " (" << width << ")" << endl;
		cout << "Step: " << argv[2] << " (" << step << ")" << endl;
	}

	double sum = 0;
	for(double ii = -width; ii <= width; ii+=step) {
		cout << ii << ", " << lanczosKern(ii,width) << endl;
		sum += lanczosKern(ii,width);
	}
	cout << endl << "Integral: " << sum*step << endl;
	
}
