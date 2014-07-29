#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <iostream>

// Defined Some usefull Macros

#define CREATEACT(actName, actFunction, label, shortcut) \
  actName = new QAction(tr(label), this);\
  actName->setShortcut(tr(shortcut));\
  connect(actName, SIGNAL(triggered()), this, SLOT(actFunction()));



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelImage->setBackgroundRole(QPalette::Base);
    ui->labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->labelImage->setScaledContents(true);


    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    setCentralWidget(ui->scrollArea);


    //createActions();
    //createMenus();

    setWindowTitle(tr("Filtershop"));
    resize(500, 400);
}

MainWindow::MainWindow(QString filePath)
{
  ui->labelImage = new QLabel;
  ui->labelImage->setBackgroundRole(QPalette::Base);
  ui->labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ui->labelImage->setScaledContents(true);

  ui->scrollArea = new QScrollArea;
  ui->scrollArea->setBackgroundRole(QPalette::Dark);
  ui->scrollArea->setWidget(ui->labelImage);
  setCentralWidget(ui->scrollArea);

  //createActions();
  //createMenus();

  setWindowTitle(tr("Filtershop"));
  resize(500, 400);

  if (!filePath.isNull()){
    open(filePath);
  }
}

void MainWindow::open()
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
    ui->labelImage->setPixmap(QPixmap::fromImage(*currentImage));
    scaleFactor = 1.0;


    ui->actionNormal_size->setEnabled(true);
    ui->actionFit_to_window->setEnabled(true);
    updateActions();

    if (!ui->actionFit_to_window->isChecked())
      ui->labelImage->adjustSize();
  }
}

void MainWindow::open(QString fileName)
{
  if (!fileName.isEmpty()) {
    this->currentImage = new QImage(fileName);
    if (currentImage->isNull()) {
      QMessageBox::information(this, tr("Image Viewer"),
          tr("Cannot load %1. ").arg(fileName));
      return;
    }
    ui->labelImage->setPixmap(QPixmap::fromImage(*currentImage));
    scaleFactor = 1.0;

    ui->actionFit_to_window->setEnabled(true);
    ui->actionGaussian_blur->setEnabled(true);
    ui->actionPicture_infos->setEnabled(true);
    updateActions();

    if (!ui->actionFit_to_window->isChecked())
      ui->labelImage->adjustSize();
  }
}
void MainWindow::drawImage()
{
  this->ui->labelImage->setPixmap(QPixmap::fromImage(*(this->currentImage)));
}

void MainWindow::updateCanvas()
{
 ui->labelImage->setPixmap(QPixmap::fromImage(*currentImage));
}

void MainWindow::zoomIn()
{
  scaleImage(0.85);
}

void MainWindow::zoomOut()
{
  scaleImage(1.25);
}

void MainWindow::normalSize()
{
  ui->labelImage->adjustSize();
  scaleFactor = 1.0;
}

void MainWindow::fitToWindow()
{
  bool fitToWindow = ui->actionFit_to_window->isChecked();
  ui->scrollArea->setWidgetResizable(fitToWindow);
  
  if (!fitToWindow) {
    normalSize();
  }
  updateActions();
}

void MainWindow::displayInfos()
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

void MainWindow::gaussianBlur()
{
  Filter::gaussianBlur(this->currentImage);
  drawImage();
}

void MainWindow::invertImage()
{
  Filter::invertImage(this->currentImage);
  drawImage();
}

