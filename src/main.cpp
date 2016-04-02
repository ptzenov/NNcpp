#include "Neuron.hpp"
#include "NN_io.hpp"
#include "Network.hpp"
#include <iostream>

int main(){

	std::cout<<"Hello";
	Network net("src/tempfilenew.nn",'t');

	net.writeNetworkToFile("src/tempfilecopy.nn",'t');


}
