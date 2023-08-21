//#include "Source/cplotlib.h"
#include "Source/numc.h"

int main()
{
    size_t neurons[4] = {2, 4, 4, 2};
    function_type activations[4] = {activation_identity, activation_identity, activation_identity, activation_identity};

    NCPerceptron perceptron = perceptron_allocate(4, neurons, activations);

    perceptron_print(perceptron);

    return 0;
}
