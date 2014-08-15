#include "picturematrix.h"
#include <armadillo>
#include <QtGui/QtGui>
#include <string>


PictureMatrix::PictureMatrix(QImage &img)
{
    int nTotalPicture = img.height() + 4 * img.width();
    image = &img;
    matrix = arma::Mat<uchar>(img.bits(),img.height(), 4* img.width());

    /* Split Image to Matrix per Channel */
    height = img.height();
    width= img.width();

    red = arma::zeros<arma::Mat<uchar>>(height, width);
    green = arma::zeros<arma::Mat<uchar>>(height, width);
    blue = arma::zeros<arma::Mat<uchar>>(height, width);
    alpha = arma::zeros<arma::Mat<uchar>>(height, width);

    uchar * cPointer = img.bits();
    for( int i = 0; i < img.height() ; i++) {
      for( int j = 0; j < img.width() ; j++) {
        QRgb value = img.pixel(i,j);
          red(i,j) = (uchar) qRed(value);
          green(i,j) = (uchar) qGreen(value);
          blue(i,j) = (uchar) qBlue(value);
          alpha(i,j) = (uchar)qAlpha(value);
      }
    }
}

void PictureMatrix::setRMatrix(arma::Mat<uchar> m){
  red = m;
}

void PictureMatrix::setGMatrix(arma::Mat<uchar> m){
  green = m;
}

void PictureMatrix::setBMatrix(arma::Mat<uchar> m){
  blue = m;
}

void PictureMatrix::setAMatrix(arma::Mat<uchar> m){
  alpha = m;
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

void PictureMatrix::concatChannels(){
  arma::Col<uchar> vecRed = arma::vectorise(red);
  arma::Col<uchar> vecBlue = arma::vectorise(blue);
  arma::Col<uchar> vecGreen = arma::vectorise(green);
  arma::Col<uchar> vecAlpha = arma::vectorise(alpha);
  arma::Mat<uchar> temp_mat1 = arma::join_rows(vecBlue, vecGreen);
  arma::Mat<uchar> temp_mat2 = arma::join_rows(vecRed, vecAlpha);
  matrix = arma::join_rows(temp_mat1, temp_mat2);
  matrix = matrix.t();
}

void PictureMatrix::sendMatrixtoImage()
{
  concatChannels();
  memcpy(image->bits(), matrix.memptr(), matrix.n_cols * matrix.n_rows);
}
