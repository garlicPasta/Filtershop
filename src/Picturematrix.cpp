#include "Picturematrix.h"
#include <armadillo>
#include <QtGui/QtGui>
#include <string>


PictureMatrix::PictureMatrix(QImage *img)
{
  int nTotalPicture = img->height() + 4 * img->width();
  image = img;
  matrix = arma::Mat<uchar>(img->bits(),img->height(), 4* img->width());

  /* Split Image to Matrix per Channel */
  int height = img->height();
  int width= img->width();

  red = arma::zeros<arma::Mat<uchar>>(height, width);
  green = arma::zeros<arma::Mat<uchar>>(height, width);
  blue = arma::zeros<arma::Mat<uchar>>(height, width);
  alpha = arma::zeros<arma::Mat<uchar>>(height, width);


  uchar * cPointer = img->bits();
  for( int i = 0; i < img->height() ; i++) {
    for( int j = 0; j < 4 * img->width() ; j++) {
      int matrixPosition = i * img->height() + j;
      int n = j / 4;
      if ( matrixPosition  % 4 == 0)
        red(i,n) = *cPointer;
      if ( matrixPosition % 4 == 1)
        green(i,n) = *cPointer;
      if ( matrixPosition  % 4 == 2)
        blue(i,n) = *cPointer;
      if ( matrixPosition % 4 == 3)
        alpha(i,n) = *cPointer;
      cPointer++;
    }
  }
}

void PictureMatrix::extendMat(int offset, extendMode mode)
{
    auto n_columns = matrix.n_cols;
    arma::Mat<uchar> left;
    arma::Mat<uchar> right;
    arma::Mat<uchar> top;
    arma::Mat<uchar> bottom;

    if (mode == PictureMatrix::extendMode::same){
        top = matrix.rows(0, offset - 1);
        bottom = matrix.rows(matrix.n_rows - 1 - offset, matrix.n_rows - 1);
        matrix = join_vert(top, matrix);
        matrix = join_vert(matrix, bottom);
        left = matrix.cols(0, offset - 1);
        right= matrix.cols(matrix.n_cols - 1 - offset, matrix.n_cols - 1);
    }

    if (mode == PictureMatrix::extendMode::black){
    }

    if (mode == PictureMatrix::extendMode::white){
    }
    if (mode == PictureMatrix::extendMode::cylindric){
    }
    matrix = join_horiz(left, matrix);
    matrix = join_horiz(matrix, right);
}

void PictureMatrix::shrinkMat(int offset)
{
    matrix = resize(matrix, matrix.n_rows - 1 - 2 * offset, matrix.n_cols -1 - 2 * offset);
}


void PictureMatrix::sendMatrixtoImage()
{
  memcpy(image->bits(), matrix.memptr(), matrix.n_cols * matrix.n_rows);
}
