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

double* use_to_array(const double *array, const size_t length, function_type function)
{
    double* result = (double*)malloc(length * sizeof(double));

    for (size_t i = 0; i < length; i++)
    {
        result[i] = function(array[i]);
    }

    return result;
}

NCMatrix matrix_allocate(size_t columns, size_t rows)
{
    NCMatrix matrix;

    matrix.columns = columns;
    matrix.rows = rows;
    matrix.pointer = malloc(sizeof(*matrix.pointer) * columns * rows);

    assert(matrix.pointer != NULL);

    return matrix;
}

void matrix_dot(NCMatrix destination, NCMatrix first, NCMatrix second)
{
    assert((first.columns == second.rows) && "First columns must be the sane as second rows");
    assert((first.rows == destination.rows && second.columns == destination.columns) && "Destination dimensions must be correct!");

    for (size_t i = 0; i < destination.rows; ++i)
    {
        for (size_t j = 0; j < destination.columns; ++j)
        {
            // TODO: not implemented
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

void matrix_delete(NCMatrix matrix)
{
    free(matrix.pointer);
}

NCVector vector_allocate(size_t points)
{
    NCVector result;

    result.length = points;
    result.pointer = malloc(sizeof(*result.pointer) * points);

    assert(result.pointer != NULL);

    return result;
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

void vector_sum(NCVector destination, NCVector first, NCVector second)
{
    assert((first.length == second.length && second.length == destination.length) && "Lengths of the vectors must be the same!");

    for (size_t i = 0; i < destination.length; ++i)
    {
        VEC_AT(destination, i) = VEC_AT(first, i) + VEC_AT(second, i);
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

void vector_delete(NCVector vector)
{
    free(vector.pointer);
}

