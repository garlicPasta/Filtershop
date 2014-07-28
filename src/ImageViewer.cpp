#include "ImageViewer.hpp"
#include <iostream>

// Defined Some usefull Macros

#define CREATEACT(actName, actFunction, label, shortcut) \
  actName = new QAction(tr(label), this);\
  actName->setShortcut(tr(shortcut));\
  connect(actName, SIGNAL(triggered()), this, SLOT(actFunction()));



ImageViewer::ImageViewer()
{
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);
  setCentralWidget(scrollArea);

  createActions();
  createMenus();

  setWindowTitle(tr("Filtershop"));
  resize(500, 400);
}

ImageViewer::ImageViewer(QString filePath)
{
  imageLabel = new QLabel;
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);
  setCentralWidget(scrollArea);

  createActions();
  createMenus();

  setWindowTitle(tr("Filtershop"));
  resize(500, 400);

  if (!filePath.isNull()){
    open(filePath);
  }
}

void ImageViewer::open()
{
  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open File"), QDir::currentPath());
  if (!fileName.isEmpty()) {
  this->currentImage =  new QImage(fileName);
    if (currentImage->isNull()) {
      QMessageBox::information(this, tr("Image Viewer"),
          tr("Cannot load %1.").arg(fileName));
      return;
    }
    imageLabel->setPixmap(QPixmap::fromImage(*currentImage));
    scaleFactor = 1.0;

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
      imageLabel->adjustSize();
  }
}

void ImageViewer::open(QString fileName)
{
  if (!fileName.isEmpty()) {
    this->currentImage = new QImage(fileName);
    if (currentImage->isNull()) {
      QMessageBox::information(this, tr("Image Viewer"),
          tr("Cannot load %1. ").arg(fileName));
      return;
    }
    imageLabel->setPixmap(QPixmap::fromImage(*currentImage));
    scaleFactor = 1.0;

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    gaussianBlurAct->setEnabled(true);
    pictureInfosAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
      imageLabel->adjustSize();
  }
}
void ImageViewer::drawImage()
{
  this->imageLabel->setPixmap(QPixmap::fromImage(*(this->currentImage)));
}

void ImageViewer::updateCanvas()
{
 imageLabel->setPixmap(QPixmap::fromImage(*currentImage));
}

void ImageViewer::print()
{
  Q_ASSERT(imageLabel->pixmap());
}

void ImageViewer::zoomIn()
{
  scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
  scaleImage(0.85);
}

void ImageViewer::normalSize()
{
  imageLabel->adjustSize();
  scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
  bool fitToWindow = fitToWindowAct->isChecked();
  scrollArea->setWidgetResizable(fitToWindow);
  
  if (!fitToWindow) {
    normalSize();
  }
  updateActions();
}

void ImageViewer::displayInfos()
{
  QMessageBox messageBox;
  messageBox.setWindowTitle(tr("Picture Infos"));
  QString text = QString("Height : %1 px\n").arg(currentImage->size().height());
  text.append(QString("Width : %1 px").arg(currentImage->size().width()));
  messageBox.setText(text);
  messageBox.setStandardButtons(QMessageBox::Ok);
  messageBox.setDefaultButton(QMessageBox::Ok);
  messageBox.exec();
}

void ImageViewer::gaussianBlur()
{
  Filter::gaussianBlur(this->currentImage);
  drawImage();
}

void ImageViewer::invertImage()
{
  Filter::invertImage(this->currentImage);
  drawImage();
}

