#include <cmath>
#include <iostream>
#include <iomanip>
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

int main(int argc, char** argv)
{
	//generate test data
	int ll = 4;
	int mm = 4;
	int nn = 4;
	double res = .05;
	double knots[9][9][9];
	for(int ii = 0; ii < 9; ii++) {
		for(int jj = 0; jj < 9; jj++) {
			for(int kk = 0; kk < 9; kk++) {
				knots[ii][jj][kk] = rand()%10;
			}
		}
	}

	//build cache
	double dalpha = 0.001;
	double ddBconv[5][5];
	for(int tt = -2 ; tt <= 2; tt++) {
		for(int pp = -2 ; pp <= 2; pp++) {
			double sum = 0;
			for(double alpha = pp-0.5; alpha < pp+0.5; alpha += dalpha) {
				sum += ddB3kern(tt+pp-alpha)*ddB3kern(-alpha);
			}
			ddBconv[tt+2][pp+2] = sum*dalpha;
			cout << setw(15) << ddBconv[tt+2][pp+2] ;
		}
		cout << endl;
	}
		cout << endl;
	
	double dBconv[5][5];
	for(int tt = -2 ; tt <= 2; tt++) {
		for(int pp = -2 ; pp <= 2; pp++) {
			double sum = 0;
			for(double alpha = pp-0.5; alpha < pp+0.5; alpha += dalpha) {
				sum += dB3kern(tt+pp-alpha)*dB3kern(-alpha);
			}
			dBconv[tt+2][pp+2] = sum*dalpha;
			cout << setw(15) << dBconv[tt+2][pp+2] ;
		}
		cout << endl;
	}
		cout << endl;
	
	double Bconv[5][5];
	for(int tt = -2 ; tt <= 2; tt++) {
		for(int pp = -2 ; pp <= 2; pp++) {
			double sum = 0;
			for(double alpha = pp-0.5; alpha < pp+0.5; alpha += dalpha) {
				sum += B3kern(tt+pp-alpha)*B3kern(-alpha);
			}
			Bconv[tt+2][pp+2] = sum*dalpha;
			cout << setw(15) << Bconv[tt+2][pp+2] ;
		}
		cout << endl;
	}
		cout << endl;

	/* AA' */
	//brute force evaluation
	double sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx << endl;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = ddB3kern(ll - xx);
				double bm = B3kern(mm - yy);
				double bn = B3kern(nn - zz);
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
							double bx = ddB3kern(ii - xx);
							double by = B3kern(jj - yy);
							double bz = B3kern(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "Brute Force AA': " << sum << endl;
	
	sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*ddBconv[pp+2][tt+2]*Bconv[qq+2][uu+2]*Bconv[rr+2][vv+2];
						}
					}
				}
			}
		}
	}

	cout << "Fast AA': " << sum << endl;
	
	/* BB' */
	sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx << endl;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = B3kern(ll - xx);
				double bm = ddB3kern(mm - yy);
				double bn = B3kern(nn - zz);
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
							double bx = B3kern(ii - xx);
							double by = ddB3kern(jj - yy);
							double bz = B3kern(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "Brute Force BB': " << sum << endl;
	
	sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*Bconv[pp+2][tt+2]*ddBconv[qq+2][uu+2]*Bconv[rr+2][vv+2];
						}
					}
				}
			}
		}
	}

	cout << "Fast BB': " << sum << endl;
	
	/* CC' */
	sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx << endl;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = B3kern(ll - xx);
				double bm = B3kern(mm - yy);
				double bn = ddB3kern(nn - zz);
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
							double bx = B3kern(ii - xx);
							double by = B3kern(jj - yy);
							double bz = ddB3kern(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "Brute Force CC': " << sum << endl;
	
	sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*Bconv[pp+2][tt+2]*Bconv[qq+2][uu+2]*ddBconv[rr+2][vv+2];
						}
					}
				}
			}
		}
	}

	cout << "Fast CC': " << sum << endl;
	
	/* DD' */
	sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx << endl;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = dB3kern(ll - xx);
				double bm = dB3kern(mm - yy);
				double bn = B3kern(nn - zz);
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
							double bx = dB3kern(ii - xx);
							double by = dB3kern(jj - yy);
							double bz = B3kern(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "Brute Force DD': " << sum << endl;
	
	sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*dBconv[pp+2][tt+2]*dBconv[qq+2][uu+2]*Bconv[rr+2][vv+2];
						}
					}
				}
			}
		}
	}

	cout << "Fast DD': " << sum << endl;
	
	/* EE' */
	sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx << endl;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = B3kern(ll - xx);
				double bm = dB3kern(mm - yy);
				double bn = dB3kern(nn - zz);
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
							double bx = B3kern(ii - xx);
							double by = dB3kern(jj - yy);
							double bz = dB3kern(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "Brute Force EE': " << sum << endl;
	
	sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*Bconv[pp+2][tt+2]*dBconv[qq+2][uu+2]*dBconv[rr+2][vv+2];
						}
					}
				}
			}
		}
	}

	cout << "Fast EE': " << sum << endl;
	
	/* FF' */
	sum = 0;
	for(double xx = 2; xx < 6; xx += res) {
		cout << xx << endl;
		for(double yy = 2; yy < 6; yy += res) {
			for(double zz = 2; zz < 6; zz += res) {
				double bl = dB3kern(ll - xx);
				double bm = B3kern(mm - yy);
				double bn = dB3kern(nn - zz);
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
							double bx = dB3kern(ii - xx);
							double by = B3kern(jj - yy);
							double bz = dB3kern(kk - zz);
							sum += phi_abc*bx*by*bz*bl*bm*bn;
						}
					}
				}
			}
		}
	}
	sum *= pow(res,3);
	cout << "Brute Force FF': " << sum << endl;
	
	sum = 0;
	for(int pp = -2; pp <= 2; pp++) { 
		for(int qq = -2; qq <= 2; qq++) { 
			for(int rr = -2; rr <= 2; rr++) { 
				for(int tt = -2; tt <= 2; tt++) { 
					for(int uu = -2; uu <= 2; uu++) { 
						for(int vv = -2; vv <= 2; vv++) { 
							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
							sum += phi*dBconv[pp+2][tt+2]*Bconv[qq+2][uu+2]*dBconv[rr+2][vv+2];
						}
					}
				}
			}
		}
	}

	cout << "Fast FF': " << sum << endl;
	
