#include <iostream>
#include <armadillo>
#include <QtGui/QtGui>
#include <armadillo>
#include "Filter.hpp"

using namespace std;
using namespace arma;


void Filter::gaussianBlur(QImage *img)
{
  int height= img->height();
  int width = img->width();
  std::cout << height << "px " << width << "px " << std::endl; 
  Mat<unsigned char> picMatrix = Mat<unsigned char>(img->bits(), height, width * 4);
  picMatrix = picMatrix / 2;
  Mat<int> pMatrix = conv_to<Mat<int>>::from(picMatrix);
  pMatrix = pMatrix /  2;
  // picMatrix = conv_to<Mat<unsigned char>>::from(pMatrix);
  memcpy(img->bits(), picMatrix.memptr(), height * width * 4);
}

void Filter::invertImage(QImage *img)
{
  img->invertPixels();
}






