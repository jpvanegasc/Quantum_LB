#include<iostream>
#include<fstream>
#include<cmath>
#include <complex> 

#include"Random64.hpp"

const int Lx = 30;
const int t_max = 100;

const double theta = M_PI/4.0; 
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);
const double mass = std::tan(theta);

const std::complex <double> j (0,1);
const std::complex <double> uno (1,0);

const double beta = 0.1;
const double k = std::tan(theta)*beta;
