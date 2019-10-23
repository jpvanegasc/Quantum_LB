#include<iostream>
#include<fstream>
#include<cmath>
#include"Random64.h"

const int Lx=256;
const int Q=3;

const double tau=0.55;
const double Utau=1.0/tau;
const double UmUtau=1-Utau;

class LatticeBoltzmann{
    private:
        double w[Q];
        double f[Lx][Q], f_new[Lx][Q]; 
        // double C[Lx]; // C written as function of x used when the medium velocity is to be changed
        int V[2][Q]; // V[0][i]=V_ix and V[1][i]=V_iy
    public:
        /* Load vectors w[Q] and V[2][Q] */
        LatticeBoltzmann(void){
            //Cargar los pesos
            w[0]=2.0/3.0; 
            w[1]=w[2]=1.0/6.0;    
            //Cargar los vectores
            V[0][0]=0;
            V[1][0]=0;

            V[0][1]=1;  V[0][2]=0;
            V[1][1]=0;  V[1][2]=1;
        }
        /**
         * Macro-Variable: 
         * @param ix: position on x-axis on which we are calculating
         * @param use_new: calculating rho either for f or f_new
         */
        double rho(int ix, bool use_new){
            int i; double suma;
            for(suma=0,i=0;i<Q;i++)
                if(use_new) suma+=f_new[ix][i]; else suma+=f[ix][i];
            return suma;
        }
        /**
         * Macro-Variable: Velocity field of the system we are modeling over the x-axis. We define 
         * f_i(x_0,t) such that the sum over i in the x direction will be U_x(x_0).
         * @param ix: position on x-axis on which we are calculating
         * @param use_new: calculating U_x either for f or f_new
         */
        double U_x(int ix, bool use_new){
            int i; double suma;
            for(suma=0,i=0;i<Q;i++)
                if(use_new) suma+=f_new[ix][i]*V[0][i]; else suma+=f[ix][i]*V[0][i];
            return suma;
        }
        /**
         * Using the LBGK equation and taking d_t/tau as one, f(x_i+d_x,t+d_t) equals this function 
         * (i.e. f(x_0+d_x,t+d_t)=f_new_i(x_0,t)).
         * It's defined for the type of system we wish to model (fluids, waves, etc.), and its 
         * moments are the same as the f(x_i,t) function (i.e. sum over i of f_new_i = sum over i
         * of f_i). 
         * @param rho0: macro-variable 
         * @param U_x0: macro-variable 
         * @param i:
         */
        double f_eq(double rho0, double U_x0, int i){
            return 0;
        }
        void colisione(void){
            int ix,iy,i; double rho0,Ux0,Uy0;
            //Para cada celda
            for(ix=0; ix<Lx; ix++){
                //Calcular las cantidades macroscópicas
                rho0=rho(ix, false);    Ux0=U_x(ix, false)/rho0;
                for(i=0; i<Q; i++)
                    f_new[ix][i]=UmUtau*f[ix][i]+Utau*f_eq(rho0, Ux0, i);}
        }
        void adveccione(void){
            int ix, i;
            for(ix=0; ix<Lx; ix++)
                for(i=0; i<Q; i++)
                    f[(ix+V[0][i]+Lx)%Lx][i]=f_new[ix][i];
        }
        /* Condiciones Iniciales */
        /* Unfinished!! */
        void inicie(double Jx0){
            int ix, i; double mu, sigma, rho0, normalization;
            mu = Lx/2.0; sigma = Lx/10.0;
            normalization = 1.0/(sigma*std::sqrt(2*M_PI));
            
            for(ix=0; ix<Lx; ix++){
                rho0 = normalization * std::exp(1);
                for(i=0; i<Q; i++){
                    f[ix][i] = 0;
                }
            }
        }
        void imponer_campos(int t){
            double nada=0;
        }
        void imprimase(const char * nombre_archivo);
};

int main(void){
    LatticeBoltzmann QuantumStuffBaby;
    return 0;
}

void LatticeBoltzmann::imprimase(const char * nombre_archivo){
    double nada=0;
}