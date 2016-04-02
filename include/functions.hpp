#ifndef _FUNCTIONS_HPP
#define _FUNCTIONS_HPP


#include <cmath>
#include "utils.hpp"

float nn_wsum(float* weights , float* inputs, int N);

float nn_tanh(float net,float astate, float thold);
float nn_fermi(float net, float astate, float thold);
float nn_heaviside(float net, float astate, float thold);

typedef float (*pfunction)(float*, float*,int);
typedef float (*afunction)(float, float,float);


extern pfunction propagationFunctions[NUM_PFTS];
extern afunction  activationFunctions[NUM_AFTS];
#endif