//	sum = 0;
//	for(int pp = -2; pp <= 2; pp++) { 
//		for(int qq = -2; qq <= 2; qq++) { 
//			for(int rr = -2; rr <= 2; rr++) { 
//				for(int tt = -2; tt <= 2; tt++) { 
//					for(int uu = -2; uu <= 2; uu++) { 
//						for(int vv = -2; vv <= 2; vv++) { 
//							double phi = knots[ll+pp+tt][mm+qq+uu][nn+rr+vv];
//							sum += phi*ddBconv[tt+2][pp+2]*Bconv[uu+2][qq+2]*Bconv[vv+2][rr+2];
//							counts[ll-pp+tt][mm-qq+uu][nn-rr+vv]++;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	cout << "Sum: " << sum << endl;
//	cout << "Counts: " << endl;
//	for(int ii = 0; ii < 9; ii++) {
//		for(int jj = 0; jj < 9; jj++) {
//			for(int kk = 0; kk < 9; kk++) {
//				cout << ii << ", " << jj << ", " << kk << ":" << counts[ii][jj][kk] << endl;
//			}
//		}
//	}
//
	
//	double xrange[2] = {-2.5, 2.5};
//	writePlot("bspline.tga", xrange, .01, .01, B3kern, dB3kern, ddB3kern);
}


