//#include "Source/cplotlib.h"
#include "Source/numc.h"

int main()
{
    size_t neurons[4] = {2, 4, 4, 2};
    function_type activations[4] = {activation_identity, activation_leaky_relu, activation_leaky_relu, activation_identity};

    NCMatrix input_data = matrix_allocate(1, 2);
    matrix_random(input_data);

    NCPerceptron perceptron = perceptron_allocate(4, neurons, activations);
    perceptron_set_input(perceptron, input_data);

    perceptron_print(perceptron);
    perceptron_forward(perceptron);
    perceptron_print(perceptron);

    return 0;
}
