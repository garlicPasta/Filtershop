/*
 * =====================================================================================
 *
 *       Filename:  GaussianBlur.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27.05.2014 23:11:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _GAUSSIANBLUR_
#define _GAUSSIANBLUR_

#include <QtWidgets/QtWidgets>
#include <armadillo>
#include "ImageViewer.hpp"

using namespace arma;

class Filter
{
  public:
    static void gaussianBlur(QImage *img);
    static void invertImage(QImage *img);
    static Mat<uchar> conv(Mat<uchar> a, Mat<uchar> b);
};

#endif
