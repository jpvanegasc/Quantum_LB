#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.h"

const int Lx = 30;
const double p= 0.5;
const double q= 0.5;

class Automata{
	private:
		double juan[Lx][2];
		double pablo[Lx][2];
	public:
		Automata(void);
		void normalize(void);
		void collision(void);
		void advection(void);
		void show(bool PrintNew);
};

int main(void)
{
	Automata QuantumStuffBaby;

	QuantumStuffBaby.normalize();

	QuantumStuffBaby.show(false);

	return 0;
}

Automata::Automata(void)
{
	for(int i=0; i<Lx; i++)
		for (int j=0; j<2; j++){
			juan[i][j] = 0;
			if(i==15 || i==16)
				juan[i][j] = 1.0;
	}
}
void Automata::normalize(void)
{
	double sum = 0, rsum;

	for (int i=0; i<Lx; i++){
			sum += (juan[i][0]+juan[i][1])*(juan[i][0]+juan[i][1]);
	}

	rsum= sqrt(sum);
	for (int i=0; i<Lx; i++)
		for(int j=0; j<2; j++){
			juan[i][j]= juan[i][j]/rsum;
	}

}
void Automata::show(bool PrintNew)
{
	if(PrintNew){
		for (int i=0; i<Lx; i++)
			std::cout << pablo[i][0] + pablo[i][1] << " | ";
		std::cout << std::endl;
	}else{
		for (int i=0; i<Lx; i++)
			std::cout <<juan[i][0] + juan[i][1]<< " | ";
		std::cout << std::endl;
	}
}
void Automata::collision(void)
{
	//Ni idea como je...
}