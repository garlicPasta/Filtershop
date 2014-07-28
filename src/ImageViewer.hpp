#ifndef _IMAGEVIEWER_
#define _IMAGEVIEWER_

#include <QtWidgets/QtWidgets>
#include <QtPrintSupport/QPrinter>
#include <QtGui/QtGui>
#include "Filter.hpp"

class ImageViewer : public QMainWindow
{
  Q_OBJECT

public:
  ImageViewer();
  ImageViewer(QString filePath);
  QImage *currentImage;

public slots:
  void updateCanvas();
    
private slots:
  void open();
  void open(QString filename);
  void print();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void displayInfos();
  void gaussianBlur();
  void invertImage();

private:
  void createActions();
  void createMenus();
  void updateActions();
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar *scrollBar, double factor);
  void drawImage();

  QLabel *imageLabel;
  QScrollArea *scrollArea;
  double scaleFactor;

#ifndef QT_NO_PRINTER
  QPrinter printer;
 #endif

  QAction *openAct;
  QAction *printAct;
  QAction *exitAct;
  QAction *zoomInAct;
  QAction *zoomOutAct;
  QAction *normalSizeAct;
  QAction *fitToWindowAct;
  QAction *gaussianBlurAct;
  QAction *invertImageAct;
  QAction *pictureInfosAct;
  QMenu *fileMenu;
  QMenu *viewMenu;
  QMenu *filterMenu;
  QMenu *helpMenu;
};
#endif
