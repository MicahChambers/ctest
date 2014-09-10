#include <iostream>
#include <list>

using namespace std;

std::list<int64_t> factor(int64_t f)
{
	std::list<int64_t> factors;
	for(int64_t ii = 2; ii<=f; ii++) {
		while(f % ii == 0) {
			f = f/ii;
			factors.push_back(ii);
		}
	}

	return factors;
}

int64_t round357(int64_t in)
{
	// make it odd
	if(in %2 == 0)
		in++;

	auto factors = factor(in);
	cerr << "Factors of " << in << ": ";
	for(auto f : factors) {
		cerr << f << ", ";
	}
	cerr << endl;
	
	// increase the largest factors first
	factors.sort();
	for(auto rit = factors.rbegin(); rit != factors.rend(); rit++) {

		// once we get to the primes we like, quit
		if(*rit == 3 || *rit == 5 || *rit == 7) 
			break;

		// round up to the product of the givne factors
		(*rit)++;
		*rit = round357(*rit);
	}

	int64_t out = 1;
	for(auto f : factors) {
		out *= f;
	}

	return out;
}


int main(int argc, char** argv)
{
	if(argc != 2) 
		return -1;

	int64_t f = atoi(argv[1]);
	cerr << "Rounding " << f << endl;
	f = round357(f);
	cerr << endl << ".... to " << f << endl;
	return 0;
}
