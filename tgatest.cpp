#include <vector>
#include "tga.h"

using namespace std;


int main(int argc, char** argv)
{
	if(argc != 5) 
		return -1;

	int ncols = 100;
	int nrows = 250;
	vector<double> testvec(nrows*ncols);

	//fill each with the row number
	for(int rr = 0; rr < nrows; rr++) {
		for(int cc = 0; cc < ncols; cc++) {
			testvec[ncols*rr+cc] = cc;
		}
	}
	writeTGA(argv[1], testvec, nrows, ncols);

	//fill each with the col number
	for(int rr = 0; rr < nrows; rr++) {
		for(int cc = 0; cc < ncols; cc++) {
			testvec[ncols*rr+cc] = rr;
		}
	}
	writeTGA(argv[2], testvec, nrows, ncols);

	//fill each with the multiple of the two 
	for(int rr = 0; rr < nrows; rr++) {
		for(int cc = 0; cc < ncols; cc++) {
			testvec[ncols*rr+cc] = cc*rr-100;
		}
	}
	writeTGA(argv[3], testvec, nrows, ncols, true);

	//lists out voxels
	double test[2][3] = {{1,2,3}, {4,5,6}};
	vector<double> testvec2(&test[0][0], &test[0][0]+6);
	writeTGA(argv[4], testvec2, 2, 3);
}
