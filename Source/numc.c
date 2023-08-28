#include "numc.h"



double* linspace(double start, double end, size_t amount)
{
    double *result = (double*)malloc(amount * sizeof(double));

    assert(result != NULL);

    double step = (end - start) / (double)(amount - 1);

    for (size_t i = 0; i < amount; i++)
    {
        result[i] = start + (double)i * step;
    }

    return result;
}

double* apply_to_array(const double *array, const size_t length, function_type function)
{
    double* result = (double*)malloc(length * sizeof(double));

    for (size_t i = 0; i < length; i++)
    {
        result[i] = function(array[i]);
    }

    return result;
}

NCWeights weights_allocate(size_t number_of_layers)
{
    NCWeights result;

    result.weights_amount = number_of_layers;
    result.matrices = malloc(sizeof(*result.matrices) * number_of_layers);

    assert(result.matrices != NULL);

    return result;
}

void weights_initialize(NCWeights weights, const NCMatrix *initializer_list, size_t initializer_size)
{
    assert((weights.weights_amount == initializer_size) && "Model and Initializer lengths must be the same!");

    for (size_t i = 0; i < initializer_size; ++i)
    {
        weights.matrices[i] = initializer_list[i];
    }
}

NCMatrix weights_at(NCWeights weights, size_t position)
{
    assert((position < weights.weights_amount) && "Model out of bounds!");

    return weights.matrices[position];
}

void weights_print(NCWeights weights)
{
    for (size_t i = 0; i < weights.weights_amount; ++i)
    {
        printf("Layer %zu\n\n", i);

        matrix_print(weights_at(weights, i));
    }
}

NCActivations activations_allocate(size_t number_of_activations)
{
    NCActivations result;

    result.activations_amount = number_of_activations;
    result.activations = malloc(sizeof(*result.activations) * number_of_activations);
    result.activations_derivatives = malloc(sizeof(*result.activations_derivatives) * number_of_activations);

    assert(result.activations != NULL);
    assert(result.activations_derivatives != NULL);

    return result;
}

void activations_initialize(NCActivations structure, function_type *activations, function_type *activation_derivatives)
{
    structure.activations = activations;
    structure.activations_derivatives = activation_derivatives;
}

NCLayers layer_allocate(size_t number_of_layers)
{
    NCLayers result;

    result.layers_amount = number_of_layers;
    result.matrices = malloc(sizeof(*result.matrices) * number_of_layers);
    result.activations = activations_allocate(number_of_layers);

    assert(result.matrices != NULL);

    return result;
}

void layer_initialize(NCLayers layers, const size_t* neurons, NCActivations structure)
{
    for (size_t i = 0; i < layers.layers_amount; ++i)
    {
        NCMatrix matrix = matrix_allocate(1, neurons[i]);
        matrix_zero(matrix);

        layers.matrices[i] = matrix;
        layers.activations.activations[i] = structure.activations[i];
    }
}

NCMatrix layer_at(NCLayers layers, size_t index)
{
    assert(index < layers.layers_amount && "Layers index out of bounds!");

    return layers.matrices[index];
}

function_type layer_activation_at(NCLayers layers, size_t index)
{
    assert((index < layers.layers_amount) && "Layer Activation out of bounds!");

    return layers.activations.activations[index];
}

void layer_set_data_at(NCLayers layers, size_t index, NCMatrix data)
{
    assert((layers.matrices[index].columns == data.columns && layers.matrices[index].rows == data.rows) && "Layer Matrix and given Matrix are incompatible");

    layers.matrices[index] = data;
}

size_t layer_at_length(NCLayers layers, size_t index)
{
    return layer_at(layers, index).columns;
}

void layer_print(NCLayers layers)
{
    for (size_t i = 0; i < layers.layers_amount; ++i)
    {
        matrix_print(layers.matrices[i]);
    }
}

NCPerceptron perceptron_allocate(size_t number_of_layers, const size_t *neurons, NCActivations structure)
{
    NCPerceptron result;

    result.layers = layer_allocate(number_of_layers);
    layer_initialize(result.layers, neurons, structure);

    NCMatrix matrices[number_of_layers - 1];

    for (size_t i = 0; i < number_of_layers - 1; ++i)
    {
        matrices[i] = matrix_allocate(neurons[i], neurons[i + 1]);
        matrix_random(matrices[i]);
    }

    result.weights = weights_allocate(number_of_layers - 1);
    weights_initialize(result.weights, matrices, number_of_layers - 1);

    return result;
}

void perceptron_print(NCPerceptron model)
{
    for (size_t i = 0; i  < model.weights.weights_amount; ++i)
    {
        printf("Layer %zu\n", i);
        matrix_print(perceptron_layer_at(model, i));

        printf("Weights %zu-%zu\n", i, i + 1);
        matrix_print(perceptron_weight_at(model, i));
    }

    printf("Layer %zu\n", perceptron_number_of_layers(model) - 1);
    matrix_print(perceptron_layer_at(model, perceptron_number_of_layers(model) - 1));
}

