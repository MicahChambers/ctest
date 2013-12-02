#include <iostream>
#include <cmath>

using namespace std;

void  heatprob(double possible[4])
{
	double sum = 0;
	for(int ii = 0 ; ii < 4; ii++) {
		possible[ii] = 1./(possible[ii]+1);
		if(isnormal(possible[ii]))
			sum += possible[ii];
	}
	for(int ii = 0 ; ii < 4; ii++) {
		if(isnormal(possible[ii])) 
			possible[ii] /= sum;
		else
			possible[ii] = 0;
	}
}

int main()
{
	double vals[] = {1,3,5,0};
	heatprob(vals);
	cout << vals[0] << ", " << vals[1] << ", " << vals[2] << ", " << vals[3] << endl;
	
	vals[0] = INFINITY;
	heatprob(vals);
	cout << vals[0] << ", " << vals[1] << ", " << vals[2] << ", " << vals[3] << endl;
}
