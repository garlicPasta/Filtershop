#ifndef _FOURIERMATRIX_
#define _FOURIERMATRIX_
#include <armadillo>

using MatComplex = arma::Mat<std::complex<double>>;

class FourierMatrix{
  public:
    static MatComplex getFourierMatrix(int n);
};
#endif

