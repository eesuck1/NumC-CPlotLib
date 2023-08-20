#include "Source/numc.h"
#include "Source/cplotlib.h"

int main()
{
    NCVector vector = vector_allocate(3);
    vector_random(vector, 0);

    vector_print(vector);
    printf("%f", vector_magnitude(vector));

    return 0;
}
