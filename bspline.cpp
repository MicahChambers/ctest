#include <iostream>
#include <string>
#include <vector>

using namespace std;

double B3kern(double x)
{
	switch((int)x) {
		case -2:
			return 4./3. + 2.*x + x*x + x*x*x/6.;
		break;
		case -1:
			return 2./3. - x*x - x*x*x/2.;
		break;
		case 0:
			return 2./3. - x*x + x*x*x/2.;
		break;
		case 1:
			return 4./3. - 2*x + x*x - x*x*x/6.;
		break;
		default:
			return 0;
		break;
	}

	return 0;
}

vector<double> buildCache(double density)
{
	vector<double> ret(4./density, 0);
	cerr << "Building cahe of length " << ret.size() << endl;
	for(size_t ii = 0 ; ii < ret.size(); ii++){
		ret[ii] = B3kern(-2 + ii*density);
	}
	return ret;
}

double B3Cache(double x)
{
	const double density = .001;
	static vector<double> cache = buildCache(density);
	return cache[(int)((2+x)/density)];
}

int main(int argc, char** argv)
{
	const int COUNT = 1000000000;
	if(argc == 2 && string(argv[1]) == "cached") {
		cout << "Cache" << endl;
		for(int ii = 0 ; ii < COUNT; ii++)
			B3Cache(-2+2*ii/((double)COUNT));
	} else {
		cout << "No Cache" << endl;
		for(int ii = 0 ; ii < COUNT; ii++)
			B3kern(-2+2*ii/((double)COUNT));
	}

}
