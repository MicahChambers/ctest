#include <algorithm>
#include <cstdio>

template <typename T>
class MatrixBase
{
	public:
	
	MatrixBase (unsigned int nrow = 1, unsigned int ncol = 1)
	{
		dim[0] = nrow;
		dim[1] = ncol;
	};
	
	class iterator;

	virtual T get(unsigned int r = 0, unsigned int c = 0) const = 0;
	virtual T& get(unsigned int r = 0, unsigned int c = 0) = 0;
	virtual void set(const T& val, unsigned int r = 0, unsigned int c = 0) = 0;

	void print() 
	{ 
		printf("Matrix (%u x %u\n)\n", dim[0], dim[1]); 
	};

	protected:
	unsigned int dim[2];
};


template <typename T>
class FullDenseMatrix : public MatrixBase<T>
{
	public:

	FullDenseMatrix(unsigned int nrow = 1, unsigned int ncol = 1) : 
				MatrixBase<T>(nrow, ncol)
	{
		data = new T[nrow*ncol];
	};

	~FullDenseMatrix()
	{
		delete[] data;
	}
	
	T& get(unsigned int r = 0, unsigned int c = 0) 
	{
		return data[r + c*this->dim[0]];
	};

	T get(unsigned int r = 0, unsigned int c = 0) const
	{
		return data[r + c*this->dim[0]];
	};
	
	void set(const T& val, unsigned int r = 0, unsigned int c = 0)
	{
		data[r + c*this->dim[0]] = val;
	};

	private:
	T* data;
};

template <typename T>
class UpperDenseMatrix : public MatrixBase<T>
{
	public:

	UpperDenseMatrix(unsigned int nrow = 1, unsigned int ncol = 1) : 
				MatrixBase<T>(nrow, ncol)
	{
		unsigned int extra = nrow*std::max<unsigned int>(ncol - nrow, 0);
		data = new T[nrow*(nrow-1)/2 + nrow + extra];
	};

	~UpperDenseMatrix()
	{
		delete[] data;
	}
	
	T& get(unsigned int r = 0, unsigned int c = 0) 
	{
		unsigned int nrow = this->dim[0];
		unsigned int ncol = this->dim[0];
		if(r > c) {
			return NULL;
		} else if(c < nrow) {
			return data[c*(c-1)/2 + c + r];
		} else {
			return data[nrow*(nrow-1)/2 + nrow + (c - nrow)*nrow + r];
		}
	};

	T get(unsigned int r = 0, unsigned int c = 0) const
	{
		unsigned int nrow = this->dim[0];
		unsigned int ncol = this->dim[0];
		if(r > c) {
			return 0;
		} else if(c < nrow) {
			return data[c*(c-1)/2 + c + r];
		} else {
			return data[nrow*(nrow-1)/2 + nrow + (c - nrow)*nrow + r];
		}
	};
	
	void set(const T& val, unsigned int r = 0, unsigned int c = 0)
	{
		unsigned int nrow = this->dim[0];
		unsigned int ncol = this->dim[0];
		if(r > c) {
			return;
		} else if(c < nrow) {
			data[c*(c-1)/2 + c + r] = val;
		} else {
			data[nrow*(nrow-1)/2 + nrow + (c - nrow)*nrow + r] = val;
		}
	};

	private:
	T* data;
};

template <typename T>
class LowerDenseMatrix : public MatrixBase<T>
{
	public:

	LowerDenseMatrix(unsigned int nrow = 1, unsigned int ncol = 1) : 
				MatrixBase<T>(nrow, ncol)
	{
		unsigned int extra = nrow*std::max<unsigned int>(ncol - nrow, 0);
		data = new T[nrow*(nrow-1)/2 + nrow + extra];
	};

	~LowerDenseMatrix()
	{
		delete[] data;
	}
	
	T& get(unsigned int r = 0, unsigned int c = 0) 
	{
		unsigned int nrow = this->dim[0];
		unsigned int ncol = this->dim[0];
		if(r > c) {
			return NULL;
		} else if(c < nrow) {
			return data[c*(c-1)/2 + c + r];
		} else {
			return data[nrow*(nrow-1)/2 + nrow + (c - nrow)*nrow + r];
		}
	};