/*
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
  

  //ui->actionZoom_in = new QAction(tr("Zoom &In"), this);
  //ui->actionZoom_in->setShortcut(tr("Ctrl++"));
  //connect(ui->actionZoom_in, SIGNAL(triggered()), this, SLOT(zoomIn()));
  CREATEACT(ui->actionZoom_in, zoomIn, "Zoom &In", "Ctrl++")
  ui->actionZoom_in->setEnabled(false);

  //ui->actionZoom_out = new QAction(tr("Zoom &Out"), this);
  //ui->actionZoom_out->setShortcut(tr("Ctrl+-"));
  //connect(ui->actionZoom_out, SIGNAL(triggered()), this, SLOT(zoomOut()));
  CREATEACT(ui->actionZoom_out->setEnabled(false);

  //ui->actionNormal_size = new QAction(tr("&Normal Size"), this);
  //ui->actionNormal_size->setShortcut(tr("Ctrl+0"));
  //connect(ui->actionNormal_size, SIGNAL(triggered()), this, SLOT(normalSize()));
  CREATEACT(ui->actionNormal_size, normalSize,  "Normal Size", "Ctrl+0")
  ui->actionNormal_size->setEnabled(false);

  //fitToWindowAct = new QAction(tr("&Fit to Window"), this);
  //fitToWindowAct->setShortcut(tr("Ctrl+F"));
  //connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
  CREATEACT(fitToWindowAct, fitToWindow,  "&Fit to Window", "Ctrl+F")
  fitToWindowAct->setEnabled(false);
  fitToWindowAct->setCheckable(true);

  //ui->actionPicture_infos = new QAction(tr("&Bild Informationen"), this);
  //ui->actionPicture_infos->setShortcut(tr("Ctrl+I"));
  //connect(ui->actionPicture_infos , SIGNAL(triggered()), this, SLOT(displayInfos()));
  CREATEACT(ui->actionPicture_infos, displayInfos,  "&Picture Informations", "Ctrl+I")
  ui->actionPicture_infos->setEnabled(false);

  //ui->actionGaussian_blur = new QAction(tr("&Gaussian Blur"), this);
  //ui->actionGaussian_blur->setShortcut(tr("Ctrl+B"));
  //connect(ui->actionGaussian_blur, SIGNAL(triggered()), this, SLOT(gaussianBlur()));
  CREATEACT(ui->actionGaussian_blur, gaussianBlur,  "&Gaussian Blur", "Ctrl+B")
  ui->actionGaussian_blur->setEnabled(false);

  //invertImageAct = new QAction(tr("&Invert Image"), this);
  //connect(invertImageAct, SIGNAL(triggered()), this, SLOT(invertImage()));
  CREATEACT(invertImageAct, invertImage,  "&Invert Image", "Ctrl+2")
  invertImageAct->setEnabled(false);
}*/
/*
void MainWindow::createMenus()
{
  fileMenu = new QMenu(tr("&File"), this);
  fileMenu->addAction(openAct);
  fileMenu->addAction(printAct);
  fileMenu->addSeparator();
  fileMenu->addAction(ui->actionPicture_infos);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  viewMenu = new QMenu(tr("&View"), this);
  viewMenu->addAction(ui->actionZoom_in);
  viewMenu->addAction(ui->actionZoom_out);
  viewMenu->addAction(ui->actionNormal_size);
  viewMenu->addSeparator();
  viewMenu->addAction(fitToWindowAct);

  filterMenu = new QMenu(tr("&Filter"));
  filterMenu->addAction(ui->actionGaussian_blur);
  filterMenu->addAction(invertImageAct);
  
  helpMenu = new QMenu(tr("&Help"), this);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(viewMenu);
  menuBar()->addMenu(filterMenu);
  //menuBar()->addMenu(helpMenu);
}
*/

void MainWindow::updateActions()
{
  ui->actionZoom_in->setEnabled(!ui->actionFit_to_window->isChecked());
  ui->actionZoom_out->setEnabled(!ui->actionFit_to_window->isChecked());
  ui->actionNormal_size->setEnabled(!ui->actionFit_to_window->isChecked());
  ui->actionGaussian_blur->setEnabled(true);
}

void MainWindow::scaleImage(double factor)
{
  Q_ASSERT(ui->labelImage->pixmap());
  scaleFactor *= factor;
  ui->labelImage->resize(scaleFactor * ui->labelImage->pixmap()->size());

  adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
  adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

  ui->actionZoom_in->setEnabled(scaleFactor < 3.0);
  ui->actionZoom_out->setEnabled(scaleFactor > 0.333);
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
  scrollBar->setValue(int(factor * scrollBar->value()
        + ((factor - 1) * scrollBar->pageStep()/2)));
}



void MainWindow::on_actionOpen_triggered()
{
    open();
}

void MainWindow::on_actionZoom_in_triggered()
{
    zoomIn();
}

void MainWindow::on_actionZoom_out_triggered()
{
    zoomOut();
}

void MainWindow::on_actionNormal_size_triggered()
{
    normalSize();
}

void MainWindow::on_actionFit_to_window_triggered()
{
   fitToWindow();
}

void MainWindow::on_actionPicture_infos_triggered()
{
   displayInfos();
}
