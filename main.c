//#include "Source/cplotlib.h"
#include "Source/numc.h"

int main()
{
    NCLayers layers = layer_allocate(4);
    size_t neurons[4] = {2, 4, 5, 1};
    function_type activations[4] = {activation_identity, activation_identity, activation_identity, activation_identity };
    layer_initialize(layers, neurons, activations);
    layer_print(layers);

    return 0;
}
