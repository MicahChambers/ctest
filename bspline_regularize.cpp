#include <cmath>
#include <iostream>
#include <iomanip>
#include <cassert>
#include "plot.h"

using namespace std;

double B3kern(double x)
{
	switch((int)floor(x)) {
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

double dB3kern(double x)
{
	switch((int)floor(x)) {
		case -2:
			return +2 + 2*x + x*x/2.;
		break;
		case -1:
			return -2*x - 3*x*x/2.;
		break;
		case 0:
			return -2*x + 3*x*x/2.;
		break;
		case 1:
			return -2 + 2*x - x*x/2.;
		break;
		default:
			return 0;
		break;
	}

	return 0;
}

double ddB3kern(double x)
{
	switch((int)floor(x)) {
		case -2:
			return 2 + x;
		break;
		case -1:
			return -2 - 3*x;
		break;
		case 0:
			return -2 + 3*x;
		break;
		case 1:
			return  2 - x;
		break;
		default:
			return 0;
		break;
	}
	return 0;
}

double combine(double ax, double(*a)(double), double bx, double(*b)(double))
{
	return a(ax)*b(bx);
}

double BB(double ax, double bx)
{
	return B3kern(ax)*B3kern(bx);
}

double dBdB(double ax, double bx)
{
	return dB3kern(ax)*dB3kern(bx);
}

double ddBddB(double ax, double bx)
{
	return ddB3kern(ax)*ddB3kern(bx);
}

double integrate(double min, double max, double dx, double(*foo)(double))
{
	double sum = 0;
	for(double x = min; x < max; x += dx) {
		sum += foo(x);
	}
	return sum*dx;
}

//This is needed for the derivative of a regularization term
class BConv1
{
	public:
	BConv1(int deriv = 0, double dalpha = 0.001)
	{
		double(*foo)(double) = NULL;
		switch(deriv) {
			case 2:
				foo = ddB3kern;
				break;
			case 1:
				foo = dB3kern;
				break;
			default:
			case 0:
				foo = B3kern;
				break;
		}

		for(int tt = -2 ; tt <= 2; tt++) {
			for(int pp = -2 ; pp <= 2; pp++) {
				double sum = 0;
				for(double alpha = pp-0.5; alpha < pp+0.5; alpha += dalpha) {
					sum += foo(tt+pp-alpha)*foo(-alpha);
				}
				m_mat[tt+2][pp+2] = sum*dalpha;
			}
		}

	};

	double m_mat[5][5];
	const double& operator()(int tt, int pp) const
	{
		assert(tt <= 2 && tt >= -2);
		assert(pp <= 2 && pp >= -2);
		return m_mat[tt+2][pp+2];
	}
};


//This is needed for the regularization term
class BConv0
{
	public:
	BConv0(int deriv = 0, double dalpha = 0.001)
	{
		double(*foo)(double) = NULL;
		switch(deriv) {
			case 2:
				foo = ddB3kern;
				break;
			case 1:
				foo = dB3kern;
				break;
			default:
			case 0:
				foo = B3kern;
				break;
		}

		for(int tt = -2 ; tt <= 2; tt++) {
			for(int pp = -2 ; pp <= 2; pp++) {
				double sum = 0;
				for(double alpha = -0.5; alpha < 0.5; alpha += dalpha) {
					sum += foo(tt-alpha)*foo(pp-alpha);
				}
				m_mat[tt+2][pp+2] = sum*dalpha;
			}
		}

	};

	double m_mat[5][5];
	const double& operator()(int tt, int pp) const
	{
		assert(tt <= 2 && tt >= -2);
		assert(pp <= 2 && pp >= -2);
		return m_mat[tt+2][pp+2];
	}
};

const BConv1 bconv1(0, 0.0001);
const BConv1 dbconv1(1, 0.0001);
const BConv1 ddbconv1(2, 0.0001);

const BConv0 bconv0(0, 0.0001);
const BConv0 dbconv0(1, 0.0001);
const BConv0 ddbconv0(2, 0.0001);
	
const int ll = 4;
const int mm = 4;
const int nn = 4;

int clamp(int lb, int ub, int val)
{
	return std::min(std::max(lb, val), ub);
}


double bruteForceDPHI(double knots[9][9][9], double res, 
		double(*xf)(double), double (*yf)(double), double (*zf)(double))
{
	/* AA' */
	//brute force evaluation
	double sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = xf(ll - xx);
				double bm = yf(mm - yy);
				double bn = zf(nn - zz);
				int iim = round(xx);
				int jjm = round(yy);
				int kkm = round(zz);
				for(int ii = iim - 2; ii <= iim + 2; ii++) {
					if(ii < 0 || ii >= 9)
						continue;
					for(int jj = jjm - 2; jj <= jjm + 2; jj++) {
						if(jj < 0 || jj >= 9)
							continue;
						for(int kk = kkm - 2; kk <= kkm + 2; kk++) {
							if(kk < 0 || kk >= 9)
								continue;
							double phi_abc = knots[ii][jj][kk];
							double bx = xf(ii - xx);
							double by = yf(jj - yy);
							double bz = zf(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "\nBrute Force: " << sum << endl;
}

double smartDPHI(double knots[9][9][9], 
		const BConv1& xf, const BConv1& yf, const BConv1& zf)
{
	double sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*xf(pp, tt)*yf(qq, uu)*zf(rr, vv);
						}
					}
				}
			}
		}
	}

	cout << "Fast: " << sum << endl;
}

