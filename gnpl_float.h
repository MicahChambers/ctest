#ifndef GNPL_FLOAT_H
#define FTYPE float

/**********************
 * FLOAT MATRIX
 *********************/
 //basic
#define MATRIX gsl_matrix_float
#define MATRIX_CONST_COL gsl_matrix_float_const_column
#define MATRIX_CONST_ROW gsl_matrix_float_const_row
#define MATRIX_ALLOC gsl_matrix_float_alloc 
#define MATRIX_FREE gsl_matrix_float_free

//get
#define MATRIX_GET gsl_matrix_float_get
#define MATRIX_GET_ROW gsl_matrix_float_get_row
#define MATRIX_GET_COL gsl_matrix_float_get_col

//set
#define MATRIX_SET gsl_matrix_float_set
#define MATRIX_SET_ROW gsl_matrix_float_set_row
#define MATRIX_SET_COL gsl_matrix_float_set_col

#define MATRIX_SET_ALL gsl_matrix_float_set_all
#define MATRIX_SET_ZERO gsl_matrix_float_set_zero

//view
#define MATRIX_CONST_VIEW_ARRAY gsl_matrix_float_const_view_array
#define MATRIX_CONST_VIEW gsl_matrix_float_const_view
#define MATRIX_MEMCPY gsl_matrix_float_memcpy

/**********************
 * FLOAT VECTOR
 *********************/
 //basic
#define VECTOR gsl_vector_float
#define VECTOR_ALLOC gsl_vector_float_alloc 
#define VECTOR_FREE gsl_vector_float_free

//math
#define VECTOR_ADD gsl_vector_float_add
#define VECTOR_ADD_CONSTANT gsl_vector_float_add_constant
#define VECTOR_MUL gsl_vector_float_mul
#define VECTOR_CONST_VIEW gsl_vector_float_const_view 

//get
#define VECTOR_GET gsl_vector_float_get

//set
#define VECTOR_SET gsl_vector_float_set
#define VECTOR_SET_ALL gsl_vector_float_set_all
#define VECTOR_SET_ZERO gsl_vector_float_set_zero

//view
#define VECTOR_CONST_VIEW_ARRAY gsl_vector_float_const_view_array
#define VECTOR_CONST_VIEW gsl_vector_float_const_view
#define VECTOR_MEMCPY gsl_vector_float_memcpy

#include "gnpl_base.h"
#endif //GNPL_FLOAT_H
