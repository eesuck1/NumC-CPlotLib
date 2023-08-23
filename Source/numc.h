#ifndef NUMC_H
#define NUMC_H

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#define MAT_AT(matrix, i, j) (matrix).numbers[(i) * (matrix).columns + (j)]
#define INITIALIZER_AT(initializer, columns, i, j) (initializer)[(i) * (columns) + (j)]
#define VEC_AT(vector, i) (vector).numbers[(i)]

/*
 *
 * TODO: |--------------------------------------------------------------------------------------------|
 * TODO: |   create backpropagation and optimization                                                  |
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
    size_t weights_amount;
    NCMatrix* matrices;
} NCWeights; // NumC Weights structure that contain: numbers of weights matrices and matrices themselves

typedef struct
{
    size_t activations_amount;
    function_type* activations;
    function_type* activations_derivatives;
} NCActivations;

typedef struct
{
    size_t layers_amount;
    NCMatrix* matrices;
    NCActivations activations;
} NCLayers; // NumC Layer structure that contain: number of neurons in Layer and data Vector

typedef struct
{
    NCLayers layers;
    NCWeights weights;
} NCPerceptron; // NumC Perceptron model structure that contain: model Layers, model Weights

long long get_seed(); // returns a seed for random number generation

NCMatrix matrix_allocate(size_t rows, size_t columns); // allocates in memory a matrix object and returns NCMatrix structure
void matrix_initialize(NCMatrix matrix, const double* initializer, const size_t* initializer_size); // initialize a matrix by a given initializer array passed by reference to first element ( for example &array[0][0] )
void matrix_initialize_v(NCMatrix matrix, const NCVector* initializer, size_t initializer_size); // initialize a matrix by a given initializer array of vectors
void matrix_copy(NCMatrix destination, NCMatrix source); // copies data from source Matrix into destination Matrix
double matrix_at(NCMatrix matrix, size_t row, size_t column); // returns an element at given position
void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix dot product between first and second and puts into destination
void matrix_sum(NCMatrix destination, NCMatrix first, NCMatrix second); // produces a matrix sum between first and second and puts into destination
double matrix_sum_of_values(NCMatrix matrix); // returns a sum of all values in matrix;
void matrix_scale(NCMatrix matrix, double scalar); // multiplies a matrix by gives scalar
void matrix_print(NCMatrix matrix); // prints a matrix
void matrix_random(NCMatrix matrix); // feels a matrix with random numbers in range (-1, 1)
void matrix_zero(NCMatrix matrix); // feels a matrix with 0.0
void apply_to_matrix(NCMatrix matrix, function_type function); // apply a given function to each element of a Matrix in-place
void matrix_transpose(NCMatrix* matrix); // transpose the given by reference Matrix in-place

void matrix_delete(NCMatrix matrix); // deletes the matrix
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

NCWeights weights_allocate(size_t initializer_size); // allocates in memory a weights object and returns NCModel structure
void weights_initialize(NCWeights weights, const NCMatrix* initializer_list, size_t initializer_size); // initialize a weights layers with Matrices
NCMatrix weights_at(NCWeights weights, size_t position); // returns a layer at given position
void weights_print(NCWeights weights); // print the weights

NCActivations activations_allocate(size_t number_of_activations); // ...
void activations_initialize(NCActivations structure, function_type* activations, function_type* activation_derivatives); // ...

NCLayers layer_allocate(size_t number_of_layers); // allocates in memory a Layer objects
void layer_initialize(NCLayers layers, const size_t* neurons, NCActivations structure); // Initialize a Layers, with lengths from neurons array, by 0.0 and given functions
void layer_set_data_at(NCLayers layers, size_t index, NCMatrix data); // Sets a data Matrix at given Layer position
function_type layer_activation_at(NCLayers layers, size_t index); // returns an Activation of given Layer
NCMatrix layer_at(NCLayers layers, size_t index); // returns a Layer Matrix at given index
size_t layer_at_length(NCLayers layers, size_t index); // returns a length of Layer Matrix at given index
void layer_print(NCLayers layers); // prints all layers

NCPerceptron perceptron_allocate(size_t number_of_layers, const size_t* neurons, NCActivations structure); // allocates in memory a Perceptron model object with given number of layers and activation functions, weight allocates and initialize with random numbers automatically
void perceptron_set_input(NCPerceptron model, NCMatrix input_data); // sets an input data
void perceptron_print(NCPerceptron model); // prints a given Perceptron model
NCMatrix perceptron_layer_at(NCPerceptron model, size_t index); // returns a Perceptron Layer Matrix at given index
NCMatrix perceptron_weight_at(NCPerceptron model, size_t index); // returns a Perceptron Weight Matrix at given index
function_type perceptron_activation_at(NCPerceptron model, size_t index); // returns an activation function of Layer at given index
size_t perceptron_number_of_layers(NCPerceptron model); // returns a Perceptron Layers number
void perceptron_forward(NCPerceptron model); // forwarding a model
void perceptron_backpropagation(NCPerceptron model); // backpropagation of a Perceptron model

double activation_identity(double x); // returns a same number
double activation_identity_derivative(double x); // identity activation function derivative
double activation_leaky_relu(double x); // leaky ReLU activation function
double activation_leaky_relu_derivative(double x); // leaky ReLU activation function derivative
NCMatrix activation_softmax(NCMatrix matrix); // returns a softmax Matrix

double* linspace(double start, double end, size_t amount); // returns a linear spaced segment
double* apply_to_array(const double* array, size_t length, function_type function); // apply a given function to given array and returns a copy


#endif // NUMC_H
