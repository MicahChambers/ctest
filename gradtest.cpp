#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "tga.h"

using namespace std;

void convertPosToIPos(double pos[2], double step[2], double origin[2], int ipos[2])
{
	for(int ii = 0 ; ii < 2; ii++){ 
		ipos[ii] = (pos[ii]-origin[ii])/step[ii];
	}
}

int main()
{
	double xrange[2] = {-10, 10};
	double yrange[2] = {-10, 10};
	int size = 100;

	double origin[2] = {xrange[0], yrange[0]};
	double step[2] = {(xrange[1]-xrange[0])/size, (yrange[1]-yrange[0])/size};

	vector<double> func(size*size);
	//fill grid
	for(int xx = 0; xx < size ; xx++) {
		for(int yy = 0; yy < size ; yy++) {
			double x = (xrange[1]-xrange[0])*xx/(double)size + xrange[0];
			double y = (yrange[1]-yrange[0])*yy/(double)size + yrange[0];
			
			func[xx*size + yy] = x*x + y*y;
		}
	}

	double dx = 1;
	double expect_dy = 0;
	double real_dy = 0;
	double dy = 0;
	double grad[2] = {0,0};
	double pos[2] = {8, -4};
	int ipos[2];
	convertPosToIPos(pos, step, origin, ipos);

	double oldval = func[size*ipos[0] + ipos[1]];
	ostringstream ostr; 

	for(int ii = 0 ; ii < 10; ii++) {
		//compute gradient
		grad[0] = 0;
		for(int xx = -1; xx <= 1; xx+=2) {
			int xi = xx+ipos[0];
			if(xi < 0) 
				xi = 0;
			else if(xi >= size) 
				xi = size-1;
			grad[0] += .5*xx*func[size*xi + ipos[1]]/step[0];
		}

		grad[1] = 0;
		for(int yy = -1; yy <= 1; yy+=2) {
			int yi = yy+ipos[1];
			if(yi < 0) 
				yi = 0;
			else if(yi >= size) 
				yi = size-1;
			grad[1] += .5*yy*func[size*ipos[0]+ yi]/step[1];
		}

		double mag = 0;
		for(int ii = 0 ; ii < 2; ii++)
			mag += pow(grad[ii], 2);
		mag = sqrt(mag);
		for(int ii = 0 ; ii < 2; ii++)
			grad[ii] /= mag;

		cout << "Position : (" << pos[0] << "," << pos[1] << ")" << endl;
		cout << "Index Position : (" << ipos[0] << "," << ipos[1] << ")" << endl;
		cout << "Gradient: (" << grad[0] << "," << grad[1] << ")" << " Mag: " << mag << endl;
		expect_dy = dx*mag;
		
		//restore old val (for display purposes)
		func[size*ipos[0] + ipos[1]] = oldval;
		real_dy = oldval;
		cout << "Y: " << func[size*ipos[0]+ipos[1]] << ", Y_Next: " << func[size*ipos[0]+ipos[1]]-expect_dy;

		//move, gradient DESCENT
		pos[0] = pos[0] - dx*grad[0];
		pos[1] = pos[1] - dx*grad[1];
		convertPosToIPos(pos, step, origin, ipos);
		real_dy -= func[size*ipos[0]+ipos[1]];
		cout << "Y_Next: " << func[size*ipos[0]+ipos[1]] << ", Error: " << real_dy << endl;
		
		//save old val (for display purposes)
		oldval = func[size*ipos[0] + ipos[1]];

		//change iposition to a highlighted pixel
		func[size*ipos[0] + ipos[1]] = 400;

		//write image
		ostr.str("test-");
		ostr << ii << ".tga";
		writeTGA(ostr.str(), func, size, size);
	}
}

