#include <iostream>
#include <QtGui/QtGui>
#include <armadillo>
#include "filter.hpp"
#include "picturematrix.h"
#include "fouriermatrix.hpp"


void Filter::gaussianBlur(QImage &img)
{
  PictureMatrix::PictureMatrix pMatrix = PictureMatrix::PictureMatrix(img);
  pMatrix.extendMat(50, PictureMatrix::same);
  pMatrix.shrinkMat(50);
  pMatrix.setRMatrix(arma::zeros<arma::Mat<uchar>>(img.height(), img.width()));
  pMatrix.sendMatrixtoImage();
}

void Filter::invertImage(QImage &img)
{
  img.invertPixels();
}

arma::Mat<uchar> conv(arma::Mat<uchar> a, arma::Mat<uchar> b)
{
  return arma::Mat<uchar>(1,1);
}

void Filter::display_active_channels(QImage &img, bool r, bool g, bool b){
  PictureMatrix::PictureMatrix pMatrix = PictureMatrix::PictureMatrix(img);
  /*  */
  if(!r){
    std::cout << "R not active" << std::endl;
    pMatrix.setRMatrix(arma::zeros<arma::Mat<uchar>>(img.height(), img.width()));
  }
  if(!g){
    std::cout << "G not active" << std::endl;
    pMatrix.setGMatrix(arma::zeros<arma::Mat<uchar>>(img.height(), img.width()));
  }
  if(!b){

    std::cout << "B not active" << std::endl;
    pMatrix.setBMatrix(arma::zeros<arma::Mat<uchar>>(img.height(), img.width()));
  }
  pMatrix.sendMatrixtoImage();
}

void Filter::dark_square(QImage &img){
  PictureMatrix::PictureMatrix pMatrix = PictureMatrix::PictureMatrix(img);
  pMatrix.red.submat(0,0,50,100) = arma::zeros<arma::Mat<uchar>>(51,101);
  pMatrix.green.submat(0,0,50,100) = arma::zeros<arma::Mat<uchar>>(51,101);
  pMatrix.blue.submat(0,0,50,100) = arma::zeros<arma::Mat<uchar>>(51,101);
  pMatrix.sendMatrixtoImage();
}
