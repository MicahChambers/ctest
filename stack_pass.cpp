
#include <ctime>
#include <iostream>

/*
 * This is a test of how long it takes to pass new[] data as part of a class
 * versus using a statically defined class. Even a move constructor doesn't
 * get the dynamically allocated memory to the same speed.
 */

using namespace std;

static int COPYCALLS = 0;
static int MOVECALLS = 0;

template <int D>
class allocvars
{
public:
	allocvars() {
		n = new double[D];
	};

	// move constructor
	allocvars(allocvars&& other) {
		n = other.n;
		other.n = NULL;
#ifdef DEBUG
		MOVECALLS++;
#endif //DEBUG
	};

	// copy constructor
	allocvars(const allocvars& other) {
		n = new double[D];
		for(size_t ii=0; ii<D; ii++)
			n[ii] = other.n[ii];
#ifdef DEBUG
		COPYCALLS++;
#endif //DEBUG
	};

	double* n;
	static const int DIM = D;
};

template <int D>
class staticvars
{
public:
	double n[D];
	static const int DIM = D;
};

template <typename T>
double passin(T var)
{
	double sum = 0;
	for(size_t ii=0; ii<T::DIM; ii++) {
		sum += var.n[ii];
	}
	return sum;
}

template <typename T>
T passout()
{
	T out;
	return out;
}

template <typename T>
void passin_test(size_t iters)
{
	cerr << "Pass out (size " << T::DIM << ")" << endl;
	T in;
	double sum = 0;
	clock_t t = clock();
	for(size_t ii=0; ii<iters; ii++) {
		sum += passin<T>(in);
	}
	t = clock() - t;
	printf ("%ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	
}

template <typename T>
double passout_test(size_t iters)
{
	cerr << "Pass out (size " << T::DIM << ")" << endl;
	double sum = 0;
	clock_t t = clock();
	for(size_t ii=0; ii<iters; ii++) {
		T out = passout<T>();
		for(size_t ii=0; ii<T::DIM; ii++)
			sum += out.n[ii];
	}
	t = clock() - t;
	printf ("%ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	
	return sum;
}

int main()
{
	size_t iters = 100000;
	
	cerr << "------------------------------" << endl;
	cerr << "Static Pass In" << endl;
	passin_test<staticvars<1>>(iters);
	passin_test<staticvars<5>>(iters);
	passin_test<staticvars<10>>(iters);
	passin_test<staticvars<100>>(iters);
	passin_test<staticvars<1000>>(iters);
	cerr << "------------------------------" << endl;
	
	cerr << "------------------------------" << endl;
	cerr << "Dynamic Pass In" << endl;
	passin_test<allocvars<1>>(iters);
	passin_test<allocvars<5>>(iters);
	passin_test<allocvars<10>>(iters);
	passin_test<allocvars<100>>(iters);
	passin_test<allocvars<1000>>(iters);
	cerr << "------------------------------" << endl;

	
	cerr << "------------------------------" << endl;
	cerr << "Static Pass Out" << endl;
	passout_test<staticvars<1>>(iters);
	passout_test<staticvars<5>>(iters);
	passout_test<staticvars<10>>(iters);
	passout_test<staticvars<100>>(iters);
	passout_test<staticvars<1000>>(iters);
	cerr << "------------------------------" << endl;
	
	cerr << "------------------------------" << endl;
	cerr << "Dynamic Pass Out" << endl;
	passout_test<allocvars<1>>(iters);
	passout_test<allocvars<5>>(iters);
	passout_test<allocvars<10>>(iters);
	passout_test<allocvars<100>>(iters);
	passout_test<allocvars<1000>>(iters);
	cerr << "------------------------------" << endl;

	cerr << "Copy calls: " << COPYCALLS << endl;
	cerr << "Copy calls: " << MOVECALLS << endl;
}
