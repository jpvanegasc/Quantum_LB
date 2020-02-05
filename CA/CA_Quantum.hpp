#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Constants.hpp"

class Automata{
    private:
        std::complex<double> phi[Lx];
    public:
        Automata(double mu, double sigma);
        void normalize(void);
        void collision(int i_start);
        void advection(void);
        void show(void);
        void grafique(int t, std::ofstream &file);
        void wave(std::ofstream &file);
        double phi2(int ix){return std::norm(phi[ix]);}
};

Automata::Automata(double mu, double sigma){
    for(int i=0; i<Lx; i++){
        // Gaussian packet
        double x=0, y=0;
        if(i==0) x=1;
        //x = (std::exp(-0.5*(((i-mu)*(i-mu))/(sigma*sigma))))/(sigma*std::sqrt(2*M_PI));
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
void Automata::grafique(int t, std::ofstream &file){
    for(int i=0; i<Lx; i++)
        file << i << "\t" << t << "\t" << std::norm(phi[i]) << "\n";
}
void Automata::wave(std::ofstream &file){
    for (int ix=0; ix<Lx; ix++){
        file << ix << '\t' << std::norm(phi[ix]) << '\n';
    }
    
}
