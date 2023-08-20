#include "Source/numc.h"
#include "Source/cplotlib.h"

int main()
{
    NCMatrix m0 = matrix_allocate(3, 3);
    NCMatrix m1 = matrix_allocate(3, 3);
    NCMatrix m2 = matrix_allocate(3, 3);

    NCMatrix matrix[3] = {m0, m1, m2};

    matrix_random(m0, 0);
    matrix_random(m1, 1);
    matrix_random(m2, 2);

    NCWeights weights = weights_allocate(3);
    weights_initialize(weights, matrix, 3);

    weights_print(weights);

    return 0;
}
