#include"Constants.hpp"

<<<<<<< HEAD
#include"Constants.hpp"
=======
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da

class Automata{
    private:
        std::complex<double> psi[Lx][2];
        std::complex<double> psi_new[Lx][2];
    public:
<<<<<<< HEAD
        Automata(double mu, double sigma);
=======
        Automata(unsigned long long seed, double mu, double sigma);
        void defPsi(void);
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
        void normalize(void);
        void collision(int i_start);
        void advect(int i_start);
        void show(void);
        void grafique(int t, std::ofstream &file);
        void wave(std::ofstream &file);
        double psi2(int ix){return std::norm(psi[ix][0]) + std::norm(psi[ix][1]);}
        double gauss_init(int x, double mu, double sigma);
};

<<<<<<< HEAD
Automata::Automata(double mu, double sigma){
    for(int i=0; i<Lx; i++){
        // Gaussian packet
        double x=0, y=0;
        if(i==0) x=1;
        //x = (std::exp(-0.5*(((i-mu)*(i-mu))/(sigma*sigma))))/(sigma*std::sqrt(2*M_PI));
        phi[i] = std::complex <double>(x, y);
=======
Automata::Automata(unsigned long long seed, double mu, double sigma){
    CRandom ran64(seed);
    double x, xm1;
    //xm1= gauss_init(Lx-1, mu, sigma);
    for(int ix=0; ix<Lx; ix++){
        x = gauss_init((ix-1+Lx)%Lx, mu, sigma);
        //psi[ix][0] = std::complex<double> (x*std::cos(k*ix), -x*std::sin(k*ix));
        psi[ix][1] = psi_new[ix][0] = psi_new[ix][1] = std::complex <double>(0, 0);
        psi[ix][0]=psi[(ix-1+Lx)%Lx][1]= std::complex <double>(x*std::cos(k*ix), -x*std::sin(k*ix));
        
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
    }
    normalize();
}

void Automata::normalize(void){
    double sum{0};
    double newSum{0};
    #pragma omp parallel for reduction(+: sum)
    for (int i=0; i<Lx; i++)
        sum += psi2(i);
    sum = sqrt(sum);

    #pragma omp parallel for
    for (int i=0; i<Lx; i++){
        psi[i][0] /= sum;
        psi[i][1] /= sum;
    }
}
/**
 * Evolves one time step the state vector 
 */
void Automata::collision(int i_start){
    for(int ix=i_start; ix<Lx; ix+=2){
        psi_new[ix][0]= j*sin_theta * cos_rho* psi[(ix-1+Lx)%Lx][1] 
                            + sin_rho*(sin_theta*psi[ix][0]-j*cos_theta*psi[ix][1]) 
                            + uno*cos_rho*cos_theta*psi[(ix+1+Lx)%Lx][0];
        psi_new[ix][1] = uno*cos_theta*psi[(ix-1+Lx)%Lx][1]  
                            + sin_rho*(sin_theta*psi[ix][1]-j*cos_theta*psi[ix][0])  
                            + j*sin_theta * psi[(ix+1+Lx)%Lx][0];
    }
}
void Automata::advect(int i_start){
    #pragma omp parallel for reduction(+: sum)
    for (int ix=i_start; ix<Lx; ix+=2){
        psi[ix][0] = psi_new[(ix-2+Lx)%Lx][0];
        psi[ix][1] = psi_new[(ix+2+Lx)%Lx][1];
    }
}
void Automata::show(void){
    for (int i=0; i<Lx; i++)
        std::cout << psi2(i) << "\t|\t";
    std::cout << std::endl;
}
void Automata::grafique(int t, std::ofstream &file){
    for(int i=0; i<Lx; i++)
<<<<<<< HEAD
        file << i << "\t" << t << "\t" << std::norm(phi[i]) << "\n";
=======
        file << i << "\t" << t << "\t" << psi2(i) << "\n";
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
}
void Automata::wave(std::ofstream &file){
    for (int ix=0; ix<Lx; ix++){
        file << ix << '\t' << psi2(ix) << '\n';
    }  
}
double Automata::gauss_init(int x, double mu, double sigma){
    return std::exp(-0.25*(((x-mu)*(x-mu))/(sigma*sigma)));
}
