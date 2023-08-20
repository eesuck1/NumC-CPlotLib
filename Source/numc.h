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
} NCVector; // NumC Vector structure that contain: length of vector and pointer to data

NCMatrix matrix_allocate(size_t columns, size_t rows); // allocates in memory a matrix object and returns NCMatrix structure
void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix dot product between first and second and puts into destination
void matrix_sum(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix sum between first and second and puts into destination
void matrix_scale(NCMatrix matrix, double scalar); // multiplies a matrix by gives scalar
void matrix_print(NCMatrix matrix); // prints a matrix
void matrix_random(NCMatrix matrix, unsigned int random_state); // feels a matrix with random numbers in range (0, 1)
void apply_to_matrix(NCMatrix matrix, function_type function); // apply a given function to each element of a matrix ( inplace )
void matrix_delete(NCMatrix matrix); // deletes the matrix

NCVector vector_allocate(size_t points); // allocates in memory a vector object and returns NCVector structure
double vector_dot(NCVector first, NCVector second); // produces a vector dot product between first and second and puts into destination
double vector_magnitude(NCVector vector); // returns a vector magnitude
void vector_sum(NCVector destination, NCVector first, NCVector second); // produces a vector sum between first and second and puts into destination
void vector_scale(NCVector vector, double scalar); // multiplies a vector by giver scalar
void vector_print(NCVector vector); // prints a vector
void vector_random(NCVector vector, unsigned int random_state); // feels a vector with random numbers in range (0, 1)
void apply_to_vector(NCVector vector, function_type function); // // apply a given function to each element of a vector ( inplace )
void vector_delete(NCVector vector); // deletes the vector

double* linspace(double start, double end, size_t amount); // returns a linear spaced segment
double* apply_to_array(const double* array, size_t length, function_type function); // apply a given function to given array and returns a copy


#endif // NUMC_H
