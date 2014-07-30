
#include <cmath>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

#define NDEBUG

class Shear
{
	public: 
	int setRotation(double Rx, double Ry, double Rz);
	int setIdent();
	int rotateX(double Ry);
	int rotateY(double Ry);
	int rotateZ(double Ry);
	int setYZXY(double Rx, double Ry, double Rz);
	int setXZYX(double Rx, double Ry, double Rz);
	int setZYXZ(double Rx, double Ry, double Rz);
	int setZYZ(double Rx);
	int setXZX(double Ry);
	int setYXY(double Rz);

	double normalize(double angle);

	// to iterate through the shear ordering
	// getShiftDim gets the dimension we are currenty beam-shifting
	// getNonShiftDims returns the dimensions that we aren't shifting 
	// getShift takes the first and second dimensions perpendicular to
	// 		the dimension returned by getShiftDim
	int getShiftDim(int iter); 
	char getShiftDimC(int iter); 
	double getShift(double v0, double v1, int iter);
	double getShift(double x, double y, double z,  int iter);

	private:
	void setorder(std::string order);
	double terms[8]; // 0,1 go for first term of order, 2,3 for second etc
	char corder[4]; // xyzx for instance
	unsigned char dorder[4]; // dimensions x-0, y-1, z-2
};

inline
double cot(double v)
{
	return 1./tan(v);
}

inline
double csc(double v)
{
	return 1./sin(v);
}

inline
double sec(double v)
{
	return 1./cos(v);
}

char Shear::getShiftDimC(int iter)
{
	assert(iter >= 0 && iter <= 3);
	return corder[iter];
}

int Shear::getShiftDim(int iter)
{
	assert(iter >= 0 && iter <= 3);
	return dorder[iter];
}

double Shear::getShift(double v0, double v1, int iter)
{
	assert(iter >= 0 && iter <= 3);

	double ret = 0;
	ret += v0*terms[iter*2];
	ret += v1*terms[iter*2+1];

	return ret;
}

double Shear::getShift(double x, double y, double z,  int iter)
{
	assert(iter >= 0 && iter <= 3);

	if(getShiftDimC(iter) == 'x')
		return getShift(y, z, iter);
	if(getShiftDimC(iter) == 'y')
		return getShift(x, z, iter);
	if(getShiftDimC(iter) == 'z')
		return getShift(x, y, iter);

	return 0;
}

int Shear::setIdent()
{
	setorder("----");

	terms[0] = 0;
	terms[1] = 0;
	terms[2] = 0;
	terms[3] = 0;
	terms[4] = 0;
	terms[5] = 0;
	terms[6] = 0;
	terms[7] = 0;

	return 0;
}

int Shear::setYZXY(double Rx, double Ry, double Rz)
{
	setorder("yzxy");

	terms[0] = -cos(Ry)*sin(Rz);
	terms[1] = -csc(Rx)*sin(Rz)+cot(Rx)*sec(Ry)*sin(Rz)+cos(Rz)*tan(Ry);
	terms[2] = csc(Rx)*tan(Ry)+sec(Ry)*(csc(Rz)-cot(Rz)*sec(Ry)-cot(Rx)*tan(Ry));
	terms[3] = cot(Rx)-csc(Rx)*sec(Ry);
	terms[4] = (csc(Rz)-cot(Rz)*sec(Ry))*sin(Rx)-cos(Rx)*tan(Ry);
	terms[5] = cos(Ry)*sin(Rx);
	terms[6] = -cot(Rz)+csc(Rz)*sec(Ry);
	terms[7] = -csc(Rz)*tan(Ry)+sec(Ry)*(-csc(Rx)+cot(Rx)*sec(Ry)+cot(Rz)*tan(Ry));

#ifndef NDEBUG
	cerr << "YZXY" << endl;
	cerr << "phi:" << Rx << ", theta:" << Ry << ", alpha:" << Rz << endl;
	for(size_t ii=0; ii<8; ii++) 
		cerr << "\t" << terms[ii] << endl;
#endif

	for(size_t ii=0; ii<8; ii++) {
		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) {
//#ifndef NDEBUG
//			cerr << "Nope" << endl;
//
//			double tmp[8];
//			// caculate slope
//			setYZXY(Rx+1E-10, Ry+1E-10, Rz+1E-10);
//			for(size_t jj=0; jj<8; jj++)
//				tmp[jj] = terms[jj];
//
//			setYZXY(Rx+2E-10, Ry+2E-10, Rz+2E-10);
//			
//			cerr << "Slope" << endl;
//			for(size_t jj=0; jj<8; jj++) {
//				cerr << "\t" << (terms[jj]-tmp[jj])/(1E-10) << endl;
//				
//			}
//#endif
			return -1;
		}
	}
	return 0;
}

