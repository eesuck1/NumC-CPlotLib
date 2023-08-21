#ifndef NUMC_H
#define NUMC_H

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define MAT_AT(matrix, i, j) (matrix).numbers[(i) * (matrix).columns + (j)]
#define INITIALIZER_AT(initializer, columns, i, j) (initializer)[(i) * (columns) + (j)]
#define VEC_AT(vector, i) (vector).numbers[(i)]

/*
 *
 * TODO: |--------------------------------------------------------------------------------------------|
 * TODO: |   optimize getting a layer and weight matrix by create separate functions ( line 403 )     |
 * TODO: |   create forwarding and backpropagation                                                    |
 * TODO: |   optimize perceptron allocation                                                           |
 * TODO: |--------------------------------------------------------------------------------------------|
 *
 */

typedef double (*function_type)(double x);

typedef struct
{
    size_t columns;
    size_t rows;
    double* numbers;
} NCMatrix; // NumC Matrix structure that contain: amount of column, amount of rows and pointer to data

typedef struct
{
    size_t length;
    double* numbers;
} NCVector; // NumC Vector structure that contain: length of vector and pointer to data

typedef struct
{
    size_t weights;
    NCMatrix* matrices;
} NCWeights; // NumC Weights structure that contain: numbers of weights matrices and matrices themselves

typedef struct
{
    size_t layers;
    NCMatrix* matrices;
    function_type* activations;
} NCLayers; // NumC Layer structure that contain: number of neurons in Layer and data Vector

typedef struct
{
    NCLayers layers;
    NCWeights weights;
} NCPerceptron; // ...


NCMatrix matrix_allocate(size_t rows, size_t columns); // allocates in memory a matrix object and returns NCMatrix structure
void matrix_initialize(NCMatrix matrix, const double* initializer, const size_t* initializer_size); // initialize a matrix by a given initializer array passed by reference to first element ( for example &array[0][0] )
void matrix_initialize_v(NCMatrix matrix, const NCVector* initializer, size_t initializer_size); // initialize a matrix by a given initializer array of vectors
double matrix_at(NCMatrix matrix, size_t row, size_t column); // returns an element at given position
void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix dot product between first and second and puts into destination
void matrix_sum(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix sum between first and second and puts into destination
void matrix_scale(NCMatrix matrix, double scalar); // multiplies a matrix by gives scalar
void matrix_print(NCMatrix matrix); // prints a matrix
void matrix_random(NCMatrix matrix, unsigned int random_state); // feels a matrix with random numbers in range (0, 1)
void matrix_zero(NCMatrix matrix); // feels a matrix with 0.0
void apply_to_matrix(NCMatrix matrix, function_type function); // apply a given function to each element of a matrix ( inplace )

void matrix_delete(NCMatrix matrix); // deletes the matrix
NCVector vector_allocate(size_t points); // allocates in memory a vector object and returns NCVector structure
void vector_initialize(NCVector vector, const double* initializer, size_t initializer_size); // / initialize a vector by a given initializer array
double vector_at(NCVector vector, size_t position); // returns an element at given position
double vector_dot(NCVector first, NCVector second); // produces a vector dot product between first and second and puts into destination
double vector_magnitude(NCVector vector); // returns a vector magnitude
void vector_sum(NCVector destination, NCVector first, NCVector second); // produces a vector sum between first and second and puts into destination
void vector_scale(NCVector vector, double scalar); // multiplies a vector by giver scalar
void vector_print(NCVector vector); // prints a vector
void vector_random(NCVector vector, unsigned int random_state); // feels a vector with random numbers in range (0, 1)
void apply_to_vector(NCVector vector, function_type function); // // apply a given function to each element of a vector ( inplace )

void vector_delete(NCVector vector); // deletes the vector

NCWeights weights_allocate(size_t initializer_size); // allocates in memory a weights object and returns NCModel structure
void weights_initialize(NCWeights weights, const NCMatrix* initializer_list, size_t initializer_size); // initialize a weights layers with Matrices
NCMatrix weights_at(NCWeights weights, size_t position); // returns a layer at given position
void weights_print(NCWeights weights); // print the weights

NCLayers layer_allocate(size_t number_of_layers); // allocates in memory a Layer objects
void layer_initialize(NCLayers layers, const size_t* neurons, const function_type* activations); // ...
NCMatrix layer_at(NCLayers layers, size_t index); // ...
size_t layer_at_length(NCLayers layers, size_t index);
void layer_print(NCLayers layers); // prints all layers

NCPerceptron perceptron_allocate(size_t number_of_layers, const size_t* neurons, const function_type* activations); // ...
void perceptron_print(NCPerceptron model); // ...

double activation_identity(double x); // returns a same number

double* linspace(double start, double end, size_t amount); // returns a linear spaced segment
double* apply_to_array(const double* array, size_t length, function_type function); // apply a given function to given array and returns a copy


#endif // NUMC_H
