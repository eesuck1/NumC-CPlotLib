#include "Source/numc.h"
#include "Source/cplotlib.h"

double foo(double x) { return sin(x / 50) * 15; }
double boo(double x) { return x * 10 - 300; }
double baz(double x) { return x * x * x / 1000; }

int main()
{
    NCMatrix first = matrix_allocate(3, 3);
    NCMatrix second = matrix_allocate(3, 3);
    NCMatrix destination = matrix_allocate(3, 3);

    matrix_random(first, 0);
    matrix_random(second, 42);

    matrix_print(first);
    matrix_print(second);

    matrix_sum(destination, first, second);
    matrix_print(destination);

    NCVector v_first = vector_allocate(3);
    NCVector v_second = vector_allocate(3);
    NCVector v_destination = vector_allocate(3);

    vector_random(v_first, 9);
    vector_random(v_second, 10);

    vector_print(v_first);
    vector_print(v_second);

    vector_sum(v_destination, v_first, v_second);
    vector_print(v_destination);

    return 0;
}
