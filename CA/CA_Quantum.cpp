#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.h"

const int Lx = 30;

class Automata{
	private:
		std::complex<double> juan[Lx];
	public:
		Automata(void);
		void normalize(void);
		void collision(void);
		void advection(void);
		void show(bool PrintNew);
		void grafique(int t);
};

int main(void)
{
	Automata QuantumStuffBaby;

	for(int t=0; t<100; t++){
		QuantumStuffBaby.collision();
		QuantumStuffBaby.grafique(t);
	}

	return 0;
}

Automata::Automata(void)
{
	Crandom ran64(1);

	for(int i=0; i<Lx; i++){
		juan[i] = complex <double>(ran64.r(), ran64.r());
	}
	normalize();
}
void Automata::normalize(void)
{
	std::complex <double> sum (0,0) , rsum;

	for (int i=0; i<Lx; i++){
			sum += std::norm(juan[i]);
	}

	rsum= sqrt(sum);
	for (int i=0; i<Lx; i++)
		juan[i]= juan[i]/rsum;
	

}
void Automata::show(bool PrintNew)
{
	for (int i=0; i<Lx; i++)
		std::cout << juan[i] << " | ";
	std::cout << std::endl;
}
void Automata::collision(void)
{
	double theta = M_PI/3; 
    complex <double> j (0,1);
	complex <double> uno (1,0);

    for(int i=0; i<Lx; i += 2){
		juan[(i-1+Lx)%Lx]= j*sin(theta)*juan[(i-1+Lx)%Lx] + uno* cos(theta)*juan[i];
		juan [i]= uno* cos(theta)*juan[(i-1+Lx)%Lx] + j*sin(theta)*juan[i];
	}
}

void Automata::grafique(int t)
{
	for(int i=0; i<Lx; i++){
		std::cout<< i << "\t" << t << "\t" << std::norm(juan[i]) << "\n";
	}

}