void ImageViewer::createActions()
{
  //openAct = new QAction(tr("&Open..."), this);
  //openAct->setShortcut(tr("Ctrl+O"));
  //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
  CREATEACT(openAct, open, "&Open", "Ctrl+O");

  //printAct = new QAction(tr("&Print..."), this);
  //printAct->setShortcut(tr("Ctrl+P"));
  //connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
  CREATEACT(printAct, print,  "&Print", "Ctrl+P")
  printAct->setEnabled(false);

  
  exitAct = new QAction(tr("E&xit..."), this);
  exitAct->setShortcut(tr("Ctrl+X"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(()));
  //CREATEACT(exitAct, ,"&Exit", "Ctrl+X")
  

  //zoomInAct = new QAction(tr("Zoom &In"), this);
  //zoomInAct->setShortcut(tr("Ctrl++"));
  //connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
  CREATEACT(zoomInAct, zoomIn, "Zoom &In", "Ctrl++")
  zoomInAct->setEnabled(false);

  //zoomOutAct = new QAction(tr("Zoom &Out"), this);
  //zoomOutAct->setShortcut(tr("Ctrl+-"));
  //connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
  CREATEACT(zoomOutAct, zoomOut ,  "&Zoom &Out", "Ctrl+-")
  zoomOutAct->setEnabled(false);

  //normalSizeAct = new QAction(tr("&Normal Size"), this);
  //normalSizeAct->setShortcut(tr("Ctrl+0"));
  //connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
  CREATEACT(normalSizeAct, normalSize,  "Normal Size", "Ctrl+0")
  normalSizeAct->setEnabled(false);

  //fitToWindowAct = new QAction(tr("&Fit to Window"), this);
  //fitToWindowAct->setShortcut(tr("Ctrl+F"));
  //connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
  CREATEACT(fitToWindowAct, fitToWindow,  "&Fit to Window", "Ctrl+F")
  fitToWindowAct->setEnabled(false);
  fitToWindowAct->setCheckable(true);

  //pictureInfosAct = new QAction(tr("&Bild Informationen"), this);
  //pictureInfosAct->setShortcut(tr("Ctrl+I"));
  //connect(pictureInfosAct , SIGNAL(triggered()), this, SLOT(displayInfos()));
  CREATEACT(pictureInfosAct, displayInfos,  "&Picture Informations", "Ctrl+I")
  pictureInfosAct->setEnabled(false);

  //gaussianBlurAct = new QAction(tr("&Gaussian Blur"), this);
  //gaussianBlurAct->setShortcut(tr("Ctrl+B"));
  //connect(gaussianBlurAct, SIGNAL(triggered()), this, SLOT(gaussianBlur()));
  CREATEACT(gaussianBlurAct, gaussianBlur,  "&Gaussian Blur", "Ctrl+B")
  gaussianBlurAct->setEnabled(false);

  //invertImageAct = new QAction(tr("&Invert Image"), this);
  //connect(invertImageAct, SIGNAL(triggered()), this, SLOT(invertImage()));
  CREATEACT(invertImageAct, invertImage,  "&Invert Image", "Ctrl+2")
  invertImageAct->setEnabled(false);
}

void ImageViewer::createMenus()
{
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAct);
  fileMenu->addAction(printAct);
  fileMenu->addSeparator();
  fileMenu->addAction(pictureInfosAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  viewMenu = new QMenu(tr("&View"), this);
  viewMenu->addAction(zoomInAct);
  viewMenu->addAction(zoomOutAct);
  viewMenu->addAction(normalSizeAct);
  viewMenu->addSeparator();
  viewMenu->addAction(fitToWindowAct);

  filterMenu = new QMenu(tr("&Filter"));
  filterMenu->addAction(gaussianBlurAct);
  filterMenu->addAction(invertImageAct);
  
  helpMenu = new QMenu(tr("&Help"), this);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(viewMenu);
  menuBar()->addMenu(filterMenu);
  //menuBar()->addMenu(helpMenu);
}

void ImageViewer::updateActions()
{
  zoomInAct->setEnabled(!fitToWindowAct->isChecked());
  zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
  normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
  gaussianBlurAct->setEnabled(true);
}

void ImageViewer::scaleImage(double factor)
{
  Q_ASSERT(imageLabel->pixmap());
  scaleFactor *= factor;
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

  adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(scrollArea->verticalScrollBar(), factor);

  zoomInAct->setEnabled(scaleFactor < 3.0);
  zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
  scrollBar->setValue(int(factor * scrollBar->value()
        + ((factor - 1) * scrollBar->pageStep()/2)));
}


