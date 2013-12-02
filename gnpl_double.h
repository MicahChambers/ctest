#define FTYPE double

/**********************
 * DOUBLE MATRIX
 *********************/
 //basic
#define MATRIX gsl_matrix
#define MATRIX_CONST_COL gsl_matrix_const_column
#define MATRIX_CONST_ROW gsl_matrix_const_row
#define MATRIX_ALLOC gsl_matrix_alloc 
#define MATRIX_FREE gsl_matrix_free

//get
#define MATRIX_GET gsl_matrix_get
#define MATRIX_GET_ROW gsl_matrix_get_row
#define MATRIX_GET_COL gsl_matrix_get_col

//set
#define MATRIX_SET gsl_matrix_set
#define MATRIX_SET_ROW gsl_matrix_set_row
#define MATRIX_SET_COL gsl_matrix_set_col

#define MATRIX_SET_ALL gsl_matrix_set_all
#define MATRIX_SET_ZERO gsl_matrix_set_zero

//view
#define MATRIX_CONST_VIEW_ARRAY gsl_matrix_const_view_array
#define MATRIX_CONST_VIEW gsl_matrix_const_view
#define MATRIX_MEMCPY gsl_matrix_memcpy

/**********************
 * VECTOR
 *********************/
 //basic
#define VECTOR gsl_vector
#define VECTOR_ALLOC gsl_vector_alloc 
#define VECTOR_FREE gsl_vector_free

//math
#define VECTOR_ADD gsl_vector_add
#define VECTOR_ADD_CONSTANT gsl_vector_add_constant
#define VECTOR_MUL gsl_vector_mul
#define VECTOR_CONST_VIEW gsl_vector_const_view 

//get
#define VECTOR_GET gsl_vector_get

//set
#define VECTOR_SET gsl_vector_set
#define VECTOR_SET_ALL gsl_vector_set_all
#define VECTOR_SET_ZERO gsl_vector_set_zero

//view
#define VECTOR_CONST_VIEW_ARRAY gsl_vector_const_view_array
#define VECTOR_CONST_VIEW gsl_vector_const_view
#define VECTOR_MEMCPY gsl_vector_memcpy

#include "gnpl_base.h"
