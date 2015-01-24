#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//#define VERBOSE

/**
 * @brief Very basic counter that iterates over an ND region.
 *
 * Example usage:
 *
 * size_t ret = 0;
 * size_t width = 5;
 * Counter c;
 * c.ndim = ndim;
 * for(size_t ii=0; ii<ndim; ii++)
 *   c.sz[ii] = width;
 * 
 * do {
 *   double weight = 1;
 *   for(int dd = 0; dd < ndim; dd++) 
 *     weight *= c.pos[dd];
 * } while(!c.advance());
 *
 */
struct Counter
{
	static const size_t MAXDIM = 10;
	int sz[MAXDIM];
	int pos[MAXDIM];
	int ndim;
	
	Counter() 
	{ 
		for(size_t dd=0; dd<MAXDIM; dd++) 
			pos[dd] = 0;
	};

	Counter(int dim, int* stop)
	{
		if(dim > MAXDIM)
			throw "Invalid dimensions, >= " + to_string(MAXDIM);
		for(size_t dd=0; dd<dim; dd++) {
			sz[dd] = stop[dd];
			pos[dd] = 0;
		}
		ndim = dim;
	};

	bool advance() {
		for(size_t dd=0; dd<ndim; dd++) {
			pos[dd]++;
			if(pos[dd] == sz[dd])
				pos[dd] = 0;
			else  
				return false;
		}
		
		return true;
	};
};

double counter(size_t ndim)
{
	size_t ret = 0;
	size_t width = 5;
	Counter c;
	c.ndim = ndim;
	for(size_t ii=0; ii<ndim; ii++)
		c.sz[ii] = width;

	do {
		double weight = 1;

		//set index
		for(int dd = 0; dd < ndim; dd++) 
			weight *= c.pos[dd];
		ret += weight;
#ifdef VERBOSE
		for(size_t dd=0; dd<ndim; dd++) {
			if(dd != 0) cout << ",";
			cout << c.pos[dd];
		}
		cout << endl;
#endif //VERBOSE
	} while(!c.advance());
	return ret;
}

double divisionb(size_t ndim)
{
	size_t ret = 0;
	size_t width = 5;
	size_t pts = pow(5, ndim);
	int64_t index[ndim];
	
	div_t result;
	for(int ii = 0 ; ii < pts; ii++) {
		double weight = 1;

		//set index
		result.quot = ii;
		for(int dd = 0; dd < ndim; dd++) {
			result = std::div(result.quot, width);
			index[dd] = result.rem;
			weight *= index[dd];
		}
		ret += weight;
#ifdef VERBOSE
		for(size_t dd=0; dd<ndim; dd++) {
			if(dd != 0) cout << ",";
			cout << index[dd];
		}
		cout << endl;
#endif //VERBOSE
	}
	return ret;
}

int main(int argc, char** argv)
{
	if(argc != 3) {
		cerr << "Usage: multicounter <reps> <ndim>" << endl;
		return 0;
	}

	int reps = atoi(argv[1]);
	int ndim = atoi(argv[2]);

	clock_t c = clock();
	for(size_t ii=0; ii<reps; ii++) 
		divisionb(ndim);
	c = clock() - c;
	cerr << "Division Time: " << c << endl;
	
	c = clock();
	for(size_t ii=0; ii<reps; ii++) 
		counter(ndim);
	c = clock() - c;
	cerr << "Counter Time:  " << c << endl;
}

