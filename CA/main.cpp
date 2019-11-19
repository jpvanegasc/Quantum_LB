#include<iostream>
#include<fstream>

#include"CA_Quantum.hpp"


int main(void)
{
	int t_max = 200;
	Automata QuantumStuffBaby;

	for(int t=0; t<t_max; t++){
		QuantumStuffBaby.grafique(t);
		QuantumStuffBaby.collision();
		std::cout << "\n";
	}

	return 0;
}