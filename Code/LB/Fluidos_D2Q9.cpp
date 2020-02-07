// Parcial 2 Jose Daniel
#include<iostream>
#include<fstream>
#include<cmath>
#include"Random64.h"
using namespace std;

const int Lx=256, Ly=64;

const int Q=9;

const double tau=0.55;
const double Utau=1.0/tau;
const double UmUtau=1-Utau;

class LatticeBoltzmann{
	private:
		double w[Q], f[Lx][Ly][Q], fnew[Lx][Ly][Q]; 
		int V[2][Q]; // V[0][i]=V_ix   V[1][i]=V_iy
	public:
		LatticeBoltzmann(void){
			//Cargar los pesos
			w[0]=4/9.0; 
			w[1]=w[2]=w[3]=w[4]=1/9.0;
			w[5]=w[6]=w[7]=w[8]=1/36.0;
			//Cargar los vectores
			V[0][0]=0;
			V[1][0]=0;

			V[0][1]=1;  V[0][2]=0;  V[0][3]=-1; V[0][4]=0;
			V[1][1]=0;  V[1][2]=1;  V[1][3]=0;  V[1][4]=-1;

			V[0][5]=1;  V[0][6]=-1; V[0][7]=-1; V[0][8]=1;
			V[1][5]=1;  V[1][6]=1;  V[1][7]=-1; V[1][8]=-1;
		}
		double rho(int ix, int iy, bool use_new){
				int i; double suma;
			for(suma=0,i=0;i<Q;i++)
				if(use_new) suma+=fnew[ix][iy][i]; else suma+=f[ix][iy][i];
			return suma;
		}
		double Jx(int ix, int iy, bool use_new){
			// Flujo de Poiseuille
			double d_p, eta, rho0; d_p=0.001; eta=10;
			rho0=rho(ix,iy,false);
			return (rho0/2)*(d_p/eta)*iy*(Ly-1-iy);
		}
		double Jy(int ix, int iy, bool use_new){
			return 0;
		}
		double f_eq(double rho0, double Ux0, double Uy0, int i){
			double UdotVi=Ux0*V[0][i]+Uy0*V[1][i], U2=Ux0*Ux0+Uy0*Uy0;
			return rho0*w[i]*(1+3*UdotVi+4.5*UdotVi*UdotVi-1.5*U2);
		}
		void colisione(void){
			int ix,iy,i; double rho0,Ux0,Uy0;
			//Para cada celda
			for(ix=0;ix<Lx;ix++)
				for(iy=0;iy<Ly;iy++){
					//Calcular las cantidades macroscópicas
					rho0=rho(ix,iy,false);	Ux0=Jx(ix,iy,false)/rho0;	Uy0=Jy(ix,iy,false)/rho0;
					for(i=0;i<Q;i++)
						fnew[ix][iy][i]=UmUtau*f[ix][iy][i]+Utau*f_eq(rho0,Ux0,Uy0,i);}
		}
		void adveccione(void){
			for(int ix=0;ix<Lx;ix++)
				for(int iy=0;iy<Ly;iy++)
					for(int i=0;i<Q;i++)
						f[(ix+V[0][i]+Lx)%Lx][(iy+V[1][i]+Ly)%Ly][i]=fnew[ix][iy][i];
		}
		void inicie(double Ux0,double Uy0){
			double mu, sigma, rho0, first_part; mu = Lx/8.0; sigma = Ly/9.0;
			first_part=1/(sigma*sqrt(2*M_PI));
			for(int ix=0;ix<Lx;ix++){
				// Generar una "densidad gaussiana"
				rho0=first_part*exp(-0.5*(((ix-mu)/sigma)*((ix-mu)/sigma)));
				for(int iy=0;iy<Ly;iy++)
					for(int i=0;i<Q;i++)
						f[ix][iy][i]=f_eq(rho0,Ux0,Uy0,i);
			}
		}
		/**
		 * Calcular sigma^2 en el eje x
		 */
		double sigmax2(void){
			double N, xprom, sigma2;
			N=0.0, xprom=0.0, sigma2=0.0;
			// Calculo N
			for(int ix=0; ix<Lx; ix++)
				for(int iy=0;iy<Ly;iy++)
					N += rho(ix, iy, true);
			// Calculo xprom
			for(int ix=0; ix<Lx; ix++)
				for(int iy=0;iy<Ly;iy++)
					xprom += ix*rho(ix, iy, true);
			xprom /= N;
			//Calculo sigma^2
			for(int ix=0; ix<Lx; ix++)
				for(int iy=0;iy<Ly;iy++)
					sigma2 += rho(ix, iy, true)*(ix-xprom)*(ix-xprom);
			sigma2 /= N;
			return sigma2;
			
		}
		/**
		 * Detector de densidad en x=150
		 */
		double detector(void){
			double rho0; rho0=0;
			for(int iy=0;iy<Ly;iy++)
				rho0 += rho(150,iy,true);
			return rho0;


		}
		/**
		 * Genera un archivo con los datos para graficar
		 * @param nombre_archivo
		 */
		void imprimase(const char *nombre_archivo);
};



int main(){
	LatticeBoltzmann Aire;
	int t, tmax=5000;

	Aire.inicie(0,0);

	for(t=0; t<tmax; t++){
		Aire.colisione();
		Aire.adveccione();
		cout<<t<<' '<<Aire.detector()<<endl;
	}
	Aire.imprimase("5000.dat");

	
	return 0;
}


void LatticeBoltzmann::imprimase( const char *nombre_archivo){
	ofstream MiArchivo(nombre_archivo); double rho0, Ux0, Uy0;
	for(int ix=0; ix<Lx; ix++){
		for(int iy=0; iy<Ly; iy++){
			rho0=rho(ix,iy,true);
			MiArchivo<<ix<<'\t'<<iy<<'\t'<<rho0<<'\n';
		}
		MiArchivo<<'\n';
	}
	MiArchivo << endl;
	MiArchivo.close();
}

