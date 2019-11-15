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

Automata::Automata(void){
	Crandom ran64(1);
	
	for(int i=0; i<Lx; i++){
		juan[i] = std::complex <double>(ran64.r(), ran64.r());
	}
	normalize();
}
void Automata::normalize(void){
	double sum{0}; std::complex <double> rsum (0,0);

	#pragma omp parallel for reduction(+: sum)
	for (int i=0; i<Lx; i++){
			sum += std::norm(juan[i]);
	}
	rsum = sqrt(sum);

	#pragma omp parallel for
	for (int i=0; i<Lx; i++)
		juan[i]= juan[i]/rsum;
	

}
void Automata::show(bool PrintNew){
	for (int i=0; i<Lx; i++)
		std::cout << juan[i] << " | ";
	std::cout << std::endl;
}
void Automata::collision(void){
	double theta = M_PI/3; 
    complex <double> j (0,1);
	complex <double> uno (1,0);

    for(int i=0; i<Lx; i += 2){
		juan[(i-1+Lx)%Lx]= j*sin(theta)*juan[(i-1+Lx)%Lx] + uno* cos(theta)*juan[i];
		juan [i]= uno* cos(theta)*juan[(i-1+Lx)%Lx] + j*sin(theta)*juan[i];
	}
}

void Automata::grafique(int t){
	for(int i=0; i<Lx; i++){
		std::cout<< i << "\t" << t << "\t" << std::norm(juan[i]) << "\n";
	}

}