#include"Constants.hpp"


class Automata{
    private:
        std::complex<double> phi[Lx];
        std::complex<double> phi_new[Lx];
        std::complex<double> psi[Lx][2];
        std::complex<double> psi_new[Lx][2];
    public:
        Automata(unsigned long long seed, double mu, double sigma);
        void defPsi(void);
        void normalize(void);
        void collision(int i_start);
        void advect(void);
        void show(void);
        void grafique(int t, std::ofstream &file);
        void wave(std::ofstream &file);
        double phi2(int ix){return std::norm(phi[ix]);}
        double gauss_init(int x, double mu, double sigma);
};

Automata::Automata(unsigned long long seed, double mu, double sigma){
    CRandom ran64(seed);
    double x;
    for(int ix=0; ix<Lx; ix++){
        x = gauss_init(ix, mu, sigma);
        phi[ix] = std::complex<double> (x*std::cos(k*ix), -x*std::sin(k*ix));
        phi_new[ix] = psi[ix][0] = psi[ix][1] = psi_new[ix][0] = psi_new[ix][1] = std::complex <double>(0, 0);
    }
    normalize();
}

void Automata::defPsi(void){
    for(int ix=0; ix<Lx; ix++){
        psi[ix][0]= phi[(ix-1+Lx)%Lx];
        psi[ix][1]= phi[ix];
    }
}

void Automata::normalize(void){
    double sum{0};
    double newSum{0};
    defPsi();
    #pragma omp parallel for reduction(+: sum)
    for (int i=0; i<Lx; i++)
        sum += std::norm(psi[i][0]) + std::norm(psi[i][1]);
    sum = sqrt(sum);

    #pragma omp parallel for
    for (int i=0; i<Lx; i++)
        phi[i] /= sum;
}
/**
 * Evolves one time step the state vector 
 */
void Automata::collision(int i_start){
    for(int ix=i_start; ix<Lx; ix+=2){
        phi_new[(ix-1+Lx)%Lx] = j*sin_theta * phi[(ix-1+Lx)%Lx] + uno*cos_theta*phi[ix];
        phi_new[ix] = uno*cos_theta*phi[(ix-1+Lx)%Lx] + j*sin_theta * phi[ix];
    }
}
void Automata::advect(void){
    #pragma omp parallel for reduction(+: sum)
    for (int i=0; i<Lx; i++)
        phi[i] = phi_new[i];
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
    defPsi();
    for (int ix=0; ix<Lx; ix++){
        file << ix << '\t' << std::norm(psi[ix][0]) + std::norm(psi[ix][1]) << '\n';
    }  
}
double Automata::gauss_init(int x, double mu, double sigma){
    return std::exp(-0.25*(((x-mu)*(x-mu))/(sigma*sigma)));
}
