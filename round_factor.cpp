#include <iostream>
#include <vector>
#include <list>

using namespace std;

int roundup(int toround, const vector<int>& fact)
{
	//remove given factors
	int div = 1;
	int tmp = toround;
	int rounded = toround;
	int ii = 0;

	int step = 0;
	while(tmp > 1) {
		step = 0;
		tmp = rounded;

		/* Factor for a while */
		for(ii = 0 ; ii < fact.size(); ) {
			int m = tmp%fact[ii];
			if(m == 0) {
				tmp /= fact[ii];
				div *= fact[ii];
			} else if(step < fact[ii] - m) {
				step = fact[ii]-m;
				ii++;
			} else {
				ii++;
			}
		}

		rounded += step;
	}
		
	return rounded;
}


int main(int argc, char** argv)
{
	if(argc < 3) {
		cout << "This program rounds up a number so that its prime factors are "
			"only in the given list of needed factors\n";
		cout << "Usage: " << argv[0] << " <number to round> <needed factor "
			"[needed factor [...]]>";
		return 0;
	}

	int tofactor = atoi(argv[1]);
	std::vector<int> primefactors(argc-2);

	for(int ii = 0 ; ii < argc-2; ii++)
		primefactors[ii] = atoi(argv[ii+2]);

	int out = roundup(tofactor, primefactors);
}
