#ifndef NCMATRIX_H
#define NCMATRIX_H

#ifndef FUNCTION_TYPE
#define FUNCTION_TYPE
typedef double (*function_type)(double x);
#endif // FUNCTION_TYPE

#ifndef  MAT_AT
#define MAT_AT(matrix, i, j) (matrix).numbers[(i) * (matrix).columns + (j)]
#endif // MAT_AT

#ifndef INITIALIZER_AT
#define INITIALIZER_AT(initializer, columns, i, j) (initializer)[(i) * (columns) + (j)]
#endif // INITIALIZER_AT

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "ncvector.h"

typedef struct
{
    size_t columns;
    size_t rows;
    double* numbers;
} NCMatrix; // NumC Matrix structure that contain: amount of column, amount of rows and pointer to data

static long long get_seed(); // returns a seed for random number generation

NCMatrix matrix_allocate(size_t rows, size_t columns); // allocates in memory a matrix object and returns NCMatrix structure
void matrix_initialize(NCMatrix matrix, const double* initializer, const size_t* initializer_size); // initialize a matrix by a given initializer array passed by reference to first element ( for example &array[0][0] )
void matrix_initialize_v(NCMatrix matrix, const NCVector* initializer, size_t initializer_size); // initialize a matrix by a given initializer array of vectors
void matrix_copy(NCMatrix destination, NCMatrix source); // copies data from source Matrix into destination Matrix
double matrix_at(NCMatrix matrix, size_t row, size_t column); // returns an element at given position
void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix dot product between first and second and puts into destination
void matrix_sum(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix sum between first and second and puts into destination
void matrix_difference(NCMatrix destination, NCMatrix first, NCMatrix second);
double matrix_sum_of_values(NCMatrix matrix); // returns a sum of all values in matrix;
void matrix_scale(NCMatrix matrix, double scalar); // multiplies a matrix by gives scalar
void matrix_print(NCMatrix matrix); // prints a matrix
void matrix_random(NCMatrix matrix); // feels a matrix with random numbers in range (-1, 1)
void matrix_zero(NCMatrix matrix); // feels a matrix with 0.0
void apply_to_matrix(NCMatrix matrix, function_type function); // apply a given function to each element of a Matrix in-place
NCMatrix matrix_transpose(NCMatrix matrix); // ...
void matrix_transpose_inplace(NCMatrix* matrix); // transpose the given by reference Matrix in-place
void matrix_delete(NCMatrix matrix); // deletes the matrix

#endif // NCMATRIX_H
