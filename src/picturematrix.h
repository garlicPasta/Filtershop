#ifndef PICTUREMATRIX_H
#define PICTUREMATRIX_H

#include <armadillo>
#include <QtGui/QtGui>
#include <vector>

class PictureMatrix
{
public:
    QImage *image;

    PictureMatrix();
    PictureMatrix(QImage &img);
    void sendMatrixtoImage();
    void setRChannel(bool value);
    void setGChannel(bool value);
    void setBChannel(bool value);
    void setAChannel(bool value);
    void gaussianBlur(int size);

private:
    int height;
    int width;
    arma::Mat<uchar> matrix;
    //RGBa
    arma::Cube<uchar> channels;
    bool activeChannel[4] = {true, true, true, true}; //RGBa

    void concatChannels();
    enum extendMode{same, black, white, cylindric};
    void extendMat(int offset, extendMode mode);
    void shrinkMat(int offset);
    void setRMatrix(arma::Mat<uchar> m);
    void setGMatrix(arma::Mat<uchar> m);
    void setAMatrix(arma::Mat<uchar> m);
    void setBMatrix(arma::Mat<uchar> m);

};
#endif // PICTUREMATRIX_H
