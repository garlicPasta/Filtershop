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
#include "mainwindow.hpp"


class Filter
{
  public:
    static void gaussianBlur(QImage &img);
    static void invertImage(QImage &img);
    static arma::Mat<uchar> conv(arma::Mat<uchar> a, arma::Mat<uchar> b);
    static void display_active_channels(QImage &img, bool r, bool g, bool b);
    static void dark_square(QImage &img);
};

#endif
