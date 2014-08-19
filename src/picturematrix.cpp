#include "picturematrix.h"
#include <armadillo>
#include <QtGui/QtGui>
#include <string>


PictureMatrix::PictureMatrix(){
    image = 0;
}

PictureMatrix::PictureMatrix(QImage &img)
{
  image = &img;
  matrix = arma::Mat<uchar>(img.bits(),img.height(), 4* img.width());


  /* Split Image to Matrix per Channel */
  height = img.height();
  width= img.width();
  channels = arma::Cube<uchar>(height, width, 4);

  for( int i = 0; i < img.height() ; i++) {
    for( int j = 0; j < img.width() ; j++) {
      QRgb value = img.pixel(i,j);
      channels(i,j,0) = (uchar) qRed(value);
      channels(i,j,1) = (uchar) qGreen(value);
      channels(i,j,2) = (uchar) qBlue(value);
      channels(i,j,3) = (uchar)qAlpha(value);
    }
  }
}

void PictureMatrix::setRChannel(bool value)
{
   activeChannel[0] = value;
}

void PictureMatrix::setGChannel(bool value)
{
   activeChannel[1] = value;
}

void PictureMatrix::setBChannel(bool value)
{
   activeChannel[2] = value;
}

void PictureMatrix::setAChannel(bool value)
{
   activeChannel[3] = value;
}

void PictureMatrix::setRMatrix(arma::Mat<uchar> m){
  //channels.slice(0)= m;
}

void PictureMatrix::setGMatrix(arma::Mat<uchar> m){
  //channels.slice(1)= m;
}

void PictureMatrix::setBMatrix(arma::Mat<uchar> m){
  //channels.slice(2)= m;
}

void PictureMatrix::setAMatrix(arma::Mat<uchar> m){
  //channels.slice(3)= m;
}


void PictureMatrix::extendMat(int offset, extendMode mode)
{
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
  //matrix = resize(matrix, matrix.n_rows - 1 - 2 * offset, matrix.n_cols -1 - 2 * offset);
}

void PictureMatrix::concatChannels(){

  arma::Col<uchar> vecRed = arma::vectorise(channels.slice(0));

  if (!activeChannel[0]) {
    vecRed = vecRed.zeros();
  }
  arma::Col<uchar> vecBlue = arma::vectorise(channels.slice(1));
  if (!activeChannel[1]) {
    vecBlue = vecBlue.zeros();
  }
  arma::Col<uchar> vecGreen = arma::vectorise(channels.slice(2));
  if (!activeChannel[2]) {
    vecGreen = vecGreen.zeros();
  }
  arma::Col<uchar> vecAlpha = arma::vectorise(channels.slice(3));
  if (!activeChannel[3]) {
    vecAlpha = vecAlpha.zeros();
  }

  arma::Mat<uchar> temp_mat1 = arma::join_rows(vecGreen, vecBlue);
  arma::Mat<uchar> temp_mat2 = arma::join_rows(vecRed, vecAlpha);
  matrix = arma::join_rows(temp_mat1, temp_mat2);
  matrix = matrix.t();
}

void PictureMatrix::sendMatrixtoImage()
{
  concatChannels();
  memcpy(image->bits(), matrix.memptr(), matrix.n_cols * matrix.n_rows);
}

void PictureMatrix::gaussianBlur(int size){
  arma::Mat<uchar> gaussianMatrix(size, size);
  for(int i=0; i < 4; i++){
    channels.slice(i) = arma::conv(channels.slice(i),gaussianMatrix);
  }
}
