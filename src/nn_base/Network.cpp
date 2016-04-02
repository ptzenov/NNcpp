
#include "Network.hpp"
#include "NN_io.hpp"
#include <stdlib.h>

Network::Network(char const * filename,char mode){

	Neuron* nrns;
	if (mode == 't'){ //read a text file
		readNetwork_t(filename,nrns,this->weights,this->N,this->M);
	}else{	// read a binary file
		readNetwork_b(filename,nrns,this->weights,this->N,this->M);
	}

	init(nrns);
}


void Network::init(Neuron*& neur){

	this->neurons.clear();
	this->states = new float[N];
	for (int n = 0; n<N; n++){

		int idx = neur[n].getIdx();

		switch (neur[n].getNType()){
		case INPUT:
			inputsIdx.push_back(idx); break;
		case PROCESSING:
			processorsIdx.push_back(idx); break;
		case OUTPUT:
			outputsIdx.push_back(idx); break;
		default:
			log_msg(stderr,"error by network initialization. Neuron type unknown!",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}

		states[n] = neur[n].getAState();
		neurons.push_back(neur[n]);
	}

	setActivationOrder(TOPOLOGICAL);

}
// construct a new network( with newly allocated memory) which contains a and b as subnetworks,
// with zeroes in the interface between neurons from a and b.
Network::Network(Network a, Network b){

	log_msg(stderr,"TODO: implement network unification constructor.",__FILE__,__LINE__);
	exit(EXIT_FAILURE);

}

void Network::setActivationOrder(ACTIVATION_ORDER newActivOrder, int* ordering){

	switch(newActivOrder){
	case SYNCHRONOUS:
		log_msg(stderr,"TODO-implement synchronous execution order",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
		break;

	case RANDORDER:
		log_msg(stderr,"TODO-implement random execution order",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
		break;

	case TOPOLOGICAL:

		orderIdx.resize(3);
		orderIdx[0].resize(inputsIdx.size());
		orderIdx[1].resize(processorsIdx.size());
		orderIdx[2].resize(outputsIdx.size());

		for(unsigned int n = 0; n<inputsIdx.size();n++)
			orderIdx[0][n] = inputsIdx[n];

		for(unsigned int n = 0; n<processorsIdx.size();n++)
			orderIdx[1][n] = processorsIdx[n];

		for( unsigned int n = 0; n<outputsIdx.size();n++)
			orderIdx[2][n] = outputsIdx[n];
		break;

	case FIXED:
		log_msg(stderr,"TODO-implement fixed execution order",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
		break;

	default:
		log_msg(stderr,"Undefined execution order",__FILE__,__LINE__);
		exit(EXIT_FAILURE); break;
	}
	this->activation_order = newActivOrder;
}

ACTIVATION_ORDER Network::getActivationOrder(){
	return activation_order;
}


// process the data contained in the inputs vector and return the output states of the "output" type neurons
// as another float vector. Inputs must have the same size of inputsIdx otherwise an error will be returned.
// also the ith input inputs[i] is taken to be the input data for the inputsIdx[i]-th neuron in our network.
std::vector<float> Network::processdata(std::vector<float> in){


	if(in.size() != this->orderIdx[0].size()){
		log_msg(stderr,"Error.Inputs array size does not match the number of input neurons.Aborting",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	int Nsteps = orderIdx.size();

	//create the results vector;
	std::vector<float> res(this->orderIdx[Nsteps-1].size());

	// propagate inputs!
	for(unsigned int i = 0; i < orderIdx[0].size(); i++){

		//set the propagation funct. output; <- same as propagate!
		neurons[orderIdx[0][i]].setNet(in[i]);
		// activate the ith input neuron
		neurons[orderIdx[0][i]].activate();
		// calculate the output signal from the neuron and update the states variable.
		this->states[orderIdx[0][i]] = neurons[orderIdx[0][i]].output();
	}


	for(unsigned int step = 1; step < Nsteps-1;step++){
		// first
		for(unsigned int i = 0; i < orderIdx[step].size();i++){
			neurons[orderIdx[step][i]].propagate(this->weights,this->states,this->N);
			neurons[orderIdx[step][i]].activate();
		}
		for(unsigned int i = 0; i < orderIdx[step].size();i++){
			this->states[orderIdx[step][i]] = neurons[orderIdx[step][i]].output();
		}
	}

}

// destructor
Network::~Network(){

	free(weights);
	free(states);

	neurons.clear(); // <- will explicitly call neurons[n].~Neuron();
	inputsIdx.clear();
	processorsIdx.clear();
	outputsIdx.clear();

}



void Network::writeNetworkToFile(const char* filename,char mode){

	if (mode == 't'){
		writeNetwork_t(filename, &(this->neurons[0]), this->weights, this->N ,this->M);
	}else if (mode == 'b'){
		writeNetwork_b(filename, &(this->neurons[0]), this->weights, this->N ,this->M);
	}else{
		log_msg(stderr,"Error! Cannot write network to file. Write mode unrecognized.",__FILE__,__LINE__);
	}

}
