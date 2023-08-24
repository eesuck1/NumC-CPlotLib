#include "numc.h"

long long get_seed()
{
    static long long SEED = 0;

    return time(NULL) + SEED++;
}

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

NCMatrix matrix_allocate(size_t rows, size_t columns)
{
    NCMatrix matrix;

    matrix.columns = columns;
    matrix.rows = rows;
    matrix.numbers = malloc(sizeof(*matrix.numbers) * columns * rows);

    assert(matrix.numbers != NULL);

    return matrix;
}

void matrix_initialize(NCMatrix matrix, const double* initializer, const size_t *initializer_size)
{
    size_t initializer_rows = initializer_size[0];
    size_t initializer_columns = initializer_size[1];

    assert((matrix.rows == initializer_rows && matrix.columns == initializer_columns) && "List and Matrix dimension must be the same!");

    for (size_t i = 0; i < initializer_rows; ++i)
    {
        for (size_t j = 0; j < initializer_columns; ++j)
        {
            MAT_AT(matrix, i, j) = INITIALIZER_AT(initializer, initializer_columns, i, j);
        }
    }
}

void matrix_initialize_v(NCMatrix matrix, const NCVector *initializer, size_t initializer_size)
{
    assert((matrix.rows == initializer_size) && "Matrix and Initializer dimensions must be the same!");

    for (size_t i = 0; i < initializer_size; ++i)
    {
        assert((matrix.columns == initializer[i].length) && "Matrix and Vector dimensions must be the same!");
    }

    size_t length = initializer[0].length;

    for (size_t i = 0; i < initializer_size; ++i)
    {
        for (size_t j = 0; j < length; ++j)
        {
            MAT_AT(matrix, i, j) = VEC_AT(initializer[i], j);
        }
    }
}

void matrix_copy(NCMatrix destination, NCMatrix source)
{
    assert(destination.rows == source.rows && "Destination and Source row lengths must be the same!");
    assert(destination.columns == source.columns && "Destination and Source column lengths must be the same!");

    for (size_t i = 0; i < destination.rows; ++i)
    {
        for (size_t j = 0; j < destination.columns; ++j)
        {
            MAT_AT(destination, i, j) = MAT_AT(source, i, j);
        }
    }
}

double matrix_at(NCMatrix matrix, size_t row, size_t column)
{
    assert((row < matrix.rows) && "Matrix row out of bounds!");
    assert((column < matrix.columns) && "Matrix column out of bounds");

    return MAT_AT(matrix, row, column);
}

void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second)
{
    assert((first.columns == second.rows) && "First columns must be the same as second rows");
    assert((first.rows == destination.rows && second.columns == destination.columns) && "Destination dimensions must be correct!");

    for (size_t i = 0; i < destination.rows; ++i)
    {
        for (size_t j = 0; j < destination.columns; ++j)
        {
            MAT_AT(destination, i, j) = 0;

            for (size_t k = 0; k < first.columns; ++k)
            {
                MAT_AT(destination, i, j) += MAT_AT(first, i, k) * MAT_AT(second, k, j);
            }
        }
    }
}

void matrix_sum(NCMatrix destination, NCMatrix first, NCMatrix second)
{
    assert((first.rows == second.rows && second.rows ==  destination.rows) && "Matrix rows must be the same!");
    assert((first.columns == second.columns && second.columns ==  destination.columns) && "Matrix columns must be the same!");

    for (size_t i = 0; i < destination.rows; ++i)
    {
        for (size_t j = 0; j < destination.columns; ++j)
        {
            MAT_AT(destination, i, j) = MAT_AT(first, i, j) + MAT_AT(second, i, j);
        }
    }
}


void matrix_difference(NCMatrix destination, NCMatrix first, NCMatrix second)
{
    assert((first.rows == second.rows && second.rows ==  destination.rows) && "Matrix rows must be the same!");
    assert((first.columns == second.columns && second.columns ==  destination.columns) && "Matrix columns must be the same!");

    for (size_t i = 0; i < destination.rows; ++i)
    {
        for (size_t j = 0; j < destination.columns; ++j)
        {
            MAT_AT(destination, i, j) = MAT_AT(first, i, j) - MAT_AT(second, i, j);
        }
    }
}


