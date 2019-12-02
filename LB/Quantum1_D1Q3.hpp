// Succi model
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include"Random64.hpp"

const int Lx=256;
const int D=1, Q=3;
const int f_size = Lx*Q;

const double tau = 0.55;
const double Utau = 1.0/tau;
const double UmUtau = 1-Utau;

class LatticeBoltzmann{
    private:
        double w[Q]; int V[D][Q]; // V[0][i]=V_ix
        double *f = NULL,   *f_new = NULL;
    public:
        LatticeBoltzmann(void);
        ~LatticeBoltzmann();
        int get_1D(int ix);
        double rho(int ix);
        double Jx(int ix);
        double Jx_new(int ix);
        double f_eq(double rho0, double U_x0, int i);
        void collide(void);
        void propagate(void);
        void initialize(double Jx0);
        void save(std::string filename);
        void print(void);
};

/* Load vectors w[Q] and V[2][Q], initialize f and f_new */
LatticeBoltzmann::LatticeBoltzmann(void){
    //Cargar los pesos
    w[0] = 2.0/3.0; 
    w[1] = w[2] = 1.0/6.0;
    //Cargar los vectores
    V[1][0]=0;  V[0][1]=1;  V[0][2]=-1;
    // f and f_new
    f = new double[f_size];
    f_new = new double[f_size];
}
/* Free Memory */
LatticeBoltzmann::~LatticeBoltzmann(){
    delete[] f; delete[] f_new;
}
/* */
int LatticeBoltzmann::get_1D(int ix){
    return ix*Q;
}
/**
 * Macro-Variable: Still no idea of wtf is this
 * @param ix: position on x-axis on which we are calculating
 */
double LatticeBoltzmann::rho(int ix){
    double rho = 0; int pos = get_1D(ix);
    for(int i=0; i<Q; i++){
        rho += f[pos + i];
    }
    return rho;
}
/**
 * Macro-Variable: Velocity field of the system we are modeling over the x-axis. 
 * We define f_i(x_0,t) such that the sum over i in the x direction will be U_x(x_0).
 * Jx is defined as Ux*rho.
 * @param ix: position on x-axis on which we are calculating
 */
double LatticeBoltzmann::Jx(int ix){
    double J_x = 0; int pos = get_1D(ix);
    for(int i=0; i<Q; i++){
        J_x += f[pos + i] * V[0][i];
    }
    return J_x;
}
/**
 * Jx but calculates the sum using f_new. This is useful when debugging. This is computationally 
 * better than making a single function and passing use_new as a parameter.
 */
double LatticeBoltzmann::Jx_new(int ix){
    double J_x = 0; int pos = get_1D(ix);
    for(int i=0; i<Q; i++){
        J_x += f_new[pos + i] * V[0][i];
    }
    return J_x;
}
/**
 * This is most likely all crap. I'm not certain of what I'm saying here, but still:
 * Using the LBGK equation and taking d_t/tau as one, f(x_i+d_x,t+d_t) equals this function 
 * (i.e. f(x_0+d_x,t+d_t)=f_new_i(x_0,t)).
 * 
 * @param rho0: macro-variable 
 * @param U_x0: macro-variable 
 * @param i: Velocity vector on which we are calculating
 */
double LatticeBoltzmann::f_eq(double rho0, double Ux0, int i){
    return 0;
}
void LatticeBoltzmann::collide(void){
    double rho0, Ux0; int pos;
    for(int ix=0; ix<Lx; ix++){
        rho0 = rho(ix); Ux0 = Jx(ix)/rho0; pos = get_1D(ix);
        for(int i=0; i<Q; i++)
        // this is from fluids, probably has to change
            f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, Ux0, i);
        }
}
void LatticeBoltzmann::propagate(void){
    for(int ix=0; ix<Lx; ix++){
        int pos_new = get_1D(ix);
        for(int i=0; i<Q; i++){ // Non periodic, non optimized
            int x_pos = (ix + V[0][i]);
            if(x_pos<0 || x_pos>=Lx) continue;
            int pos = get_1D(x_pos);
            f[pos + i] = f_new[pos_new + i];
        }
    }
}
/* Initial conditions */
/* Unfinished!! */
void LatticeBoltzmann::initialize(double Jx0){
    int ix, i; double mu, sigma, rho0, normalization;
    mu = Lx/2.0; sigma = Lx/10.0;
    normalization = 1.0/(sigma*std::sqrt(2*M_PI));
    // this doesnt use the doubleformat here
    for(ix=0; ix<Lx; ix++){
        rho0 = normalization * std::exp(1);
        for(i=0; i<Q; i++){
            f[ix+i] = 0;
        }
    }
}
void LatticeBoltzmann::save(std::string filename){
    double this_=0;
}
void LatticeBoltzmann::print(void){
    double that = 0;
}
