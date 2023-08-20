#ifndef NUMC_H
#define NUMC_H

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define MAT_AT(matrix, i, j) (matrix).pointer[(i) * (matrix).columns + (j)]
#define VEC_AT(vector, i) (vector).pointer[(i)]

typedef double function_type(double x);

typedef struct
{
    size_t columns;
    size_t rows;
    double *pointer;

} NCMatrix; // NumC Matrix structure that contain: amount of column, amount of rows and pointer to data

typedef struct
{
    size_t length;
    double *pointer;
} NCVector;

NCMatrix matrix_allocate(size_t columns, size_t rows); // allocates in memory a matrix object and returns NCMatrix structure
void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix dot product between first and second and puts into destination
void matrix_sum(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix sum between first and second and puts into destination
void matrix_print(NCMatrix matrix); // prints a matrix
void matrix_random(NCMatrix matrix, unsigned int random_state); // feels a matrix with random numbers in range (0, 1)
void matrix_delete(NCMatrix matrix); // deletes the matrix

NCVector vector_allocate(size_t points); // allocates in memory a vector object and returns NCVector structure
double vector_dot(NCVector first, NCVector second); // produces a vector dot product between first and second and puts into destination
void vector_sum(NCVector destination, NCVector first, NCVector second); // produces a vector sum between first and second and puts into destination
void vector_print(NCVector vector); // prints a vector
void vector_random(NCVector vector, unsigned int random_state); // feels a vector with random numbers in range (0, 1)
void vector_delete(NCVector vector); // deletes the vector

double* linspace(double start, double end, size_t amount); // returns a linear spaced segment
double* use_to_array(const double* array, size_t length, function_type function); // calls a unary function to each number in an array

#endif // NUMC_H
