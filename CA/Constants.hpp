<<<<<<< HEAD
#include<complex>
#include<cmath>

const int Lx = 30;

// m = tan(theta)
//const double theta = 0.463647609;
//const double theta = 0.197395598;
const double theta = M_PI_4;
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);
=======
#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.hpp"

const int Lx = 2048;
const int t_max = 2000;

const double theta = M_PI/4.0; 
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);
const double mass = std::tan(theta);

const double rho = 0; 
const double sin_rho = std::sin(rho);
const double cos_rho = std::cos(rho);
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da

const std::complex <double> j (0,1);
const std::complex <double> uno (1,0);

<<<<<<< HEAD
const double beta = -0.1;
const double k = std::tan(theta)*beta;
=======
const double beta = 0.1;
const double k = mass*beta;
>>>>>>> 67265b660daf169dc542ad732be0431b97b743da
