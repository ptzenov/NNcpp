#include "Neuron.hpp"
#include "NN_io.hpp"
#include "Network.hpp"
#include <iostream>
#include <stdio.h>

int main(){

	std::cout<<"Hello";
	Network net("src/binaryANDcopy.nn",'t');
	net.printNetoworkToConsole();

	std::cout << "reading some inputs from stdin. Terminate input by entering -1! \n ";
	int inputsize;
	float* inputs;
	read_inputs(stdin, inputs,inputsize);


	std::vector<float> outputs = net.processdata(inputs,inputsize);


	for(int n  = 0 ; n < outputs.size(); n++)
		std::cout<< "o["<<n<<"] = " << outputs[n] << "\n";

	std::cout<<"BUBYE";

}
