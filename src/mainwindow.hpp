#ifndef _IMAGEVIEWER_
#define _IMAGEVIEWER_

#include <QtWidgets/QtWidgets>
#include <QtPrintSupport/QPrinter>
#include <QMainWindow>
#include <QtGui/QtGui>
#include "filter.hpp"
#include "picturematrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  MainWindow(QString filePath);
  QImage currentImage;
  PictureMatrix picture;
    
private slots:
  void open();
  void open(QString filename);
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void displayInfos();
  void gaussianBlur();
  void invertImage();

  void drawImage();

  void on_actionOpen_triggered();
  void on_actionZoom_in_triggered();
  void on_actionZoom_out_triggered();
  void on_actionNormal_size_triggered();
  void on_actionFit_to_window_triggered();
  void on_actionPicture_infos_triggered();
  void on_actionGaussian_blur_triggered();
  void on_checkBox_blue_toggled(bool checked);
  void on_checkBox_red_toggled(bool checked);
  void on_checkBox_green_toggled(bool checked);
  void on_pushButton_clicked();

private:
  void createActions();
  void createMenus();
  void updateActions();
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar *scrollBar, double factor);

  double scaleFactor;

#ifndef QT_NO_PRINTER
  QPrinter printer;
 #endif

  Ui::MainWindow * ui;

};
#endif
