#include <armadillo>
#include <math.h>
#include <QtGui/QtGui>
#include "fouriermatrix.hpp"
#include <iostream>

#define _USE_MATH_DEFINES

MatComplex FourierMatrix::getFourierMatrix(int n){
  MatComplex s = MatComplex(n, n);
  double real = cos(2 * M_PI / n);
  double img = sin(-2 * M_PI / n);
  std::complex<double> omega(real, img);

  for (int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      s(i,j) = pow(omega,i * j);
    }
  }
  s *= 1/sqrt(n);
  std::cout << s << std::endl;
 return s;
}
