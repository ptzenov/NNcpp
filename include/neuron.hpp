#ifndef _NEURON_HPP
#define _NEURON_HPP

#include <iostream>
#include <stdlib.h>

#include <functions.hpp>
#include <utils.hpp>

// number of properties characterizing the neuron, which will be stored in
// the outputfile!

#define NPROPS 7


class Neuron {

	private:
		unsigned int idx; NEURON_TYPE ntype;
		PROPAGATION_F_TYPE pftype;
		ACTIVATION_F_TYPE aftype;
		OUTPUT_F_TYPE oftype;
		pfunction pf; afunction af;

		//activation state and threshold of the neuron
		float  astate , thold;

		// todo: allow for different output function;
		// the net input value to the neuron!
		float net;

	public:

		/** destructor */
		~Neuron();

		/** default constructor */
		Neuron();

		/** construct a neuron from a line specifying its params.*/
		Neuron(float* line);

		/** copy constructor*/
		Neuron(const Neuron& b);

		/** convert the neuron to a float array for storage in a file */
		void fromFloatArray(float input[NPROPS]);
		void toFloatArray(float output[NPROPS]);

		/** print the neuron to the current output stream */
		void print();

	       /** Calculate the incoming signal into the current neuron. Apply propagation function onto weights and states.
		* @param weights -> the weights matrix of the current network.
		* @param states  -> the states vector of the current network, states[j] is the current state of the j^th neuron.
		* @param N -> total number of neurons in the network (equals the number of rows and cols in the network)
		*/
		void propagate(float* weights,float* states, int N);

		/**
		* activates the neuron as a function of it's net parameter
		*/
		void activate();

		// retrieves the activation state of the neuron, possibly after applying an output function
		float output();

		/** getters and setters for the neuron attributes*/

		float getThreshold();
		void setThreshold(float thld);

		unsigned int getIdx();
		void setIdx(unsigned int newidx);

		NEURON_TYPE getNType();
		void setNType(NEURON_TYPE ty);

		float getAState();

		float getNet();
		void setNet(float newNet);

		PROPAGATION_F_TYPE getPFType();
		void setPFType(PROPAGATION_F_TYPE pfnewtype);

		ACTIVATION_F_TYPE getAFType();
		void setAFType(ACTIVATION_F_TYPE afnewtype);



};


#endif
