#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class foo
{
	double a;
	T extradata;
	vector<T> moredata;
};

class composite
{
	double b;
	double c;
	int d;
};

int main()
{
	foo<double> dfoo;
	foo<composite> cfoo;
	foo<double[4]> afoo;
}
