#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"CA_Quantum.hpp"


int main(void)
{
	Automata QuantumStuffBaby;

	for(int t=0; t<100; t++){
		QuantumStuffBaby.collision();
		QuantumStuffBaby.grafique(t);
	}

	return 0;
}