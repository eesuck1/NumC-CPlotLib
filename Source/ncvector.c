#include "ncvector.h"

long long get_seed()
{
    static long long SEED = 0;

    return time(NULL) + SEED++;
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