int Shear::setXZYX(double Rx, double Ry, double Rz)
{
	setorder("xzyx");

	terms[0] = (-1+(cos(Rx)*cot(Ry)-csc(Ry))*sin(Rz)*sin(Rx)+cos(Rz)*(cos(Rx)+
				cos(Ry)*pow(sin(Rx),2)))/(cos(Rx)*sin(Rz)+cos(Rz)*sin(Ry)*sin(Rx));
	terms[1] = -cos(Rx)*cot(Ry)+csc(Ry);
	terms[2] = -sin(Ry);
	terms[3] = (sin(Ry)-cos(Rz)*cos(Rx)*sin(Ry)+sin(Rz)*sin(Rx))/
				(cos(Rx)*sin(Rz)+cos(Rz)*sin(Ry)*sin(Rx));
	terms[4] = cos(Rx)*sin(Rz)+cos(Rz)*sin(Ry)*sin(Rx);
	terms[5] = (cos(Ry)-cos(Rx))*csc(Ry)*sin(Rz)-cos(Rz)*sin(Rx);
	terms[6] = (-1+cos(Rz)*cos(Rx)-sin(Rz)*sin(Ry)*sin(Rx))/
				(cos(Rx)*sin(Rz)+cos(Rz)*sin(Ry)*sin(Rx));
	terms[7] = (-cot(Ry)*sin(Rz)+cos(Rx)*csc(Ry)*sin(Rz)+(cos(Rz)-cos(Ry))*sin(Rx))/
				(cos(Rx)*sin(Rz)+cos(Rz)*sin(Ry)*sin(Rx));
#ifndef NDEBUG
	cerr << "XZYX" << endl;
	cerr << Rx << ", " << Ry << ", " << Rz << endl;
	for(size_t ii=0; ii<8; ii++) 
		cerr << "\t" << terms[ii] << endl;
#endif

	for(size_t ii=0; ii<8; ii++){
		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) {
//#ifndef NDEBUG
//			cerr << "Nope" << endl;
//
//			double tmp[8];
//			// caculate slope
//			setYZXY(Rx+1E-10, Ry+1E-10, Rz+1E-10);
//			for(size_t jj=0; jj<8; jj++)
//				tmp[jj] = terms[jj];
//
//			setYZXY(Rx+2E-10, Ry+2E-10, Rz+2E-10);
//			cerr << "Slope" << endl;
//			for(size_t jj=0; jj<8; jj++) {
//				cerr << "\t" << (terms[jj]-tmp[jj])/(1E-10) << endl;
//				
//			}
//#endif
			return -1;
		}
	}
	return 0;
}

