#include<complex>
#include<cmath>

const int Lx = 30;

// m = tan(theta)
//const double theta = 0.463647609;
//const double theta = 0.197395598;
const double theta = M_PI_4;
const double sin_theta = std::sin(theta);
const double cos_theta = std::cos(theta);

const std::complex <double> j (0,1);
const std::complex <double> uno (1,0);

const double beta = -0.1;
const double k = std::tan(theta)*beta;