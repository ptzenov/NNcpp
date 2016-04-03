#include "Neuron.hpp"
#include "NN_io.hpp"
#include "Network.hpp"
#include <iostream>
#include <stdio.h>

int main(){

	std::cout<<"Hello";
	Network net("src/binaryANDOR.nn",'t');
	net.printNetworkToConsole();
	net.printNetworkWeightsToConsole();

	std::cout << "reading some inputs from stdin. Terminate input by entering -1! \n ";
	int inputsize;
	float* inputs;
	read_inputs(stdin, inputs,inputsize);

	std::vector<float> outputs = net.processdata(inputs,inputsize);

//	std::cout<<"Post-processing network: \n";
//	net.printNetworkToConsole();


	for(int n  = 0 ; n < outputs.size(); n++)
		std::cout<< "o["<<n<<"] = " << outputs[n] << "\n";

	std::cout<<"BUBYE";

}