int Shear::setZYXZ(double Rx, double Ry, double Rz)
{
	setorder("zyxz");

	terms[0] = -(sin(Ry)-cos(Rz)*cos(Rx)*sin(Ry)+sin(Rz)*sin(Rx))/
			 ( cos(Rx)*sin(Rz)*sin(Ry)+cos(Rz)*sin(Rx));
	terms[1] = sin(Ry);
	terms[2] = cos(Rx)*sin(Rz)+(cos(Rz)-cos(Ry))*csc(Ry)*sin(Rx);
	terms[3] = -cos(Rx)*sin(Rz)*sin(Ry)-cos(Rz)*sin(Rx);
	terms[4] = ((cos(Ry)-cos(Rx))*sin(Rz)+(-cos(Rz)+cos(Ry))*csc(Ry)*sin(Rx))/
				(cos(Rx)*sin(Rz)*sin(Ry)+cos(Rz)*sin(Rx));
	terms[5] = (1-cos(Rz)*cos(Rx)+sin(Rz)*sin(Ry)*sin(Rx))/
		(cos(Rx)*sin(Rz)*sin(Ry)+cos(Rz)*sin(Rx));
	terms[6] = (-1+cos(Rz)*cos(Ry))*csc(Ry);
	terms[7] = (1-cos(Rx)*(cos(Rz)+cos(Ry)*pow(sin(Rz),2))+
				(-cos(Rz)*cot(Ry)+csc(Ry))*sin(Rz)*sin(Rx))/
				(cos(Rx)*sin(Rz)*sin(Ry)+cos(Rz)*sin(Rx));

#ifndef NDEBUG
	cerr << "ZYXZ" << endl;
	cerr << Rx << ", " << Ry << ", " << Rz << endl;
	for(size_t ii=0; ii<8; ii++) 
		cerr << "\t" << terms[ii] << endl;
#endif
	

	for(size_t ii=0; ii<8; ii++){
		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) {
//#ifndef NDEBUG
//			cerr << "Nope" << endl;
//
//			double tmp[8];
//			// caculate slope
//			setYZXY(Rx+1E-10, Ry+1E-10, Rz+1E-10);
//			for(size_t jj=0; jj<8; jj++)
//				tmp[jj] = terms[jj];
//
//			setYZXY(Rx+2E-10, Ry+2E-10, Rz+2E-10);
//			cerr << "Slope" << endl;
//			for(size_t jj=0; jj<8; jj++) {
//				cerr << "\t" << (terms[jj]-tmp[jj])/(1E-10) << endl;
//				
//			}
//#endif
			return -1;
		}
	}
	return 0;
}

// Rotate About X
//int Shear::setYZY(double Rx)
//{
//// In[119]:= FullSimplify[Solve[Sy[0,b].Sz[0,d].Sy[0,f]==R[Rx,0,0],{b,d,f}]]
//// Out[119]= {{b->(-1+Cos[Rx]) Csc[Rx],d->Sin[Rx],f->-Tan[Rx/2]}}
//	setorder("yzy-");
//
//	terms[0] = 0;
//	terms[1] = (-1+cos(Rx))*csc(Rx);
//	terms[2] = 0;
//	terms[3] = sin(Rx);
//	terms[4] = 0;
//	terms[5] = -tan(Rx/2.);
//	terms[6] = 0;
//	terms[7] = 0;
//
//	for(size_t ii=0; ii<8; ii++){
//		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) 
//			return -1;
//	}
//
//	return 0;
//}

int Shear::setZYZ(double Rx)
{
// In[120]:= FullSimplify[Solve[Sz[0,b].Sy[0,d].Sz[0,f]==R[Rx,0,0],{b,d,f}]]
// Out[120]= {{b->Tan[Rx/2],d->-Sin[Rx],f->Tan[Rx/2]}}
	setorder("zyz-");

	terms[0] = 0;
	terms[1] = tan(Rx/2);
	terms[2] = 0;
	terms[3] = -sin(Rx);
	terms[4] = 0;
	terms[5] = tan(Rx/2);
	terms[6] = 0;
	terms[7] = 0;
	
	for(size_t ii=0; ii<8; ii++){
		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) 
			return -1;
	}

	return 0;
}

// Rotate About Y
int Shear::setXZX(double Ry)
{
// In[121]:= FullSimplify[Solve[Sx[0,b].Sz[c,0].Sx[0,f]==R[0,Ry,0],{b,c,f}]]
// Out[121]= {{b->Tan[Ry/2],c->-Sin[Ry],f->Tan[Ry/2]}}
	setorder("xzx-");
	
	terms[0] = 0;
	terms[1] = tan(Ry/2);
	terms[2] = -sin(Ry);
	terms[3] = 0;
	terms[4] = 0;
	terms[5] = tan(Ry/2);
	terms[6] = 0;
	terms[7] = 0;

	for(size_t ii=0; ii<8; ii++){
		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) 
			return -1;
	}
	return 0;
}

