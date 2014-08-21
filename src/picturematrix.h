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
    void sharpen();
    void edgeDetection();

private:
    int height;
    int width;
    arma::Mat<uchar> matrix;
    //RGBa
    arma::Cube<double> channels;
    bool activeChannel[4] = {true, true, true, true}; //RGBa

    enum extendMode{same, black, white, cylindric};

    void concatChannels();
    void extendMat(int offset, extendMode mode);
    void setRMatrix(arma::Mat<double> m);
    void setGMatrix(arma::Mat<double> m);
    void setAMatrix(arma::Mat<double> m);
    void setBMatrix(arma::Mat<double> m);
    void convo(arma::Mat<double> m);

};
#endif // PICTUREMATRIX_H
