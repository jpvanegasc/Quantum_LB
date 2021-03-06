///-------------------------------------------------------------//
// Implementation of Succi's scheme for the Quantum Lattice
// Boltzmann method. 
// 
// Author: Ivan Pulido (@ijpulidos)
// National University of Colombia (Bogota, Colombia)
// -------------------------------------------------------------//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>    // for formatting, leading zeros, etc.
#include <cmath>
#include <complex>
#include <armadillo>    // linear algebra library
#include <omp.h>
#include <ctime>
using namespace std;
using namespace arma;

// --------- Declaration and prototipes -----------------------------//

#define L 2048
#define TMAX 5000    // maximum time value
#define beta_0 0.2 // propagation speed (related to momentum)
const complex <double> I (0, 1); // Imaginary unit
const complex <double> Cero (0, 0);// Zero in complex field
const complex <double> Uno_r (1, 0);// One in complex field
const double mass=0.1 ;// particle's mass

//---------------- Main class for QLB -------------------------------//

class Qlb_Succi{
public:
    Qlb_Succi(void);
    ~Qlb_Succi(void);
    //void OndaPlana(void);
    void Gaussian(double mu, double sigma);
    double WellPotential(int center, int width, double V0, int x);
    double HoPotential(double omega, int x);    // function for harmonic potential
    void EvCoeffs(void); // This computes evolution coefficients a,b
    void Evolucione(void);
    void Eigenvalues(void);
    void Muestra_CS_Real(double t);
    void Muestra_CS_Imag(double t);
    void Reconstruction(string NombreArchivo, double t);
    double sigma();
    double mu(double * f);
private:
    complex <double> *a, *b;    // evolution coefficients
    complex <double> **C_spinor,**C_spinor_new; //[0]->Derecha,[1]->right,[2]->left,[3]->left. The spinor is [u1,u2,d1,d2]
    int V[4];                // 4 possible velocities in 1D (2 l 2 r). 
};

Qlb_Succi::Qlb_Succi(void){
    int ix,i;
    // Velocity arrays (for u and d components)
    V[0]=1; V[1]=1;                    // velocities for U components
    V[2]=-1; V[3]=-1;                // velocities for D components

    // Memory allocation for coefficients arrays a,b
    a = new complex <double> [L];
    b = new complex <double> [L];
    
    // Memory allocation for matrices with spinors 
    C_spinor =new complex <double> *[L];
    C_spinor_new=new complex <double>* [L];
    for(ix=0;ix<L;ix++){
        C_spinor[ix]=new complex <double>[4];
        C_spinor_new[ix]=new complex <double>[4];
    }
}

Qlb_Succi::~Qlb_Succi(void){
    for(int ix=0;ix<L;ix++){
        delete [] C_spinor[ix]; delete C_spinor_new[ix];
     }
    delete [] C_spinor; delete [] C_spinor_new;
}


/*
void Qlb_Succi::OndaPlana(void){
    //Llenar los contenidos de las metrices
    int ix;
    double k, x;
    k=2*M_PI*n/L;// Vector de Onda Cuantización espacial de la red.
    for( ix=0;ix<L;ix++){
        x=k*ix;
        Psi[ix][1]=Cero;
        Psi[ix][0]=exp(I*x);
        // cout<<ix<<" "<<imag(Psi[ix][0])<<endl;
    }
}
*/

void Qlb_Succi::Gaussian(double mu, double sigma){// mean, width
    int ix;
    double k, x, coef;
    complex <double> expon1;
    complex <double> expon2;

    coef=pow(2*M_PI*sigma*sigma, -0.25);
    for( ix=0;ix<L;ix++){
        expon1=exp(I*mass*beta_0*(ix-mu));
        expon2=exp(-I*mass*beta_0*(ix-mu));
        C_spinor[ix][3]=-I*expon1*exp(-0.25*pow((ix-mu)/sigma,2))*coef;
        C_spinor[ix][2]=-I*expon1*exp(-0.25*pow((ix-mu)/sigma,2))*coef;
        C_spinor[ix][1]=expon1*exp(-0.25*pow((ix-mu)/sigma,2))*coef;
        C_spinor[ix][0]=expon1*exp(-0.25*pow((ix-mu)/sigma,2))*coef;
        // Ojo en la definición de la exponencial, hay un 1/4 que define le gaussiana.
        // cout<<ix<<" "<<imag(Psi[ix][0])<<endl;
    }
    
}

double Qlb_Succi::WellPotential(int center, int width, double V0, int x){
    if (abs(x-center)<0.5*width){
        return 0.0;
    }
    else{
        return V0;
    }
}

double Qlb_Succi::HoPotential(double omega, int x){
    double V0;
    double pot = mass*omega*omega*x*x;    // useful coefficient
    // ACÁ VOY (REHACER)
    // tengo que pensar que realmente los coeficientes deberían calcularse
    // por fuera de la función del potencial, fue un error hacerlo así.
    
    return pot;
}

