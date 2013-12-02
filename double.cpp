#include <iostream>

using namespace std;

int main()
{
	double test1 = 0;
	float test2 = 0;
	for(int ii = 0 ; ii < 10 ; ii++) {
		cout << ii << ", " << test1 << ", " << test2 << endl;
		test1++;
		test2++;
	}
}
