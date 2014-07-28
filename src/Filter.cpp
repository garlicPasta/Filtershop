#include <iostream>
#include <QtGui/QtGui>
#include <armadillo>
#include "Filter.hpp"
#include "MatHelper.hpp"
#include "Picturematrix.h"

using namespace std;
using namespace arma;


void Filter::gaussianBlur(QImage *img)
{
  PictureMatrix pMatrix = PictureMatrix(img);
  pMatrix.extendMat(50, PictureMatrix::same);
  pMatrix.shrinkMat(50);
  pMatrix.sendMatrixtoImage();
}

void Filter::invertImage(QImage *img)
{
  img->invertPixels();
}

Mat<uchar> conv(Mat<uchar> a, Mat<uchar> b)
{
  return Mat<uchar>(1,1);
}