void Qlb_Succi::EvCoeffs(void){
    int ix;
    complex <double> an,ad,bn,bd;    // evolution coeffs.
    double coeff, g;
    // building the evolution coeffs.
    for(ix=0;ix<L;ix++){
        //g = 0;    // For free particle
        g = WellPotential(0.5*L,L/3,0.2,ix);    // For Potential well
        //clog << ix << " " << g << endl;    // to draw potential
        coeff = 0.25*(mass*mass - g*g);
        an = complex<double>(1-coeff);
        ad = complex<double>(1+coeff,-g);
        a[ix] = an/ad;
        bn = complex<double>(mass);
        bd = complex<double>(1+coeff,-g);
        b[ix] = bn/bd;
        //cout << a[ix] << " " << b[ix] << endl;
    }
}

void Qlb_Succi::Evolucione(void){
    int ix,i;
    complex <double> C;
    complex <double> **aux;
    C=exp(Cero);

#pragma omp parallel for private(ix)
    for(ix=0;ix<L;ix++){
        C_spinor_new[(ix+V[0]+L)%L][0]= a[ix]*C_spinor[ix][0]+b[ix]*C_spinor[ix][2];
        C_spinor_new[(ix+V[1]+L)%L][1]= a[ix]*C_spinor[ix][1]+b[ix]*C_spinor[ix][3];
        C_spinor_new[(ix+V[2]+L)%L][2]= a[ix]*C_spinor[ix][2]-b[ix]*C_spinor[ix][0];
        C_spinor_new[(ix+V[3]+L)%L][3]= a[ix]*C_spinor[ix][3]-b[ix]*C_spinor[ix][1];
        //cout << a << " " << b << endl;
    }
    aux=C_spinor; C_spinor= C_spinor_new; C_spinor_new=aux;
}

void Qlb_Succi::Eigenvalues(void){
    /* Builds the evolution matrix U and calculate eigenvalues using
    armadillo lib.*/
    int i, j, idx;
    int flag; // flag to tell me wether even row (1 or 0, 1 for even)
    cx_mat C(4*L,4*L);    // Collision matrix
    cx_mat A(4*L,4*L);    // Advection matrix (traslation)
    cx_mat Ar(4,4);    // Advection matrix block for "right traslation"
    cx_mat Al(4,4);    // Advection matrix block for "left traslation"
    cx_mat T(4,4);    // Time evolution matrix T = A*C
    //cx_mat A(4,4);
    cx_vec eigv(4*L);
    //cx_vec eigv(4);
    cx_vec eigvtmp;
    cx_mat eigf;
    cx_vec eigfv(4*L);
    C.fill(0.0);    // fill with zeroes
    A.fill(0.0);    // fill with zeroes
    Ar.fill(0.0);    // fill with zeroes
    Al.fill(0.0);    // fill with zeroes
    
    // BUILDING COLLISION MATRIX 
    for (i=0;i<4*L;i+=4){
        idx = i/4;
        C(i,i) = a[idx];
        C(i,i+2) = b[idx];
        C(i+1,i+1) = a[idx];
        C(i+1,i+3) = b[idx];
        C(i+2,i) = -b[idx];
        C(i+2,i+2) = a[idx];
        C(i+3,i+1) = -b[idx];
        C(i+3,i+3) = a[idx];
    }
    C.save("C.dat", raw_ascii);

    // BUILDING ADVECTION MATRIX
    /* You have to fill A in two steps, one to fill "even" row-blocks and
     * other one to fill "odd" row-blocks, that's what flag is for. */
    flag = 1; // we start with even row-block (0) 
    for (i=0;i<4*L;i+=4){
        if (flag==1){ // check if it is an even row-block
            for (j=4*flag; j<4*L; j+=8){
                if (j%12==0 && j!=0){
                    A(i,j) = 1;
                    A(i+1,j+1) = 1;
                }
                else{
                    A(i+2,j+2) = 1;
                    A(i+3,j+3) = 1;
                }
            }
        }
        else{
            for (j=4*flag; j<4*L; j+=8){
                if (j%16==0){
                    A(i,j) = 1;
                    A(i+1,j+1) = 1;
                }
                else{
                    A(i+2,j+2) = 1;
                    A(i+3,j+3) = 1;
                }
            }
        }
        cout << flag << endl;
        flag = (flag+1)%2;
    }
    A.save("A.dat", raw_ascii);
    
    // BUILDING TIME EVOLUTION MATRIX
    T = A*C;
    T.save("T.dat", raw_ascii);
    eig_gen(eigvtmp, eigf, T);
    eigv = log(eigvtmp)/I;
    //for(i=0;i<4*L;i++){
    //        eigv(i) = abs(eigvtmp(i));
    //}
    eigv.save("eigv.dat", raw_ascii);
    eigf.save("eigf.dat", raw_ascii);
    
    //This jons the u,d for every lattice point from the eigf matrix into eigfv
    for(j=0; j<4*L; j++){
        idx = floor(j/4.0);
        cout << j << " " << idx << " ";
        for(i=idx; i<idx+4; i++){
            cout << i << " ";
            /*eigfv(i) = eigf(j,i); 
            eigfv(i+1) = eigf(j,i+1); 
            eigfv(i+2) = eigf(j,i+2); 
            eigfv(i+3) = eigf(j,i+3); */
        }
        cout << endl;
    }
    //eigfv.save("eigf.dat", raw_ascii);
}

