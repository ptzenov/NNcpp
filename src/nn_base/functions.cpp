#include <functions.hpp>

pfunction propagationFunctions[NUM_PFTS] = {&nn_wsum};
afunction activationFunctions[NUM_AFTS] = {&nn_heaviside,&nn_tanh,&nn_fermi};

float nn_wsum(float* weights, float* inputs, int N){
	float sum = 0.0f;
	for (int i = 0; i<N; i++)
		sum+=inputs[i]*weights[i];

	return sum;
}

// tanh(x) > 0 for x > 0 ! and spans the interval [-1;1]
// map it back to [0;1] via the transform (tan(x)+1)/2
float nn_tanh(float net,float astate, float thold){
	return ((float)std::tanh(net-thold)+1.)/2.;
}

// fermi(x) = 1/(1. + exp(-x)) spans the interval [0;1] for x in [-inf;inf];
// a parameter T (temperature) can be used to determine the slope of
// fermi(x) at x = 0! T is inversly proportional to the slope!
// TODO implement in the future
float nn_fermi(float net, float astate, float thold){
	return  1./(1.+std::exp(-(net-thold)));
}

// simple step function!
float nn_heaviside(float net, float astate, float thold){

	return (float)(net>thold);
}
