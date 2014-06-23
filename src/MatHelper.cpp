#include <iostream>
#include <QtGui/QtGui>
#include <armadillo>
#include "MatHelper.hpp"

using namespace std;
using namespace arma;

Mat<uchar> MatHelper::qImg2Mat(QImage *img)
{
  int height= img->height();
  int width = img->width();
  return Mat<uchar>(img->bits(), height, width * 4); // multiplay by 4 because of RGBa
}

void MatHelper::sendMatrixtoImage(Mat<uchar> m, QImage *img)
{
  memcpy(img->bits(), m.memptr(), img->height() * img->width() * 4);
}
