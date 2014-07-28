#ifndef PICTUREMATRIX_H
#define PICTUREMATRIX_H

#include <armadillo>
#include <QtGui/QtGui>

class PictureMatrix
{
public:
    QImage *image;
    arma::Mat<uchar> matrix;
    arma::Mat<uchar> red;
    arma::Mat<uchar> green;
    arma::Mat<uchar> blue;
    arma::Mat<uchar> alpha;

    PictureMatrix(QImage *img);
    void sendMatrixtoImage();
    enum extendMode{same, black, white, cylindric};
    void extendMat(int offset, extendMode mode);
    void shrinkMat(int offset);
};

#endif // PICTUREMATRIX_H
