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
#include <QApplication>
#include <iostream>
#include "mainwindow.hpp"


int main(int argv, char **args)
{
  QApplication app(argv, args);
  QApplication::setApplicationName("Filter Shop");
  QApplication::setApplicationVersion("0.2");

  QCommandLineParser parser;
  parser.setApplicationDescription("Programm for calculating various Filters");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("source", QApplication::translate("main", 
        "Image for applying filer"));
  parser.process(app);
  const QStringList options = parser.positionalArguments();


  for ( QString option : options)
  {
    std::cout << option.toStdString() << std::endl;
  }
  
  if (options.length() > 100){
    std::cout << "Hello" << std::endl;
    MainWindow window(options.first());
    window.show();
  }else{
  }
  MainWindow window;
  window.show();
  return app.exec();
}

