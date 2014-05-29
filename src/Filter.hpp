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

class Filter : public QWidget
{
  Q_OBJECT

  public:
    Filter(QImage *img);
    
  public slots:
    void gaussianBlur();

  private:
  QImage *image;
};

#endif
