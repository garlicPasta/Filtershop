#include "ImageViewer.hpp"
#include <iostream>


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
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
  std::cout << fileName.toStdString() << std::endl;
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

void ImageViewer::createActions()
{
  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  printAct = new QAction(tr("&Print..."), this);
  printAct->setEnabled(false);
  printAct->setShortcut(tr("Ctrl+P"));
  connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

  
  exitAct = new QAction(tr("E&xit..."), this);
  exitAct->setShortcut(tr("Ctrl+X"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(()));
  

  zoomInAct = new QAction(tr("Zoom &In"), this);
  zoomInAct->setShortcut(tr("Ctrl++"));
  zoomInAct->setEnabled(false);
  connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

  zoomOutAct = new QAction(tr("Zoom &Out"), this);
  zoomOutAct->setShortcut(tr("Ctrl+-"));
  zoomOutAct->setEnabled(false);
  connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

  normalSizeAct = new QAction(tr("&Normal Size"), this);
  normalSizeAct->setShortcut(tr("Ctrl+0"));
  normalSizeAct->setEnabled(false);
  connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

  fitToWindowAct = new QAction(tr("&Fit to Window"), this);
  fitToWindowAct->setEnabled(false);
  fitToWindowAct->setCheckable(true);
  fitToWindowAct->setShortcut(tr("Ctrl+F"));
  connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

  pictureInfosAct = new QAction(tr("&Bild Informationen"), this);
  pictureInfosAct->setShortcut(tr("Ctrl+I"));
  pictureInfosAct->setEnabled(false);
  connect(pictureInfosAct , SIGNAL(triggered()), this, SLOT(displayInfos()));

  gaussianBlurAct = new QAction(tr("&Gaussian Blur"), this);
  gaussianBlurAct->setShortcut(tr("Ctrl+B"));
  gaussianBlurAct->setEnabled(false);
  connect(gaussianBlurAct, SIGNAL(triggered()), this, SLOT(gaussianBlur()));

  invertImageAct = new QAction(tr("&Invert Image"), this);
  invertImageAct->setEnabled(false);
  connect(invertImageAct, SIGNAL(triggered()), this, SLOT(invertImage()));
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

