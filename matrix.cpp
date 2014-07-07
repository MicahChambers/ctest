#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstddef>

using namespace std;

template <int D1, int D2, typename T = double>
class Matrix
{
public:

	// identity
	Matrix() {
		for(size_t ii=0; ii<D1; ii++) {
			for(size_t jj=0; jj<D2; jj++) {
				data[ii][jj] = (ii==jj);
			}
		}
	};
	
	// constant
	Matrix(double v) {
		for(size_t ii=0; ii<D1; ii++) {
			for(size_t jj=0; jj<D2; jj++) {
				data[ii][jj] = v;
			}
		}
	};

	T& operator[](size_t row) 
	{ 
		assert(row < D1);
		return data[row][0]; 
	};

	T& operator()(size_t row, size_t col = 0) 
	{
		assert(row < D1 && col < D2);
		return data[row][col]; 
	};

	const T& operator[](size_t row) const
	{ 
		assert(row < D1);
		return data[row][0]; 
	};

	const T& operator()(size_t row, size_t col = 0) const
	{
		assert(row < D1 && col < D2);
		return data[row][col]; 
	};

	

private:
	T data[D1][D2];
};

template <int D1, int D2, typename T = double>
ostream& operator<<(ostream& os, const Matrix<D1, D2, T>& dt)
{
	for(size_t rr=0; rr<D1; rr++) {
		os << "[ ";
		for(size_t cc=0; cc<D2; cc++) {
			os << std::setw(9) << std::setprecision(5) << dt(rr, cc);
		}
		os << " ]" << std::endl;
	}
	os << std::endl;
	return os;
}

template <int D1, int D2, typename T = double>
Matrix<D1, D2> operator+=(Matrix<D1, D2>& lhs, const Matrix<D1, D2>& rhs)
{
	for(size_t ii=0; ii<D1; ii++) {
		for(size_t jj=0; jj<D2; jj++) {
			lhs(ii,jj) += rhs(ii,jj);
		}
	}
	return lhs;
}

template <int D1, int D2, typename T = double>
Matrix<D1, D2> operator+(const Matrix<D1, D2>& lhs, const Matrix<D1, D2>& rhs)
{
	Matrix<D1, D2> out(0);
	for(size_t ii=0; ii<D1; ii++) {
		for(size_t jj=0; jj<D2; jj++) {
			out(ii,jj) = lhs(ii,jj)+rhs(ii,jj);
		}
	}
	return out;
}

template <int D1, int D2, typename T = double>
Matrix<D1, D2> operator-(const Matrix<D1, D2>& lhs, const Matrix<D1, D2>& rhs)
{
	Matrix<D1, D2> out(0);
	for(size_t ii=0; ii<D1; ii++) {
		for(size_t jj=0; jj<D2; jj++) {
			out(ii,jj) = lhs(ii,jj)-rhs(ii,jj);
		}
	}
	return out;
}

template <int D1, int D2, typename T = double>
Matrix<D1, D2> operator-(const Matrix<D1, D2>& rhs)
{
	Matrix<D1, D2> out(0);
	for(size_t ii=0; ii<D1; ii++) {
		for(size_t jj=0; jj<D2; jj++) {
			out(ii,jj) = -rhs(ii,jj);
		}
	}
	return out;
}

template <int D1, int D2, int D3, typename T = double>
Matrix<D1, D3> operator*(const Matrix<D1, D2>& lhs, const Matrix<D2, D3>& rhs)
{
	Matrix<D1, D3> out(0);
	for(size_t ii=0; ii<D1; ii++) {
		for(size_t jj=0; jj<D3; jj++) {
			out(ii,jj) = 0;
			for(size_t kk=0; kk<D2; kk++) {
				out(ii,jj) += lhs(ii, kk)*rhs(kk, jj);
			}
		}
	}
	return out;
}

/**
 * @brief Join together 4 matrices from a blockwise decomposition
 *
 * @tparam D1
 * @tparam D2
 * @tparam T
 * @param tl
 * @param tr
 * @param bl
 * @param br
 *
 * @return 
 */
template <int D1, int D2, typename T = double>
Matrix<D1+D2,D1+D2> join(const Matrix<D1,D1>& tl, const Matrix<D1, D2>& tr, 
		const Matrix<D2, D1>& bl, const Matrix<D2,D2>& br)
{
	Matrix<D1+D2, D1+D2> out;

	// top left
	for(size_t rr=0; rr<D1; rr++) {
		for(size_t cc=0; cc<D1; cc++) {
			out(rr,cc) = tl(rr,cc);
		}
	}
	
	// top right
	for(size_t rr=0; rr<D1; rr++) {
		for(size_t cc=0; cc<D2; cc++) {
			out(rr,cc+D1) = tr(rr,cc);
		}
	}
	
	// bottom left 
	for(size_t rr=0; rr<D2; rr++) {
		for(size_t cc=0; cc<D1; cc++) {
			out(rr+D1,cc) = bl(rr,cc);
		}
	}
	
	// bottom right 
	for(size_t rr=0; rr<D2; rr++) {
		for(size_t cc=0; cc<D2; cc++) {
			out(rr+D1,cc+D1) = br(rr,cc);
		}
	}

	return out;
}

