#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.hpp"
#include"Constants.hpp"

class Automata{
    private:
        std::complex<double> phi[Lx][dim], phi_new[Lx][dim]; int V[dim];
    public:
        Automata(double mu, double sigma);
        void normalize(void);
        void collide(void);
        void advect(void);
        void print(std::ofstream &file);
};

Automata::Automata(double mu, double sigma){
    double gauss_coef = 1.0/(sigma*std::sqrt(2*M_PI));
    
    for(int ix=0; ix<Lx; ix++){
        // Gaussian packet
        double x = gauss_coef*(std::exp(-0.5*(((ix-mu)*(ix-mu))/(sigma*sigma))));
        // Gaussian packet times e^ikx
        phi[ix][0] = std::complex<double> (x*std::cos(k*ix), x*std::sin(k*ix));
        phi[ix][1] = phi_new[ix][0] = phi_new[ix][1] = std::complex<double> (0, 0);
    }
    //normalize();
}

void Automata::normalize(void){
    std::complex<double> c_norm = (0, 0), c_norm_new = (0, 0);
    for(int ix=0; ix<Lx; ix++){
        c_norm += phi[ix][0] + phi[ix][1];
        c_norm_new += phi_new[ix][0] + phi_new[ix][1];
    }
    double norm = std::norm(c_norm), norm_new = std::norm(c_norm_new);
    if(norm == 0.0) norm = 1.0; if(norm_new == 0.0) norm_new = 1.0;

    for(int ix=0; ix<Lx; ix++){
        phi[ix][0] /= norm; phi[ix][1]/norm;
        phi_new[ix][0] /= norm_new; phi_new[ix][1] /= norm_new;
    }
}

void Automata::collide(void){
    for(int ix=0; ix<Lx; ix++){
        phi_new[(ix+1+Lx)%Lx][0] = uno*cos_theta*phi[ix][0] + j*sin_theta*phi[ix][1];
        phi_new[(ix-1+Lx)%Lx][1] = j*sin_theta*phi[ix][0] + uno*cos_theta*phi[ix][1];
    }
}

void Automata::advect(void){
    for(int ix=0; ix<Lx; ix++){
        phi[ix][0] = phi_new[ix][0];
        phi[ix][1] = phi_new[ix][1];
    }
}

void Automata::print(std::ofstream &file){
    for(int ix=0; ix<Lx; ix++){
        std::complex<double> phi_2 = 0;
        for(int i=0; i<dim; i++)
            phi_2 += phi[ix][i];
        file << ix << '\t' << std::norm(phi_2) << '\n';
    }
    file << std::endl;
}
