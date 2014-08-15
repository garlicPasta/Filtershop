#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <iostream>

// Defined Some usefull Macros
/*Controller and View */

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    setCentralWidget(ui->scrollArea);

    setWindowTitle(tr("Filtershop"));
    open("resources/img/Lenna.jpg");
    resize(500, 400);
}

MainWindow::MainWindow(QString filePath){
    MainWindow::MainWindow;
    open(filePath);
}

void MainWindow::open()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Open File"), QDir::currentPath());
  open(fileName);
}

void MainWindow::open(QString fileName)
{
  if (!fileName.isEmpty()) {
    this->currentImage = QImage(fileName);
    this->coreImage = QImage(fileName);
    if (currentImage.isNull() || coreImage.isNull()) {
      QMessageBox::information(this, tr("Image Viewer"),
                               tr("Cannot load %1. ").arg(fileName));
      return;
    }
    ui->labelImage->setPixmap(QPixmap::fromImage(currentImage));
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
  this->ui->labelImage->setPixmap(QPixmap::fromImage((this->currentImage)));
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
  QString text = QString("Height : %1 px\n").arg(currentImage.size().height());
  text.append(QString("Width : %1 px").arg(currentImage.size().width()));
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

void MainWindow::on_actionGaussian_blur_triggered()
{
    gaussianBlur();
}

void MainWindow::on_checkBox_blue_toggled(bool checked)
{
  qDebug() << "Blue toggle";
  currentImage = coreImage.copy();
  Filter::display_active_channels(currentImage, ui->checkBox_red->isChecked(), ui->checkBox_green->isChecked(), ui->checkBox_blue->isChecked());
  drawImage();
}

void MainWindow::on_checkBox_red_toggled(bool checked)
{
  qDebug() << "Red toggle";
  currentImage = coreImage.copy();
  Filter::display_active_channels(currentImage, ui->checkBox_red->isChecked(), ui->checkBox_green->isChecked(), ui->checkBox_blue->isChecked());
  drawImage();
}


void MainWindow::on_checkBox_green_toggled(bool checked)
{
  qDebug() << "Green toggle";
  currentImage = coreImage.copy();
  Filter::display_active_channels(this->currentImage, ui->checkBox_red->isChecked(), ui->checkBox_green->isChecked(), ui->checkBox_blue->isChecked());
  drawImage();
}

void MainWindow::on_pushButton_clicked()
{
  Filter::dark_square(currentImage);
  drawImage();
}
