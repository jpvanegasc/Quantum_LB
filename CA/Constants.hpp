#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.hpp"

const int Lx = 2048;
const int t_max = 2000;

const double theta = M_PI/6.0; 
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);
const double mass = std::tan(theta);

const double roh = M_PI/6.0; 
const double sin_roh = std::sin(roh);
const double cos_roh = std::cos(roh);

const std::complex <double> j (0,1);
const std::complex <double> uno (1,0);

const double beta = 0.1;
const double k = mass*beta;
