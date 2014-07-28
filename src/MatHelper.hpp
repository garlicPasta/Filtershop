#ifndef _MATHELPER_
#define _MATHELPER_

#include <QtGui/QtGui>
#include <armadillo>
#include <string.h>

using namespace arma;

class MatHelper
{
  public:
    static Mat<uchar> qImg2Mat(QImage *img);
    static void sendMatrixtoImage(Mat<uchar> m,  QImage *img);
    static Mat<uchar> extendMat (Mat<uchar> m, int offset, std::string mode);
};

#endif
