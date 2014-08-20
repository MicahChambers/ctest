#include <iostream>
#include <list>
#include <cmath>

using namespace std;

list<int> bringInRange(double& f)
{
	double MINTHRESH = 0.000000000001;
	list<int> out;
	f = fmod(f, 4);

	if(fabs(f) < MINTHRESH) {
		f = 0;
		out.push_back(0);
	} else if(fabs(f-1) < MINTHRESH) {
		f = 0;
		out.push_back(1);
	} else if(fabs(f-2) < MINTHRESH) {
		f = 0;
		out.push_back(2);
	} else if(fabs(f-3) < MINTHRESH) {
		f = 0;
		out.push_back(3);
	} else if(f < 0.5) {
		f += 1;
		out.push_back(3);
	} else if(f <= 1.5) {
	} else if(f < 2.5) {
		f -= 1;
		out.push_back(1);
	} else if(f < 3.5) {
		f -= 2;
		out.push_back(2);
	} else {
		f -= 3;
		out.push_back(3);
	}
	return out;
}

int main(int argc, char** argv)
{
	if(argc != 2)
		return 0;

	double f = atof(argv[1]);

	auto out = bringInRange(f);
	cerr << "Gimmes: " << endl;
	for(auto v:out) {
		cerr << v << endl;
	}
	cerr << "Fractional: " << endl;
	cerr << f << endl;

	return 0;
}
