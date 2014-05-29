#include <armadillo>
#include <QtGui/QtGui>
#include "Filter.hpp"

Filter::Filter(QImage *img)
{
  image = img;
}

void Filter::gaussianBlur()
{
  image->invertPixels();
}



