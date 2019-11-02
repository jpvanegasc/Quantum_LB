#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.h"

const int Lx = 30;

class Automata{
	private:
		double juan[Lx];
	public:
		Automata(void);
		void normalize(void);
		void collision(void);
		void advection(void);
		void show(void);
};

int main(void){
	Automata QuantumStuffBaby;

	QuantumStuffBaby.normalize();

	QuantumStuffBaby.show();

	return 0;
}

Automata::Automata(void){
	for(int i=0; i<Lx; i++){
		juan[i] = 0;
		if(i==15 || i==16)
			juan[i] = 1.0;
	}
}

void Automata::normalize(void){
	double sum = 0, rsum;

	for (int i=0; i<Lx; i++){
		sum += juan[i]*juan[i];
	}

	rsum= sqrt(sum);
	for (int i=0; i<Lx; i++){
		juan[i]= juan[i]/rsum;
	}

}
void Automata::show(void){
	for (int i=0; i<Lx; i++)
		std::cout << juan[i] << " | ";
		std::cout << std::endl;
	}