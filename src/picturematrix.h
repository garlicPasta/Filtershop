#ifndef PICTUREMATRIX_H
#define PICTUREMATRIX_H

#include <armadillo>
#include <QtGui/QtGui>

class PictureMatrix
{
public:
    QImage *image;
    int height;
    int width;
    arma::Mat<uchar> matrix;
    arma::Mat<uchar> red;
    arma::Mat<uchar> green;
    arma::Mat<uchar> blue;
    arma::Mat<uchar> alpha;

    PictureMatrix(QImage &img);
    void sendMatrixtoImage();
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
