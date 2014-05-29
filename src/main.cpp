/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27.05.2014 00:43:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <QtGui/QtGui>
#include "ImageViewer.hpp"
#include "Filter.hpp"


int main(int argv, char **args)
{
  QApplication app(argv, args);
  ImageViewer window;
  window.show();

  return app.exec();
}

