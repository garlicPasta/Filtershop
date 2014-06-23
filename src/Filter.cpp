#include <iostream>
#include <QtGui/QtGui>
#include <armadillo>
#include "Filter.hpp"
#include "MatHelper.hpp"

using namespace std;
using namespace arma;


void Filter::gaussianBlur(QImage *img)
{
  Mat<uchar> pMatrix = MatHelper::qImg2Mat(img);
  pMatrix = pMatrix / 2;
  MatHelper::sendMatrixtoImage(pMatrix, img);
}

void Filter::invertImage(QImage *img)
{
  img->invertPixels();
}






