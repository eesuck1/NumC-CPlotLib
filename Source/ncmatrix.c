#include "ncmatrix.h"

static long long get_seed()
{
    static long long SEED = 0;

    return time(NULL) + SEED++;
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
