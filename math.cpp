#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double tmp1 = 0.0;
	double tmp2 = 0.00000000001;
	double tmp3 = 1.0/0.0;
	double tmp4 = -1.0/0.0;
	cout << 1.0/tmp1 << endl << 1.0/tmp2 << endl << min(1.0/tmp1, 1.0/tmp2) << endl;
	cout << tmp3 << endl << tmp4 << endl << 1.0/tmp3 << endl << 1.0/tmp4 << endl;
}
