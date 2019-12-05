#include<iostream>
#include<fstream>

#include"CA_Quantum.hpp"


int main(void)
{
	int t_max = 100;
	Automata QuantumStuffBaby(1);

	for(int t=0; t<t_max; t++){
		QuantumStuffBaby.grafique(t);
		QuantumStuffBaby.collision(0);
		QuantumStuffBaby.collision(1);
		//QuantumStuffBaby.collision(0);
		std::cout << "\n";
	}

	return 0;
}