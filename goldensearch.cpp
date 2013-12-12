#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

double goldenSectionSearch(double x1, double x4, double (*f)(double)) 
{
	double midp;
	double x;
	const double TAU = (3.-sqrt(5.))/2;
	double x2, x3, y2, y3;
	double y1 = f(x1);
	double y4 = f(x4);
	double TOL = .001;
		
	x2 = x1+TAU*(x4-x1);
	x3 = x4-TAU*(x4-x1);
	y2 = f(x2);
	y3 = f(x3);
	//a = x_1
	//b = x_2
	//b_bar = x_3
	//a_bar = x4
	while(fabs(x4 - x1) > TOL ) {
		assert(fabs(x2 - (x1+TAU*(x4-x1))) < 0.00000001);
		assert(fabs(x3 - (x4-TAU*(x4-x1))) < 0.00000001);
		if(y2 < y3) {
			if(y1 <= y2) {
				//     * 
				//   ]   
				// *
				cout << "1Bef: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
				x4 = x2;
				y4 = y2; 

				x2 = x1+TAU*(x4-x1);
				x3 = x4-TAU*(x4-x1);
				y2 = f(x2);
				y3 = f(x3);
				cout << "Next: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
			} else {
				// *   ] 
				//   * 
				cout << "2Bef: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
				x4 = x3;
				y4 = y3;
				
				x3 = x2;
				y3 = y2;
				x2 = x1+TAU*(x4-x1);
				y2 = f(x2);
				cout << "Next: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
			}
		} else if(y2 > y3) {
			if(y3 >= y4) {
				// *
				//   [
				//     *
				cout << "3Bef: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
				x1 = x3;
				y1 = y3;
				x3 = x1-TAU*(x4-x1);
				y3 = f(x3);
				
				x2 = x1+TAU*(x4-x1);
				x3 = x4-TAU*(x4-x1);
				y2 = f(x2);
				y3 = f(x3);
				cout << "Next: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
			} else {
				// [   *
				//   *
				cout << "4Bef: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
				x1 = x2;
				y1 = y2;
				
				x2 = x3;
				y2 = y3;
				x3 = x4-TAU*(x4-x1);
				y3 = f(x3);
				cout << "Next: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
			}
		} else {
			cout << "5Bef: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
			x1 = x2;
			y1 = y2;

			//used x2, so need to recompute
			x2 = x1+TAU*(x4-x1);
			y2 = f(x2);
			
			x4 = x3;
			y4 = y3;
			//used x3, so need to recompute
			x3 = x1-TAU*(x4-x1);
			y3 = f(x3);
			cout << "Next: " << x1 << "\t" << x2 << "\t" << x3 << "\t" << x4 << endl;
		}
	}
	return (x4+x1)/2.;
}

double foo(double x)
{
	static int count = 0;
	cout << "|"<<count++ << "|\n";
	return sin(x)*cos(x);
}

int main()
{
	cout << "Min X: " << goldenSectionSearch(-10, 20, foo) << endl;
}
