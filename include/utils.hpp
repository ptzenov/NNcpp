#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <stdio.h>
#include <stdlib.h>

#define NUM_PFTS 1
#define NUM_AFTS 3


enum NEURON_TYPE  {INPUT = 0 , PROCESSING = 1, OUTPUT = 2, BIAS = 3};
enum ACTIVATION_ORDER {SYNCHRONOUS = 0 , RANDORDER = 1, TOPOLOGICAL = 2, FIXED = 3 };

enum PROPAGATION_F_TYPE {WSUM = 0};
enum ACTIVATION_F_TYPE {HEAVISIDE = 0 ,TANH = 1 ,FERMI = 2};
enum OUTPUT_F_TYPE {identity = 0 };

void log_msg(FILE* fp, char const * mesage, char const * file, int line);




#endif
