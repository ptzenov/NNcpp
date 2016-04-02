#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <vector>
#include "Neuron.hpp"
#include "NN_io.hpp"
#include "utils.hpp"
#include <stdlib.h>


class Network{

private:

	ACTIVATION_ORDER activation_order;

	/** lists with the indices of the inputs, outputs and the processor neurons in the newtwork.*/
	std::vector<int> inputsIdx; std::vector<int> outputsIdx; std::vector<int> processorsIdx;

	/** a vector with dynamically allocated neurons. */
	std::vector<Neuron> neurons;

	// an NxN matrix with the corresponding weights. TODO: implement with sparse mtrices
	float* weights;
	float* states;

	//execution order of the neurons.
	std::vector< std::vector<int> > orderIdx;
	// number of neurons and connections in the network
	int N,M;


	/**
	 * construct the network from a predefined set of neurons and weights. No new memory is allocated. Notice that
	 * since it is assumed that the network logically "owns" the neurons the class's destructor will attempt to
	 * free the neurons vector and the weights matrix. Careful for undesired memory conflicts.
	 * @param neur an array of this-> N neurons, ith  owned by the network.
	 **/

	void init(Neuron*& neur);





public:
	/**
	 * basic constructor for construction of the network from a file.
	 * @param filename the name of the file to read the network from. If file not exists return error.
	 * @param mode the IO mode under which the file ought to be open. give 'b' for binary and 't' for textual.
	 * The default execution order is set to be "topological", i.e. first all input neurons are activated, followed by the
	 * processing (all others - output) and lastly the output neurons. Dynamical memory is allocated for each neuron as well as
	 * for the weights matrix after reading the file.
	 **/

	Network(char const * filename,char  mode);

	/*construct a new network( with newly allocated memory) which contains a and b as subnetworks,
		with zeroes in the interface between neurons from a and b.*/
	Network(Network a, Network b);

	/*reset the activation order of the network*/
	void setActivationOrder(ACTIVATION_ORDER order,int* ordering = NULL);
	ACTIVATION_ORDER getActivationOrder();

	// process the data contained in the inputs vector and return the output states of the "output" type neurons
	// as another float vector. Inputs must have the same size of inputIdx otherwise an error will be returned.
	// also the ith input inputs[i] is taken to be the input data for the inputIdx[i]-th neuron in our network.
	std::vector<float> processdata(std::vector<float> inputs);

	// destructor
	~Network();

	void writeNetworkToFile(const char* filename,char mode);


};




#endif