//int Shear::setZXZ(double Ry)
//{
//// In[122]:= FullSimplify[Solve[Sz[a,0].Sx[0,d].Sz[e,0]==R[0,Ry,0],{a,d,e}]]
//// Out[122]= {{a->-Tan[Ry/2],d->Sin[Ry],e->(-1+Cos[Ry]) Csc[Ry]}}
//	setorder("zxz-");
//
//	terms[0] = -tan(Ry/2);
//	terms[1] = 0;
//	terms[2] = 0;
//	terms[3] = sin(Ry);
//	terms[4] = (-1+cos(Ry))*csc(Ry);
//	terms[5] = 0;
//	terms[6] = 0;
//	terms[7] = 0;
//
//	for(size_t ii=0; ii<8; ii++){
//		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) 
//			return -1;
//	}
//	return 0;
//}

// Rotate About Z
//int Shear::setXYX(double Rz)
//{
//// In[123]:= FullSimplify[Solve[Sx[a,0].Sy[c,0].Sx[e,0]==R[0,0,Rz],{a,c,e}]]
//// Out[123]= {{a->(-1+Cos[Rz]) Csc[Rz],c->Sin[Rz],e->-Tan[Rz/2]}}
//	setorder("xyx-");
//	terms[0] = (-1+cos(Rz))*csc(Rz);
//	terms[1] = 0;
//	terms[2] = sin(Rz);
//	terms[3] = 0;
//	terms[4] = -tan(Rz/2);
//	terms[5] = 0;
//	terms[6] = 0;
//	terms[7] = 0;
//	
//	for(size_t ii=0; ii<8; ii++){
//		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) 
//			return -1;
//	}
//	return 0;
//}

int Shear::setYXY(double Rz)
{
// In[124]:= FullSimplify[Solve[Sy[a,0].Sx[c,0].Sy[e,0]==R[0,0,Rz],{a,c,e}]]
// Out[124]= {{a->Tan[Rz/2],c->-Sin[Rz],e->Tan[Rz/2]}}
	setorder("yxy-");
	terms[0] = tan(Rz/2);
	terms[1] = 0;
	terms[2] = -sin(Rz);
	terms[3] = 0;
	terms[4] = tan(Rz/2);
	terms[5] = 0;
	terms[6] = 0;
	terms[7] = 0;
	
	for(size_t ii=0; ii<8; ii++){
		if(std::isnan(terms[ii]) || std::isinf(terms[ii]) || fabs(terms[ii]) > 10) 
			return -1;
	}
	return 0;
}

int Shear::rotateX(double Rx)
{
	// There are two solutions, the first uses tan(Rx/2), the other
	// is limited by tan(Rx) and sec(Rx), we choose the lesser
	if(fabs(tan(Rx/2)) < fabs(-1+cos(Rx)+tan(Rx)*(sin(Rx)-1)) && 
			fabs(tan(Rx/2)) < fabs(sec(Rx)*(sin(Rx)-1))) {
		setorder("zyz-");
		terms[0] = 0;
		terms[1] = tan(Rx/2);
		terms[2] = 0;
		terms[3] = -sin(Rx);
		terms[4] = 0;
		terms[5] = tan(Rx/2);
		terms[6] = 0;
		terms[7] = 0;
	} else {
		setorder("yzyz");
		terms[0] = 0;
		terms[1] = -1+cos(Rx)+(-1+sin(Rx))*tan(Rx);
		terms[2] = 0;
		terms[3] = 1;
		terms[4] = 0;
		terms[5] = -1+cos(Rx);
		terms[6] = 0;
		terms[7] = sec(Rx)*(-1+sin(Rx));
	}
#ifndef NDEBUG
	cerr << "X Rotation Only, nonzero terms:";
	for(size_t ii=0 ;ii<8; ii++) {
		if(fabs(terms[ii]) > .00001) {
			cerr << ii << "|" << terms[ii] << "," ;
		}
	}
#endif
	return 0;
}

