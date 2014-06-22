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

class Filter
{
  public:
    static void gaussianBlur(QImage *img);
    static void invertImage(QImage *img);

  private:
    static void qImg2armaMat(QImage *img);
};

#endif
