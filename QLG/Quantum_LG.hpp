#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.hpp"
#include"Constants.hpp"

class Automata{
    private:
        std::complex<double> phi[Lx][dim], phi_new[Lx][dim];
    public:
        Automata(double mu, double sigma);
        void normalize(void);
        void collide(int start);
        void advect(void);
        void print(std::ofstream &file);
        void wave(int t, std::ofstream &file);
        double sigma2(void);
        //double phi2(int ix){return std::norm(phi[ix][0]+phi[ix][1]);}
        double phi2(int ix){return std::norm(phi[ix][0])+std::norm(phi[ix][1]);}
        double phi2_new(int ix){return std::norm(phi_new[ix][0]+phi_new[ix][1]);}
};

Automata::Automata(double mu, double sigma){
    double gauss_coef = 1.0/(2*sigma*std::sqrt(2*M_PI));

    #pragma opm parallel for
    for(int ix=0; ix<Lx; ix++){
        double x=0;
        // Gaussian packet
        x = (std::exp(-0.25*(((ix-mu)*(ix-mu))/(sigma*sigma))));
        // Gaussian packet times e^-ikx
        phi[ix][0] = std::complex<double> (x*std::cos(k*ix), -x*std::sin(k*ix));
        phi[ix][1] = phi_new[ix][0] = phi_new[ix][1] = std::complex<double> (0, 0);
    }
    normalize();
}

void Automata::normalize(void){
    double norm = 0, norm_new = 0;
    #pragma omp parallel for reduction(+:norm, norm_new)
    for(int ix=0; ix<Lx; ix++){
        norm += phi2(ix); norm_new += phi2_new(ix);
    }
    norm = std::sqrt(norm); norm_new = std::sqrt(norm_new);
    if(norm == 0.0) norm = 1.0; if(norm_new == 0.0) norm_new = 1.0;

    for(int ix=0; ix<Lx; ix++){
        phi[ix][0] /= norm; phi[ix][1] /= norm;
        phi_new[ix][0] /= norm_new; phi_new[ix][1] /= norm_new;
    }
}

void Automata::collide(int start){
    for(int ix=start; ix<Lx; ix+=2){
        phi_new[ix][0] = uno*cos_theta*phi[ix][0] + j*sin_theta*phi[ix][1];
        phi_new[ix][1] = j*sin_theta*phi[ix][0] + uno*cos_theta*phi[ix][1];
    }
}

void Automata::advect(void){
    #pragma opm parallel for
    for(int ix=0; ix<Lx; ix++){
        phi[(ix+1+Lx)%Lx][0] = phi_new[ix][0];
        phi[(ix-1+Lx)%Lx][1] = phi_new[ix][1];
    }
}
/* prints wavefunction */
void Automata::print(std::ofstream &file){
    for(int ix=0; ix<Lx; ix++){
        file << ix << '\t' << std::norm(phi[ix][0]+phi[ix][1]) << '\n';
    }
    file << std::endl;
}
/* splot */
void Automata::wave(int t, std::ofstream &file){
    for(int ix=0; ix<Lx; ix++)
        file << ix << "\t" << t << "\t" << phi2(ix) << "\n";
}
/*Standard deviation */
double Automata::sigma2(void){
    double mu = 0, sigma_2 = 0;
    #pragma omp parallel for reduction(+:mu, sigma_2)
    for(int ix=0; ix<Lx; ix++){
        double phi_2 = phi2(ix);
        mu += ix*phi_2; sigma_2 += ix*ix*phi_2;
    }
    return sigma_2 - (mu*mu);
}
