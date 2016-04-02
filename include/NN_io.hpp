#ifndef _NN_IO_HPP
#define _NN_IO_HPP

#include "Neuron.hpp"
#include "utils.hpp"


void readNetwork_b(const char*, Neuron*&, float*&, int&, int&);
void readNetwork_t(const char*, Neuron*&, float*&, int&,int&);

void writeNetwork_t(const char*, Neuron  const * , float const *, const int& , const int&);
void writeNetwork_b(const char*, Neuron  const * , float const *, const int& , const int&);

void read_inputs(FILE* fp, float*& inputs,int& inputsize);




#endif



