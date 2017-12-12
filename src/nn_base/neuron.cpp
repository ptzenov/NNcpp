#include <neuron.hpp>
#include <stdlib.h>

// nothing much to free here.
Neuron::~Neuron(){
	this->pf = NULL;
	this->af = NULL;
}

Neuron::Neuron(){
	idx = -1;
}

Neuron::Neuron(const Neuron& a){
	idx = a.idx; ntype = a.ntype;

	pftype = a.pftype;
	aftype = a.aftype; oftype = a.oftype;

	astate = a.astate; thold  = a.thold;
	net = a.net; pf = a.pf; af = a.af;
}

Neuron::Neuron(float* line){

	this->idx = (unsigned int) line[0];
	this->ntype = (NEURON_TYPE) line[1];
	this->pftype = (PROPAGATION_F_TYPE) line[2];
	this->aftype = (ACTIVATION_F_TYPE)line[3];
	this->oftype = (OUTPUT_F_TYPE)line[4];

	// and two floats
	this->astate=  line[5];
	this->thold= line[6];

	this->pf = propagationFunctions[(unsigned int)this->pftype];
	this->af = activationFunctions[(unsigned int) this->aftype];
	this->net = 0.;
}


void  Neuron::toFloatArray(float res[NPROPS]){

	res[0] = (float)idx; res[1] = (float)ntype; res[2] = (float)pftype;
	res[3] = (float)aftype; res[4] = (float)oftype; res[5] = astate;  res[6] = thold;

}

void Neuron::fromFloatArray(float input[NPROPS]){

	idx = (unsigned int) input[0];
	ntype= (NEURON_TYPE) input[1];
	pftype = (PROPAGATION_F_TYPE)input[2];
	aftype = (ACTIVATION_F_TYPE) input[3];
	oftype = (OUTPUT_F_TYPE) input[4];
	astate = input[5];
	thold  = input[6];

	this->pf = propagationFunctions[(unsigned int)pftype];
	this->af = activationFunctions[(unsigned int) aftype];
	this->net = 0.;

}

void Neuron::print(){
	std::cout<<"this is me, dad!:\n ";
	float me[NPROPS];
	this->toFloatArray(me);
	for(int i=0;i<NPROPS;i++)
		std::cout << me[i] << " ";

	std::cout<< "\n";
}


/** Calculate the incoming signal into the current neuron. Apply propagation function onto weights and states.
 * @param weights -> the weights matrix of the current network.
 * @param states  -> the states vector of the current network, states[j] is the current state of the j^th neuron.
 * @param N -> total number of neurons in the network (equals the number of rows and cols in the network)
 */
void Neuron::propagate(float* weights,float* states, int N){
	// propagation shall be executed only for neurons different from bias n input neurons!
	if (this->ntype != BIAS && this->ntype != INPUT)
		this->net = (*this->pf)(weights+N*this->idx,states,N);
}

/**
 * activates the neuron as a function of it net parameter
 */
void Neuron::activate(){
	this->astate = (*this->af)(this->net,this->astate,this->thold);
}

// retrieves the activation state of the neuron, possibly after applying an output function
float Neuron::output(){

	//TODO: generalize for arbitrary output function
	return this->astate;

}

/** getters and setters for the neuron attributes*/
float Neuron::getThreshold(){return this->thold;}
void Neuron::setThreshold(float t){
	this->thold = t;
}

unsigned int Neuron::getIdx(){return this->idx;}
void Neuron::setIdx(unsigned int newidx){
	this->idx = newidx;
}

NEURON_TYPE Neuron::getNType(){return this->ntype;}
void Neuron::setNType(NEURON_TYPE ty){
	this->ntype=ty;
}

float Neuron::getAState(){return this->astate;}


float Neuron::getNet(){return this->net;}

void Neuron::setNet(float newNet){
	this->net = newNet;
}


PROPAGATION_F_TYPE Neuron::getPFType(){return this->pftype;}
void Neuron::setPFType(PROPAGATION_F_TYPE pfnewtype){
	this->pftype = pfnewtype;
	this->pf = propagationFunctions[(unsigned int)this->pftype];
}

ACTIVATION_F_TYPE Neuron::getAFType(){return this->aftype;}
void Neuron::setAFType(ACTIVATION_F_TYPE afnewtype){
	this->aftype = afnewtype;
	this->af = activationFunctions[(unsigned int) this->aftype];
}