	T get(unsigned int r = 0, unsigned int c = 0) const
	{
		unsigned int nrow = this->dim[0];
		unsigned int ncol = this->dim[0];
		if(r > c) {
			return 0;
		} else if(c < nrow) {
			return data[c*(c-1)/2 + c + r];
		} else {
			return data[nrow*(nrow-1)/2 + nrow + (c - nrow)*nrow + r];
		}
	};
	
	void set(const T& val, unsigned int r = 0, unsigned int c = 0)
	{
		unsigned int nrow = this->dim[0];
		unsigned int ncol = this->dim[0];
		if(r > c) {
			return;
		} else if(c < nrow) {
			data[c*(c-1)/2 + c + r] = val;
		} else {
			data[nrow*(nrow-1)/2 + nrow + (c - nrow)*nrow + r] = val;
		}
	};

	private:
	T* data;
};

//template <typename T>
//class Matrix : public MatrixBase<T>
//{
//	public:
//	
//	class iterator
//	{	
//		public:
//		iterator(bool skipzeros = false, bool downrows = true) : 
//					skipZeros(skipzeros), rowCol(downrows)
//		{ };
//
//		void operator++() = 0;
//		void operator--() = 0;
//		void operator*() = 0;
//		
//		bool getRowFirst() const { return rowCol; }
//		bool getSkipZeros() const { return skipZeros; }
//		void where(unsigned int& r, unsigned int& c) 
//		{
//			r = this->r;
//			c = this->c;
//		};
//
//		void where(unsigned int& r) 
//		{
//			r = this->r;
//		};
//
//		protected:
//			unsigned int r;
//			unsigned int c;
//			bool skipZeros;
//			bool rowCol;
//			friend FullDenseMatrix<T>;
//	};
//	
//	friend iterator;
//	iterator begin(bool skipzeros = false, bool downrows = true)
//	{
//		iterator tmp(skipzeros, downrows);
//		tmp.r = 0;
//		tmp.c = 0;
//
//		return tmp;
//	};
//
//	iterator end(bool skipzeros = false, bool downrows = true)
//	{
//		iterator tmp(skipzeros, downrows);
//		if(downrows) {
//			tmp.r = this->dim[0];
//			tmp.c = this->dim[1]-1;
//		} else {
//			tmp.r = this->dim[0]-1;
//			tmp.c = this->dim[1];
//		}
//		return tmp;
//	};
//
//	iterator find(unsigned int r, unsigned int c, bool skipzeros = false, 
//				bool downrows = true)
//	{
//		iterator tmp(skipzeros, downrows);
//		tmp.r = r;
//		tmp.c = c;
//		return tmp;
//	};
//
//	Matrix (unsigned int nrow = 1, unsigned int ncol = 1, bool dense = true,
//				bool upper = false, bool lower = false, bool symm = false)
//	{
//		dim[0] = nrow;
//		dim[1] = ncol;
//		this->structure = 0;
//		this->dense = true;
//	};
//	
//	void makeSymmetric() 
//	{
//		structure = SYMMETRIC;
//	};
//	
//	void makeFull(bool dense) 
//	{
//		//must reallocate and copy
//		if(structure != 0 || structure != SYMMETRIC) {
//			if(dense) {
//				//allocate
//			} else {
//
//			}
//		}
//		structure = 0;
//	};
//	
//	void makeLowerTri(bool realloc = false) 
//	{
//		structure = UPPER;
//		if(realloc) {
//
//		}
//	};
//	
//	void makeUpperTri(bool realloc = false) 
//	{
//		structure = LOWER;
//	};
//
//	void print() 
//	{ 
//		printf("Matrix (%u x %u\n)\n", dim[0], dim[1]); 
//		switch(structure) {
//			case UPPER: 
//				printf("  Upper Triangular\n"); 
//			break; 
//			case LOWER: 
//				printf("  Lower Triangular\n"); 
//			break;
//			case SYMMETRIC: {
//				printf("  Symmetric\n"); 
//			break; 
//			default: 
//				printf("  Full (non symmetric/triangular)\n"); 
//			break; 
//		}
//	};
//
//	T& get(int r, int c)
//	{
//		
//	};
//
//	private:
//	
//	bool dense;
//};