int Shear::rotateY(double Ry)
{
	// There are two solutions, the first uses tan(Ry/2), the other
	// is limited by tan(Ry) and sec(Ry), we choose the lesser
	if(fabs(tan(Ry/2)) < fabs(-1+cos(Ry)+tan(Ry)*(sin(Ry)+1)) && 
			fabs(tan(Ry/2)) < fabs(sec(Ry)*(sin(Ry)+1))) {
		setorder("xzx-");
		terms[0] = 0;
		terms[1] = tan(Ry/2);
		terms[2] = -sin(Ry);
		terms[3] = 0;
		terms[4] = 0;
		terms[5] = tan(Ry/2);
		terms[6] = 0;
		terms[7] = 0;
	} else {
		setorder("xzxz");
		terms[0] = 0;
		terms[1] = -1+cos(Ry)+(1+sin(Ry))*tan(Ry);
		terms[2] = 1;
		terms[3] = 0;
		terms[4] = 0;
		terms[5] = -1+cos(Ry);
		terms[6] = sec(Ry)*(1+sin(Ry));
		terms[7] = 0;
	}
#ifndef NDEBUG
	cerr << "Y Rotation Only, nonzero terms:";
	for(size_t ii=0 ;ii<8; ii++) {
		if(fabs(terms[ii]) > .00001) {
			cerr << terms[ii] << "," ;
		}
	}
#endif
	return 0;
}

int Shear::rotateZ(double Rz)
{
	// There are two solutions, the first uses tan(Rz/2), the other
	// is limited by tan(Rz) and sec(Rz), we choose the lesser
	if(fabs(tan(Rz/2)) < fabs(-1+sec(Rz)+tan(Rz)) && 
			fabs(tan(Rz/2)) < fabs(-sec(Rz)*(sin(Rz)+1))) {
		setorder("yxy-");
		terms[0] = tan(Rz/2);
		terms[1] = 0;
		terms[2] = -sin(Rz);
		terms[3] = 0;
		terms[4] = tan(Rz/2);
		terms[5] = 0;
		terms[6] = 0;
		terms[7] = 0;
	} else {
		setorder("yxyx");
		terms[0] = -1+sec(Rz)+tan(Rz);
		terms[1] = 0;
		terms[2] = 1;
		terms[3] = 0;
		terms[4] = -1+cos(Rz);
		terms[5] = 0;
		terms[6] = -sec(Rz)*(1+sin(Rz));
		terms[7] = 0;
	}
#ifndef NDEBUG
	cerr << "Z Rotation Only, nonzero terms:";
	for(size_t ii=0 ;ii<8; ii++) {
		if(fabs(terms[ii]) > .00001) {
			cerr << terms[ii] << "," ;
		}
	}
#endif
	return 0;
}

double Shear::normalize(double angle)
{
	const double PI = acos(-1);
	while(angle > PI)
		angle -= 2*PI;
	while(angle < -PI)
		angle += 2*PI;
	return angle;
}

int Shear::setRotation(double Rx, double Ry, double Rz)
{
	const double PI = acos(-1);
	Rx = normalize(Rx); 
	Ry = normalize(Ry); 
	Rz = normalize(Rz); 

	if(fabs(Rx) >= PI/2 || fabs(Ry) >= PI/2 || fabs(Rz) >= PI/2) {
		cerr << "Error, angles > PI / 2 are not supported" << endl;
		return -1;
	} 

	if(Rx == 0 && Ry == 0 && Rz == 0) {
		return setIdent();
	} else if(Ry == 0 && Rz == 0) {
		return rotateX(Rx);
	} else if(Rx == 0 && Rz == 0) {
		return rotateY(Ry);
	} else if(Rx == 0 && Ry == 0) {
		return rotateZ(Rz);
	} else if(setYZXY(Rx, Ry, Rz)==0) {
		return 0;
	} else if(setXZYX(Rx, Ry, Rz)==0) {
		return 0;
	} else if(setZYXZ(Rx, Ry, Rz)==0) {
		return 0;
	}
	return -1;
}

