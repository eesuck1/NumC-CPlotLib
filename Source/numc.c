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

double matrix_at(NCMatrix matrix, size_t row, size_t column)
{
    assert((row < matrix.rows) && "Matrix row out of bounds!");
    assert((column < matrix.columns) && "Matrix column out of bounds");

    return MAT_AT(matrix, row, column);
}

void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second)
{
    assert((first.columns == second.rows) && "First columns must be the sane as second rows");
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

void matrix_random(NCMatrix matrix, unsigned int random_state)
{
    srand(random_state);

    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            MAT_AT(matrix, i, j) = (double)rand() / RAND_MAX;
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

void vector_random(NCVector vector, unsigned int random_state)
{
    srand(random_state);

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

    result.weights = number_of_layers;
    result.matrices = malloc(sizeof(*result.matrices) * number_of_layers);

    assert(result.matrices != NULL);

    return result;
}

NCWeights weights_initialize(NCWeights weights, const NCMatrix *initializer_list, size_t initializer_size)
{
    assert((weights.weights == initializer_size) && "Model and Initializer lengths must be the same!");

    for (size_t i = 0; i < initializer_size; ++i)
    {
        weights.matrices[i] = initializer_list[i];
    }

    return weights;
}

NCMatrix weights_at(NCWeights weights, size_t position)
{
    assert((position < weights.weights) && "Model out of bounds!");

    return weights.matrices[position];
}

void weights_print(NCWeights weights)
{
    for (size_t i = 0; i < weights.weights; ++i)
    {
        printf("Layer %zu\n\n", i);

        matrix_print(weights_at(weights, i));
    }
}
