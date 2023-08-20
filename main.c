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
    printf("\n");
    matrix_print(second);
    printf("\n");

    matrix_sum(destination, first, second);
    matrix_print(destination);

    return 0;
}