int main()
{
	// Note only angles < 90 degrees work
	const double PI = acos(-1);
	size_t nstep = 100;
	Shear shear;

	for(size_t ii=0; ii < nstep; ii++) {
		for(size_t jj=0; jj < nstep; jj++) {
			for(size_t kk=0; kk < nstep; kk++) {
				double rx = PI/2*ii/nstep;
				double ry = PI/2*jj/nstep;
				double rz = PI/2*kk/nstep;
				if(shear.setRotation(rx, ry, rz) != 0) {
					cerr << "Shear Failed! " << endl;
					return -1;
				}
				
//				shear.setRotation(rx+1E-9, ry+1E-9, rz+1E-9);
				double pos[3] = {1, 3, 9};

				fprintf(stderr, "Before: (%02.2f %02.2f %02.2f)\n", pos[0], pos[1], pos[2]);
				fprintf(stderr, "Angles: (%02.2f %02.2f %02.2f)\n", rx, ry, rz);
//				cerr << "Rotation:\n\tRx: " << rx << "\n\tRy: " << ry 
//					<< "\n\tRz: " << rz << endl;
//				cerr << "Pos:\n\tx:" << pos[0] << "\n\ty:" << pos[1] 
//					<< "\n\tz:" << pos[2] << endl;
				for(size_t it = 0; it < 4; it++) {
					double shift = shear.getShift(pos[0],pos[1],pos[2],it);
					pos[shear.getShiftDim(it)] += shift;
//					cerr << shear.getShiftDim(it) << ":" << shift << endl;
				}
				fprintf(stderr, "After: (%02.2f %02.2f %02.2f)\n", pos[0], pos[1], pos[2]);
			}
		}
	}
}

void Shear::setorder(std::string order)
{
	size_t len = min<size_t>(4, order.size());
	size_t ii=0;

	for(; ii < len; ii++){
		corder[ii] = order[ii];
		if(corder[ii] == 'x') {
			dorder[ii] = 0;
		} else if(corder[ii] == 'y') {
			dorder[ii] = 1;
		} else if(corder[ii] == 'z') {
			dorder[ii] = 2;
		} else if(corder[ii] == '-') {
			dorder[ii] = 0;
		} else {
			cerr << "Coding error results in bad order in Shear::setorder" 
				<< endl;
			throw(-1);
		}
	}

	for(; ii<4; ii++) {
		corder[ii] = '-';
		dorder[ii] = 0;
	}
}

//Sx[a_,b_]:={{1,a,b},{0,1,0},{0,0,1}}
//Sy[c_,d_]:={{1,0,0},{c,1,d},{0,0,1}}
//Sz[e_,f_]:={{1,0,0},{0,1,0},{e,f,1}} 
// Solve For 1 Rotation
// Rotate About X
// In[119]:= FullSimplify[Solve[Sy[0,b].Sz[0,d].Sy[0,f]==R[\[Phi],0,0],{b,d,f}]]
// Out[119]= {{b->(-1+Cos[\[Phi]]) Csc[\[Phi]],d->Sin[\[Phi]],f->-Tan[\[Phi]/2]}}
// In[120]:= FullSimplify[Solve[Sz[0,b].Sy[0,d].Sz[0,f]==R[\[Phi],0,0],{b,d,f}]]
// Out[120]= {{b->Tan[\[Phi]/2],d->-Sin[\[Phi]],f->Tan[\[Phi]/2]}}
// Rotate About Y
// In[121]:= FullSimplify[Solve[Sx[0,b].Sz[c,0].Sx[0,f]==R[0,\[Theta],0],{b,c,f}]]
// Out[121]= {{b->Tan[\[Theta]/2],c->-Sin[\[Theta]],f->Tan[\[Theta]/2]}}
// In[122]:= FullSimplify[Solve[Sz[a,0].Sx[0,d].Sz[e,0]==R[0,\[Theta],0],{a,d,e}]]
// Out[122]= {{a->-Tan[\[Theta]/2],d->Sin[\[Theta]],e->(-1+Cos[\[Theta]]) Csc[\[Theta]]}}
// Rotate About Z
// In[123]:= FullSimplify[Solve[Sx[a,0].Sy[c,0].Sx[e,0]==R[0,0,\[Alpha]],{a,c,e}]]
// Out[123]= {{a->(-1+Cos[\[Alpha]]) Csc[\[Alpha]],c->Sin[\[Alpha]],e->-Tan[\[Alpha]/2]}}
// In[124]:= FullSimplify[Solve[Sy[a,0].Sx[c,0].Sy[e,0]==R[0,0,\[Alpha]],{a,c,e}]]
// Out[124]= {{a->Tan[\[Alpha]/2],c->-Sin[\[Alpha]],e->Tan[\[Alpha]/2]}}
