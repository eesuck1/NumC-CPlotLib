#ifndef NUMC_H
#define NUMC_H

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#include "ncmatrix.h"
#include "ncvector.h"

#define INITIALIZER_AT(initializer, columns, i, j) (initializer)[(i) * (columns) + (j)]


/*
 *
 * TODO: |--------------------------------------------------------------------------------------------|
 * TODO: |   create backpropagation and optimization                                                  |
 * TODO: |   this is where the mess starts                                                            |
 * TODO: |--------------------------------------------------------------------------------------------|
 *
 */

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
void perceptron_train(NCPerceptron model, NCMatrix* train, size_t train_amount, NCMatrix* labels, size_t labels_amount); // forwarding a model

double activation_identity(double x); // returns a same number
double activation_identity_derivative(double x); // identity activation function derivative
double activation_leaky_relu(double x); // leaky ReLU activation function
double activation_leaky_relu_derivative(double x); // leaky ReLU activation function derivative
NCMatrix activation_softmax(NCMatrix matrix); // returns a softmax Matrix
double mean_squared_error(NCMatrix predicted, NCMatrix real); // returns a mean squared error
double mean_squared_error_derivative(NCMatrix predicted, NCMatrix real);

double* linspace(double start, double end, size_t amount); // returns a linear spaced segment
double* apply_to_array(const double* array, size_t length, function_type function); // apply a given function to given array and returns a copy


#endif // NUMC_H