double bruteForce(double knots[9][9][9], double res, 
		double(*xf)(double), double (*yf)(double), double (*zf)(double))
{
	double sum = 0;
	for(double xx = 0; xx < 9; xx += res) {
		cerr << "\r" << "            " << xx << ": " << sum*pow(res, 3) << "\r";
		for(double yy = 0; yy < 9; yy += res) {
			for(double zz = 0; zz < 9; zz += res) {
				double val = 0;
				int iim = round(xx);
				int jjm = round(yy);
				int kkm = round(zz);
				for(int ii = iim - 2; ii <= iim + 2; ii++) {
					for(int jj = jjm - 2; jj <= jjm + 2; jj++) {
						for(int kk = kkm - 2; kk <= kkm + 2; kk++) {
							double bx = xf(ii - xx);
							double by = yf(jj - yy);
							double bz = zf(kk - zz);
							double phi_abc = knots[clamp(0,8,ii)][clamp(0,8,jj)][clamp(0,8,kk)];
							val += phi_abc*bx*by*bz;
						}
					}
				}
				sum += val*val;
			}
		}
	}
	sum *= pow(res,3);
	cout << "\nBrute Force" << sum << endl;
}

double smart(double knots[9][9][9], 
		const BConv0& xf, const BConv0& yf, const BConv0& zf)
{

	double sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							for(int xx = 0; xx < 9; xx++) {
								for(int yy = 0; yy < 9; yy++) {
									for(int zz = 0; zz < 9; zz++) {
										double k1 = knots[clamp(0,8,xx+tt)][clamp(0,8,yy+uu)][clamp(0,8,zz+vv)];
										double k2 = knots[clamp(0,8,xx+pp)][clamp(0,8,yy+qq)][clamp(0,8,zz+rr)];
										sum += k1*k2*xf(pp, tt)*yf(qq, uu)*zf(rr, vv);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "Smart" << sum << endl;
}

int main(int argc, char** argv)
{
	cerr << "Starting" << endl;
	//generate test data
	double res = .03;
	double knots[9][9][9];
	for(int ii = 0; ii < 9; ii++) {
		for(int jj = 0; jj < 9; jj++) {
			for(int kk = 0; kk < 9; kk++) {
				knots[ii][jj][kk] = rand()%10;
			}
		}
	}

	cerr << "AA'" << endl;
	bruteForceDPHI(knots, res, ddB3kern, B3kern, B3kern);
	smartDPHI(knots, ddbconv1, bconv1, bconv1);
	
	cerr << "BB'" << endl;
	bruteForceDPHI(knots, res, B3kern, ddB3kern, B3kern);
	smartDPHI(knots, bconv1, ddbconv1, bconv1);
	
	cerr << "CC'" << endl;
	bruteForceDPHI(knots, res, B3kern, B3kern, ddB3kern);
	smartDPHI(knots, bconv1, bconv1, ddbconv1);
	
	cerr << "DD'" << endl;
	bruteForceDPHI(knots, res, dB3kern, B3kern, dB3kern);
	smartDPHI(knots, dbconv1, bconv1, dbconv1);
	
	cerr << "EE'" << endl;
	bruteForceDPHI(knots, res, B3kern, dB3kern, dB3kern);
	smartDPHI(knots, bconv1, dbconv1, dbconv1);
	
	cerr << "FF'" << endl;
	bruteForceDPHI(knots, res, dB3kern, dB3kern, B3kern);
	smartDPHI(knots, dbconv1, dbconv1, bconv1);
	
	cerr << "AA" << endl;
	bruteForce(knots, res, ddB3kern, B3kern, B3kern);
	smart(knots, ddbconv0, bconv0, bconv0);
	
	cerr << "BB" << endl;
	bruteForce(knots, res, B3kern, ddB3kern, B3kern);
	smart(knots, bconv0, ddbconv0, bconv0);
	
	cerr << "CC" << endl;
	bruteForce(knots, res, B3kern, B3kern, ddB3kern);
	smart(knots, bconv0, bconv0, ddbconv0);
	
	cerr << "DD" << endl;
	bruteForce(knots, res, dB3kern, B3kern, dB3kern);
	smart(knots, dbconv0, bconv0, dbconv0);
	
	cerr << "EE" << endl;
	bruteForce(knots, res, B3kern, dB3kern, dB3kern);
	smart(knots, bconv0, dbconv0, dbconv0);
	
	cerr << "FF" << endl;
	bruteForce(knots, res, dB3kern, dB3kern, B3kern);
	smart(knots, dbconv0, dbconv0, bconv0);
}