void Qlb_Succi::Muestra_CS_Real(double t){
 int ix;
 cout<<"CS_real"<<endl;
 cout<<"t    ix    u1    u2    d1    d2"<<endl;
    for(ix=0;ix<L;ix++)
        cout<<t<<" "<<ix<<" "<<real(C_spinor[ix][0])<<" "<<real(C_spinor[ix][1])<<" " 
	<<real(C_spinor[ix][2])<<" "<<real(C_spinor[ix][3])<<" " <<endl;

}
void Qlb_Succi::Muestra_CS_Imag(double t){
    int ix;
    cout<<"CS_imag"<<endl;
    cout<<"t    ix    u1    u2    d1    d2"<<endl;
    for(ix=0;ix<L;ix++)
        cout<<t<<" "<<ix<<" "<<imag(C_spinor[ix][0])<<" "<<imag(C_spinor[ix][1])<<" "    
	<<imag(C_spinor[ix][2])<<" "<<imag(C_spinor[ix][3])<<" " <<endl;
}

double Qlb_Succi::mu(double * f){
    int i;
    double t1,t2,r;
    t1 = 0;
    t2 = 0;
    for(i=0; i<L; i++){
        t1+=f[i]*(i);
        t2+=f[i];
    }
    return t1/t2;
}

double Qlb_Succi::sigma(){
    int i;
    double prom, sum1, sum2, x, r;

    int ix;
    double psi[L];
    complex <double> Phi_1, Phi_2;
    complex <double> expon;
    
    for(ix=0;ix<L;ix++){
        Phi_1= (C_spinor[ix][0]+I*C_spinor[ix][2])*0.7071067812 ;
        Phi_2= (C_spinor[ix][1]+I*C_spinor[ix][3])*0.7071067812 ;
        psi[ix]=real( (Phi_1)*conj(Phi_1))+real( (Phi_2)*conj(Phi_2));
    }

    prom = mu(psi);
    sum1=0;
    sum2=0;
    for(i=0; i<L; i++){
        x = i;
        sum1+=psi[i]*(x-prom)*(x-prom);
        sum2+=psi[i];
    }
    return sqrt(sum1/sum2);
}

void Qlb_Succi::Reconstruction(string NombreArchivo, double t){
    
    ofstream MiArchivo(NombreArchivo.c_str());
    complex <double> Psi_total;
    
    int ix;
    double rho_grafica;
    complex <double> Phi_1, Phi_2;
    complex <double> expon;
    
    for(ix=0;ix<L;ix++){
        Phi_1= (C_spinor[ix][0]+I*C_spinor[ix][2])*0.7071067812 ;
        Phi_2= (C_spinor[ix][1]-I*C_spinor[ix][3])*0.7071067812 ;
        rho_grafica=real( (Phi_1)*conj(Phi_1))+real( (Phi_2)*conj(Phi_2));
        MiArchivo<<ix<<" "<<rho_grafica <<endl;
    }
}

int main(){
    // variables/struct to measure time
    double start, end;
    start = omp_get_wtime();
    
    // variables for QLB method
    Qlb_Succi WaveFunction;
    int t;
    t=0;
    double sigma0 = 50.0;
    double mu0 = L*1.0/2;
    
    //string filename, partfn;
    //WaveFunction.Gaussiana(L*1.0/2, 5.0);
    WaveFunction.Gaussian(mu0, sigma0);
    //    WaveFunction.Rho_uno_mas(t);
    
    //WaveFunction.Reconstruction(const_cast<char *>("rho_sil_0.dat"), t);
        
    // Creating string stream for filenames
    ostringstream oss;

    // Building the evolution coefficients a and b
    WaveFunction.EvCoeffs();

    for(t=0;t<TMAX;t++){
        // building filename and saving data
        oss << "./data/rho_sil_" << setfill('0') << setw(4) << t << ".dat";
        WaveFunction.Evolucione();
        //WaveFunction.Reconstruction(const_cast<char *>(oss.str()), t);
        //cout << oss.str() << endl;
        WaveFunction.Reconstruction(oss.str(), t);
        oss.str("");
        oss.clear();
    }
    //WaveFunction.Eigenvalues();
    
    // Time elapsed since "start"
    end = omp_get_wtime();
    cout << "Execution time: "<< end-start << endl;
    //    WaveFunction.Rho_uno_mas(t);
    //stringstream(t) >> partfn;
    //filename = "rho_sil_" + partfn + ".dat";
    //WaveFunction.Reconstruction(const_cast<char *>("rho_sil_last.dat"), t);
    
    return 0;
}

