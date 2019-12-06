#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.hpp"

const int Lx = 30;

const double theta = M_PI/4.0; 
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);

const std::complex <double> j (0,1);
const std::complex <double> uno (1,0);

class Automata{
    private:
        std::complex<double> phi[Lx];
    public:
        Automata(unsigned long long seed);
        void normalize(void);
        void collision(int i_start);
        void advection(void);
        void show(void);
        void grafique(int t);
};

Automata::Automata(unsigned long long seed){
    Crandom ran64(seed);
    
    for(int i=0; i<Lx; i++){
        //double x=ran64.r(), y=ran64.r();
        double x=0, y=0;
        if (i==15) x = 1;
        if (i==16) x = 1;
        phi[i] = std::complex <double>(x, y);
    }
    normalize();
}
void Automata::normalize(void){
    double sum{0}; std::complex <double> rsum (0,0);

    #pragma omp parallel for reduction(+: sum)
    for (int i=0; i<Lx; i++)
        sum += std::norm(phi[i]);
    rsum = sqrt(sum);

    #pragma omp parallel for
    for (int i=0; i<Lx; i++)
        phi[i]= phi[i]/rsum;
}
/**
 * Evolves one time step the state vector 
 */
void Automata::collision(int i_start){
    for(int i=i_start; i<Lx; i+=2){
        std::complex <double> phi_i = phi[i], phi_i_minus_one = phi[(i+1+Lx)%Lx];
        
        phi[(i+1+Lx)%Lx] = sin_theta*(j*phi_i_minus_one) + cos_theta*(uno*phi_i);
        phi[i] = cos_theta*(uno*phi_i_minus_one) + sin_theta*(j*phi_i);
    }
}
void Automata::show(void){
    for (int i=0; i<Lx; i++)
        std::cout << std::norm(phi[i]) << "\t|\t";
    std::cout << std::endl;
}
void Automata::grafique(int t){
    for(int i=0; i<Lx; i++)
        std::cout<< i << "\t" << t << "\t" << std::norm(phi[i]) << "\n";
}
