#if !defined(GNPL_BASE_DOUBLE_CPP)
#include "gnpl_double.h"
#define GNPL_BASE_DOUBLE_CPP
#elif !defined(GNPL_BASE_FLOAT_CPP)

#undef FTYPE
#undef MATRIX
#undef MATRIX_CONST_COL
#undef MATRIX_CONST_ROW
#undef MATRIX_ALLOC
#undef MATRIX_FREE
#undef MATRIX_GET
#undef MATRIX_GET_ROW
#undef MATRIX_GET_COL
#undef MATRIX_SET
#undef MATRIX_SET_ROW
#undef MATRIX_SET_COL
#undef MATRIX_SET_ALL
#undef MATRIX_SET_ZERO
#undef MATRIX_CONST_VIEW_ARRAY
#undef MATRIX_CONST_VIEW
#undef MATRIX_MEMCPY
#undef VECTOR
#undef VECTOR_ALLOC
#undef VECTOR_FREE
#undef VECTOR_ADD
#undef VECTOR_ADD_CONSTANT
#undef VECTOR_MUL
#undef VECTOR_CONST_VIEW
#undef VECTOR_GET
#undef VECTOR_SET
#undef VECTOR_SET_ALL
#undef VECTOR_SET_ZERO
#undef VECTOR_CONST_VIEW_ARRAY
#undef VECTOR_CONST_VIEW
#undef VECTOR_MEMCPY
#include "gnpl_float.h"
#define GNPL_BASE_FLOAT_CPP
#endif

#ifndef GNPL_BASE_CPP_DONE

#include <iostream>
using std::cout;
FTYPE test(FTYPE in)
{
	cout << sizeof(in);
}

#ifndef GNPL_BASE_FLOAT_CPP
#include "gnpl_base.cpp"
#endif 

#endif
