#include<iostream>
#include<fstream>
#include<cmath>
#include"Random64.h"

const int Lx = 30;

class Automata{
	private:
		double juan[Lx];
	public:
		Automata(void){
			for(int i=0; i<Lx; i++){
				juan[i] = 0;
				if(i==15 || i==16)
					juan[i] = 1.0/M_SQRT2;
			}
		}
		void collision(void);
		void advection(void);
		void show(void){
			for (int i=0; i<Lx; i++)
					std::cout << juan[i] << " | ";
			std::cout << std::endl;
		}
};

int main(void){
	Automata QuantumStuffBaby;

	QuantumStuffBaby.show();

	return 0;
}