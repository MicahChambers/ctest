#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char** argv) 
{
	if(argc != 4)
		return -1;
	int DIM = atoi(argv[2]);
	int KPOINTS = atoi(argv[3]);
	int index[DIM];
	for(int ii=0; ii<DIM; ii++)
		index[ii] = 0;

	if(argv[1][0] == 'a') {
		auto t = clock();
		while(index[DIM-1] < KPOINTS) {
//			for(size_t ii=0; ii<DIM; ii++) 
//				cerr << index[ii] << ", ";
//			cerr << endl;

			// iterate
			for(int ii=0; ii<DIM; ii++) {
				if(index[ii]+1 < KPOINTS || ii+1 == DIM) {
					index[ii]++;
					break;
				} else {
					index[ii] = 0;
				}
			}
		}
		t = clock()-1;
		cerr << t << " a" << endl;
	} else {
		auto t = clock();
		div_t result;
		for(int ii = 0 ; ii < pow(KPOINTS, DIM); ii++) {
			//set index
			result.quot = ii;
			for(int dd = 0; dd < DIM; dd++) {
				result = std::div(result.quot, KPOINTS);
				index[dd] = result.rem;
			}

//			for(size_t ii=0; ii<DIM; ii++) 
//				cerr << index[ii] << ", ";
//			cerr << endl;
		}
		t = clock()-1;
		cerr << t << " b" << endl;
	}

	return 0;
}
