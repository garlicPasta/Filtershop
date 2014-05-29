#ifndef IMAGE_VIEWER
#define IMAGE_VIEWER
#include <QtWidgets/QtWidgets>
#include <QtPrintSupport/QPrinter>
#include "Filter.hpp"


class ImageViewer : public QMainWindow
{
  Q_OBJECT

public:
  ImageViewer();

private slots:
  void open();
  void print();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void displayInfos();

private:
  void createActions();
  void createMenus();
  void updateActions();
  void scaleImage(double factor);
  void adjustScrollBar(QScrollBar *scrollBar, double factor);

  QLabel *imageLabel;
  QScrollArea *scrollArea;
  QImage *currentImage;
  Filter *filter;
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
  QAction *pictureInfosAct;

  QMenu *fileMenu;
  QMenu *viewMenu;
  QMenu *filterMenu;
  QMenu *helpMenu;
};
#endif
