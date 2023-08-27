#ifndef NCVECTOR_H
#define NCVECTOR_H

#ifndef FUNCTION_TYPE
#define FUNCTION_TYPE
typedef double (*function_type)(double x);
#endif // FUNCTION_TYPE

#ifndef VEC_AT
#define VEC_AT(vector, i) (vector).numbers[(i)]
#endif // VEC_AT

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>

typedef struct
{
    size_t length;
    double* numbers;
} NCVector; // NumC Vector structure that contain: length of vector and pointer to data

#ifndef GET_SEED
#define GET_SEED
long long get_seed(); // returns a seed for random number generation
#endif // GET_SEED

NCVector vector_allocate(size_t points); // allocates in memory a vector object and returns NCVector structure
void vector_initialize(NCVector vector, const double* initializer, size_t initializer_size); // / initialize a vector by a given initializer array
double vector_at(NCVector vector, size_t position); // returns an element at given position
double vector_dot(NCVector first, NCVector second); // produces a vector dot product between first and second and puts into destination
double vector_magnitude(NCVector vector); // returns a vector magnitude
void vector_sum(NCVector destination, NCVector first, NCVector second); // produces a vector sum between first and second and puts into destination
void vector_scale(NCVector vector, double scalar); // multiplies a vector by giver scalar
void vector_print(NCVector vector); // prints a vector
void vector_random(NCVector vector); // feels a vector with random numbers in range (0, 1)
void apply_to_vector(NCVector vector, function_type function); // // apply a given function to each element of a vector ( in-place )
void vector_delete(NCVector vector); // deletes the vector

#endif // NCVECTOR_H