void perceptron_set_input(NCPerceptron model, NCMatrix input_data)
{
    layer_set_data_at(model.layers, 0, input_data);
}

NCMatrix perceptron_layer_at(NCPerceptron model, size_t index)
{
    assert(index < perceptron_number_of_layers(model) && "Perceptron model Layer index out of bounds!");

    return model.layers.matrices[index];
}

NCMatrix perceptron_weight_at(NCPerceptron model, size_t index)
{
    assert(index < model.weights.weights_amount && "Perceptron model Weight index out of bounds!");

    return model.weights.matrices[index];
}

function_type perceptron_activation_at(NCPerceptron model, size_t index)
{
    assert(index < perceptron_number_of_layers(model) && "Perceptron model Activation index out of bounds!");

    return layer_activation_at(model.layers, index);
}

size_t perceptron_number_of_layers(NCPerceptron model)
{
    return model.layers.layers_amount;
}

void perceptron_train(NCPerceptron model, NCMatrix* train, size_t train_amount, NCMatrix* labels, size_t labels_amount)
{
    assert((train_amount == labels_amount) && "Train data samples amount must be the same as Labels amount");

    size_t layers_amount = perceptron_number_of_layers(model);

    for (size_t i = 0; i < train_amount; ++i)
    {
        assert((perceptron_layer_at(model, 0).rows == train[i].rows) && "Train data rows and Input Layer rows are incompatible");
        assert((perceptron_layer_at(model, 0).columns == train[i].columns) && "Train data columns and Input Layer columns are incompatible");
        assert((perceptron_layer_at(model, layers_amount - 1).rows == labels[i].rows) && "Label rows and Input Layer rows are incompatible");
        assert((perceptron_layer_at(model, layers_amount - 1).columns == labels[i].columns) && "Label columns and Input Layer columns are incompatible");
    }

//    NCLayers before_activation = layer_allocate(layers_amount);
    double error = 0.0;

    for (size_t sample_index = 0; sample_index < train_amount; ++sample_index)
    {
        perceptron_set_input(model, train[sample_index]);
//        layer_set_data_at(before_activation, 0, train[sample_index]);

        for (size_t epoch = 0; epoch < 100; ++epoch)
        {
            for (size_t i = 1; i < layers_amount; ++i)
            {
                matrix_dot(perceptron_layer_at(model, i), perceptron_layer_at(model, i - 1), perceptron_weight_at(model, i - 1));
//                layer_set_data_at(before_activation, i, perceptron_layer_at(model, i));
                apply_to_matrix(perceptron_layer_at(model, i), perceptron_activation_at(model, i));
            }

            error = mean_squared_error(perceptron_layer_at(model, layers_amount - 1), labels[sample_index]);

            printf("Epochs: %zu Error: %f", epoch, error);
        }
    }
}

double activation_identity(double x) { return x; }

double activation_identity_derivative(double x) { return 1; }

double activation_leaky_relu(double x) { return fmax(0.01 * x, x); }

double activation_leaky_relu_derivative(double x) { return x < 0 ? 0.01 : 1; }

NCMatrix activation_softmax(NCMatrix matrix)
{
    NCMatrix result = matrix_allocate(matrix.rows, matrix.columns);
    matrix_copy(result, matrix);

    apply_to_matrix(result, exp);
    matrix_scale(result, 1 / matrix_sum_of_values(result));

    return result;
}

double mean_squared_error(NCMatrix predicted, NCMatrix real)
{
    assert(predicted.rows == real.rows && "Predicted and True row lengths must be the same!");
    assert(predicted.columns == real.columns && "Predicted and True column lengths must be the same!");

    double error = 0;

    for (size_t i = 0; i < predicted.rows; ++i)
    {
        for (size_t j = 0; j < predicted.columns; ++j)
        {
            error += pow(MAT_AT(predicted, i, j) - MAT_AT(real, i, j), 2);
        }
    }

    return error / (double)(predicted.columns * predicted.rows);
}

double mean_squared_error_derivative(NCMatrix predicted, NCMatrix real)
{
    assert(predicted.rows == real.rows && "Predicted and True row lengths must be the same!");
    assert(predicted.columns == real.columns && "Predicted and True column lengths must be the same!");

    double error = 0;

    for (size_t i = 0; i < predicted.rows; ++i)
    {
        for (size_t j = 0; j < predicted.columns; ++j)
        {
            error += 2 * (MAT_AT(predicted, i, j) - MAT_AT(real, i, j));
        }
    }

    return error / (double)(predicted.columns * predicted.rows);
}
