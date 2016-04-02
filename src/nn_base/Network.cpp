
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

		int idx = neur[n].getIdx() % N ;
		neur[n].setIdx((unsigned int) idx);
		switch (neur[n].getNType()){
		case INPUT:
			inputsIdx.push_back(idx); break;
		case PROCESSING:
			processorsIdx.push_back(idx); break;
		case OUTPUT:
			outputsIdx.push_back(idx); break;
		case BIAS:
			biasIdx.push_back(idx); break;
		default:
			log_msg(stderr,"error by network initialization. Neuron type unknown!",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}

		neurons.push_back(neur[n]);
		states[idx] = neur[n].getAState();

	}

	setActivationOrder(TOPOLOGICAL);
}

void Network::printNetoworkToConsole(){
	std::cout<< "Network size (" << this->N  << "," << M <<")";
	std::cout<< "\n->input neurons: \n";
	for(int n = 0; n < this->inputsIdx.size();n++)
	{	int idx = this->inputsIdx[n];
		std::cout << "(" << idx <<"," << neurons[idx].getNet() << "," << neurons[idx].getAState() <<"," << neurons[idx].getThreshold() <<") ";
	}

	std::cout<< "\n->bias neurons:\n";
	for(int n = 0; n < this->biasIdx.size();n++)
	{	int idx = this->biasIdx[n];
		std::cout << "(" << idx <<"," << neurons[idx].getNet() << "," << neurons[idx].getAState() <<"," << neurons[idx].getThreshold() <<") ";
	}

	std::cout<< "\n->processor neurons:\n";
	for(int n = 0; n < this->processorsIdx.size();n++)
	{	int idx = this->processorsIdx[n];
		std::cout << "(" << idx <<"," << neurons[idx].getNet() << "," << neurons[idx].getAState() <<"," << neurons[idx].getThreshold() <<") ";
	}


	std::cout<< "\n->output neurons:\n";
	for(int n = 0; n < this->outputsIdx.size();n++)
	{	int idx = this->outputsIdx[n];
		std::cout << "(" << idx <<"," << neurons[idx].getNet() << "," << neurons[idx].getAState() <<"," << neurons[idx].getThreshold() <<") ";
	}
	std::cout<<std::endl;


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

		orderIdx.resize(4);
		// activate the input and bias neurons first!
		orderIdx[0].resize(inputsIdx.size() );
		// activate the bias neurons second!
		orderIdx[1].resize( biasIdx.size() );

		// activate the processor neurons third
		orderIdx[2].resize( processorsIdx.size());
		// activate the output neurons last!
		orderIdx[3].resize( outputsIdx.size() );

		for(unsigned int n = 0; n<inputsIdx.size();n++)
			orderIdx[0][n] = inputsIdx[n];

		for(unsigned int n = 0; n<inputsIdx.size();n++)
			orderIdx[1][n] = biasIdx[n];

		for(unsigned int n = 0; n<processorsIdx.size();n++)
			orderIdx[2][n] = processorsIdx[n];


		for( unsigned int n = 0; n<outputsIdx.size();n++)
			orderIdx[3][n] = outputsIdx[n];
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
std::vector<float> Network::processdata( float const *  in, int const inputsize){

	std::cout<<"inputs index size: " << this->inputsIdx.size();
	if( inputsize > this->inputsIdx.size()){
		log_msg(stderr,"Error.Inputs array size is greater than  the number of input neurons.Aborting",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}


	int Nsteps = orderIdx.size();
	//create the results vector;
	std::vector<float> res(this->outputsIdx.size());
	// set inputs!
	for(unsigned int n = 0; n < inputsize; n++){
		//set the propagation funct. output; <- same as propagate!
		neurons[inputsIdx[n]].setNet(in[n]);
	}

	for (unsigned int step = 0; step < orderIdx.size();step++)
	{
		for(unsigned int n = 0; n < orderIdx[step].size();n++){
			neurons[orderIdx[step][n]].propagate(this->weights,this->states,this->N);
			neurons[orderIdx[step][n]].activate();
		}

		for(unsigned int i = 0; i < orderIdx[step].size();i++){
					this->states[orderIdx[step][i]] = neurons[orderIdx[step][i]].output();
		}
	}

	std::vector<float> outputs(this->outputsIdx.size());
	for(int n = 0 ; n < this->outputsIdx.size();n++)
		outputs[n] = neurons[outputsIdx[n]].output();

	return outputs;

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
