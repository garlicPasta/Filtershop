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
  channels = arma::Cube<double>(height, width, 4);

  for( int i = 0; i < img.height() ; i++) {
    for( int j = 0; j < img.width() ; j++) {
      QRgb value = img.pixel(i,j);
      channels(i,j,0) =  qRed(value) / 255.0;
      channels(i,j,1) =  qGreen(value) / 255.0;
      channels(i,j,2) =  qBlue(value) / 255.0;
      channels(i,j,3) =  qAlpha(value) / 255.0;
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

void PictureMatrix::setRMatrix(arma::Mat<double> m){
  channels.slice(0)= m;
}

void PictureMatrix::setGMatrix(arma::Mat<double> m){
  channels.slice(1)= m;
}

void PictureMatrix::setBMatrix(arma::Mat<double> m){
  channels.slice(2)= m;
}

void PictureMatrix::setAMatrix(arma::Mat<double> m){
  channels.slice(3)= m;
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
  matrix = join_horiz(matrix, right);
  }
  matrix = join_horiz(left, matrix);
}

void PictureMatrix::concatChannels(){

  arma::Col<double> vecRed = arma::vectorise(channels.slice(0));

  if (!activeChannel[0]) {
    vecRed = vecRed.zeros();
  }
  arma::Col<double> vecBlue = arma::vectorise(channels.slice(1));
  if (!activeChannel[1]) {
    vecBlue = vecBlue.zeros();
  }
  arma::Col<double> vecGreen = arma::vectorise(channels.slice(2));
  if (!activeChannel[2]) {
    vecGreen = vecGreen.zeros();
  }
  arma::Col<double> vecAlpha = arma::vectorise(channels.slice(3));
  if (!activeChannel[3]) {
    vecAlpha = vecAlpha.zeros();
  }

  arma::Mat<double> temp_mat1 = arma::join_rows(vecGreen, vecBlue);
  arma::Mat<double> temp_mat2 = arma::join_rows(vecRed, vecAlpha);
  // Convert from Mat<double> to Mat<uchar>
  matrix = arma::conv_to<arma::Mat<uchar> >::from(255 * arma::join_rows(temp_mat1, temp_mat2));
  matrix = matrix.t();
}

void PictureMatrix::sendMatrixtoImage()
{
  concatChannels();
  memcpy(image->bits(), matrix.memptr(), matrix.n_cols * matrix.n_rows);
}

void PictureMatrix::gaussianBlur(int size){
  arma::Mat<double> gaussianMatrix(size, size);
  gaussianMatrix.fill(0.25);
  //gaussianMatrix = arma::normalise(gaussianMatrix);
  convo(gaussianMatrix);
}

void PictureMatrix::sharpen(){
    arma::Mat<double> sharpMatrix(3,3);
    sharpMatrix << 0 << -1 << 0 << arma::endr
                << -1 << 5 << -1 << arma::endr
                << 0 << -1 << 0 << arma::endr;
    convo(sharpMatrix);
}



void PictureMatrix::edgeDetection(){
    arma::Mat<double> sharpMatrix(3, 3);
    sharpMatrix << -1 << -1 << -1 << arma::endr
                << -1 << 8 << -1 << arma::endr
                << -1 << -1 << -1 << arma::endr;
    convo(sharpMatrix);
}

void PictureMatrix::convo(arma::Mat<double> m){
    m.resize(height, width);
    auto koeff = arma::fft2(m);
    for (int i=0; i<4; ++i){
      auto slice = arma::ifft2(arma::fft2(channels.slice(i)) % koeff);
      channels.slice(i) = arma::real(slice);
    }
}