double matrix_sum_of_values(NCMatrix matrix)
{
    double sum = 0;

    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            sum += MAT_AT(matrix, i, j);
        }
    }

    return sum;
}

void matrix_scale(NCMatrix matrix, double scalar)
{
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            MAT_AT(matrix, i, j) *= scalar;
        }
    }
}

void matrix_print(NCMatrix matrix)
{
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            printf("%f\t", MAT_AT(matrix, i, j));
        }

        printf("\n");
    }

    printf("\n");
}

void matrix_random(NCMatrix matrix)
{
    srand(get_seed());

    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            MAT_AT(matrix, i, j) = 2 * (double)rand() / RAND_MAX - 1;
        }
    }
}

void matrix_zero(NCMatrix matrix)
{
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            MAT_AT(matrix, i, j) = 0.0;
        }
    }
}

void apply_to_matrix(NCMatrix matrix, function_type function)
{
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            MAT_AT(matrix, i, j) = function(MAT_AT(matrix, i, j));
        }
    }
}

void matrix_transpose_inplace(NCMatrix* matrix)
{
    size_t rows = matrix->rows;

    matrix->rows = matrix->columns;
    matrix->columns = rows;
}

NCMatrix matrix_transpose(NCMatrix matrix)
{
    NCMatrix result = matrix_allocate(matrix.columns, matrix.rows);
    memcpy(result.numbers, matrix.numbers, matrix.rows * matrix.columns);

    return result;
}


void matrix_delete(NCMatrix matrix)
{
    free(matrix.numbers);
}

NCVector vector_allocate(size_t points)
{
    NCVector result;

    result.length = points;
    result.numbers = malloc(sizeof(*result.numbers) * points);

    assert(result.numbers != NULL);

    return result;
}

void vector_initialize(NCVector vector, const double *initializer, size_t initializer_size)
{
    assert((vector.length == initializer_size) && "Vector and Initializer lengths must be the same!");

    for (size_t i = 0; i < initializer_size; ++i)
    {
        VEC_AT(vector, i) = initializer[i];
    }
}

double vector_at(NCVector vector, size_t position)
{
    assert((position < vector.length) && "Vector out of bounds!");

    return VEC_AT(vector, position);
}

double vector_dot(NCVector first, NCVector second)
{
    assert((first.length == second.length) && "Lengths of the vectors must be the same!");

    double sum = 0;

    for (size_t i = 0; i < first.length; ++i)
    {
        sum += VEC_AT(first, i) * VEC_AT(second, i);
    }

    return sum;
}

double vector_magnitude(NCVector vector)
{
    double result = 0;

    for (size_t i = 0; i < vector.length; ++i)
    {
        result += pow(VEC_AT(vector, i), 2);
    }

    return sqrt(result);
}

void vector_sum(NCVector destination, NCVector first, NCVector second)
{
    assert((first.length == second.length && second.length == destination.length) && "Lengths of the vectors must be the same!");

    for (size_t i = 0; i < destination.length; ++i)
    {
        VEC_AT(destination, i) = VEC_AT(first, i) + VEC_AT(second, i);
    }
}

void vector_scale(NCVector vector, double scalar)
{
    for (size_t i = 0; i < vector.length; ++i)
    {
        VEC_AT(vector, i) *= scalar;
    }
}

void vector_print(NCVector vector)
{
    for (size_t i = 0; i < vector.length; ++i)
    {
        printf("%f\t", VEC_AT(vector, i));
    }

    printf("\n");
}

void vector_random(NCVector vector)
{
    srand(get_seed());

    for (size_t i = 0; i < vector.length; ++i)
    {
        VEC_AT(vector, i) = (double)rand() / RAND_MAX;
    }
}

void apply_to_vector(NCVector vector, function_type function)
{
    for (size_t i = 0; i < vector.length; ++i)
    {
        VEC_AT(vector, i) = function(VEC_AT(vector, i));
    }
}

void vector_delete(NCVector vector)
{
    free(vector.numbers);
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
