#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.h"

const int Lx = 30;
const double theta = M_PI/4.0; 
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);
const std::complex <double> j (0,1);
const std::complex <double> uno (1,0);

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
		//double x=ran64.r(), y=ran64.r();
		double x=0, y=0;
		if (i==0) x = 1;
		//if (i==16) x = 1;
		juan[i] = std::complex <double>(x, y);
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
		std::cout << juan[i] << "\t|\t";
	std::cout << std::endl;
}
void Automata::collision(void){
    for(int i=0; i<Lx; i++){
		juan[(i-1+Lx)%Lx] = j*sin_theta*juan[(i-1+Lx)%Lx] + uno*cos_theta*juan[i];
		juan[i] = uno*cos_theta*juan[(i-1+Lx)%Lx] + j*sin_theta*juan[i];
	}
	normalize();
}

void Automata::grafique(int t){
	for(int i=0; i<Lx; i++){
		std::cout<< i << "\t" << t << "\t" << std::norm(juan[i]) << "\n";
	}

}