template <int D1, int D2, typename T = double>
void split(const Matrix<D1+D2, D1+D2>& input,
		Matrix<D1,D1>& tl, Matrix<D1, D2>& tr, 
		Matrix<D2, D1>& bl, Matrix<D2,D2>& br)
{
	// top left
	for(size_t rr=0; rr<D1; rr++) {
		for(size_t cc=0; cc<D1; cc++) {
			tl(rr,cc) = input(rr,cc);
		}
	}
	
	// top right
	for(size_t rr=0; rr<D1; rr++) {
		for(size_t cc=0; cc<D2; cc++) {
			tr(rr,cc)= input(rr, cc+D1);
		}
	}
	
	// bottom left 
	for(size_t rr=0; rr<D2; rr++) {
		for(size_t cc=0; cc<D1; cc++) {
			bl(rr,cc) = input(rr+D1,cc);
		}
	}
	
	// bottom right 
	for(size_t rr=0; rr<D2; rr++) {
		for(size_t cc=0; cc<D2; cc++) {
			br(rr,cc) = input(rr+D1,cc+D1);
		}
	}
}

template <typename T = double>
Matrix<1, 1> inverse(const Matrix<1, 1>& trg)
{
	return Matrix<1,1>(1./trg(0,0));
}

template <typename T = double>
Matrix<2, 2> inverse(const Matrix<2, 2>& trg)
{
	Matrix<2,2> tmp;
	double det = trg(0,0)*trg(1,1)-trg(1,0)*trg(0,1);
	if(det == 0) {
		std::cerr << "Error non-invertible matrix!" << std::endl;
		return Matrix<2,2>();
	}

	tmp(0,0) = trg(1,1)/det;
	tmp(1,1) = trg(0,0)/det;
	tmp(1,0) = -trg(1,0)/det;
	tmp(0,1) = -trg(0,1)/det;
	return tmp;
}

template <int DIM, typename T = double>
Matrix<DIM, DIM> inverse(const Matrix<DIM, DIM>& trg)
{
#ifdef DEBUG
	cerr << "Blockwise Invert " << trg << endl;
#endif //DEBUG

	// break up into smaller matrices
	Matrix<DIM/2,DIM/2> A;
	Matrix<DIM/2,(DIM+1)/2> B;
	Matrix<(DIM+1)/2,DIM/2> C;
	Matrix<(DIM+1)/2,(DIM+1)/2> D;
	split(trg, A, B, C, D);
	
#ifdef DEBUG
	cerr << "A=" << A << endl;
	cerr << "B=" << B << endl;
	cerr << "C=" << C << endl;
	cerr << "D=" << D << endl;
#endif //DEBUG

	auto AI = inverse(A);
	auto betaI = inverse(D-C*AI*B);

#ifdef DEBUG
	cerr << "AI=" << AI << endl;
	cerr << "betaI=" << betaI << endl;
#endif //DEBUG

	auto tl = AI + AI*B*betaI*C*AI;
	auto tr = -AI*B*betaI;
	auto bl = -betaI*C*AI;
	auto br = betaI;
	
#ifdef DEBUG
	cerr << "A=" << tl << endl;
	cerr << "B=" << tr << endl;
	cerr << "C=" << bl << endl;
	cerr << "D=" << br << endl;
#endif //DEBUG

	auto ret = join(tl, tr, bl, br);
#ifdef DEBUG
	cerr << "Returning " << endl;
#endif //DEBUG

	return ret;
}

/*
int main(int argc, char** argv)
{
	Matrix<3,3> mat1;
	Matrix<3,3> mat2;
	Matrix<3,1> vec;
	for(size_t rr=0; rr<3; rr++) {
		for(size_t cc=0; cc<3; cc++) {
			mat1(rr,cc) = rand()/(double)RAND_MAX;
			mat2(rr,cc) = rand()/(double)RAND_MAX;
		}
		vec[rr] = rand()/(double)RAND_MAX;
	}

	auto mat3 = mat1*mat2;
	cerr << mat1 << " * " << mat2 << " = " << mat3 << endl;

	auto mat4 = mat3*vec;
	cerr << mat3 << " * " << vec << " = " << mat4 << endl;

//	auto mat5 = vec*mat3; //error conflicting types
	
	Matrix<2,2> mat5;
	for(size_t rr=0; rr<2; rr++) {
		for(size_t cc=0; cc<2; cc++) {
			mat5(rr,cc) = rand()/(double)RAND_MAX;
		}
	}

	auto mat6 = inverse(mat5);
	cerr << mat5 << "^-1 = " << endl << mat6 << endl;
	
	auto mat7 = mat1;
	auto mat1I = inverse(mat1);
	cerr << mat1 << "^-1 = " << endl << mat1I << endl;

	auto mat8 = mat7*mat1I;
	cerr << "Identity? " << endl << mat8 << endl;
	auto mat9 = mat1I*mat7;
	cerr << "Identity? " << endl << mat9 << endl;
}
*/

// speed test
int main()
{
	const int iters = 100000000;
	Matrix<3,3> mat1;
	Matrix<3,1> vec;
	Matrix<3,1> acc(0);
	
	auto t = clock();
	for(size_t rr=0; rr<3; rr++) {
		for(size_t cc=0; cc<3; cc++) {
			mat1(rr,cc) = rand()/(double)RAND_MAX;
		}
		vec[rr] = rand()/(double)RAND_MAX;
	}

	t = clock();
	for(size_t ii=0; ii<iters; ii++) {

		// new vector value
		for(size_t rr=0; rr<3; rr++) {
			vec[rr] = rand()/(double)RAND_MAX;
		}
		acc += mat1*vec;
	}
	t = clock() - t;
	printf("%li clicks (%f seconds)\n",t,((float)t)/CLOCKS_PER_SEC);

}
