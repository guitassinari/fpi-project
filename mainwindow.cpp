#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QTreeView>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->QuantizationNumber->setEnabled(false);
    ui->QuantizationButton->setEnabled(false);
    ui->HistogramButton->setEnabled(false);
    ui->EqualizeHistogramButton->setEnabled(false);

    QObject::connect(ui->OpenImageButton, SIGNAL(clicked(bool)),
                         this, SLOT(openImage()));
    QObject::connect(ui->FlipVerticallyButton, SIGNAL(clicked(bool)),
                         this, SLOT(flipVertically()));
    QObject::connect(ui->FlipHorizontallyButton, SIGNAL(clicked(bool)),
                         this, SLOT(flipHorizontally()));
    QObject::connect(ui->SaveImageButton, SIGNAL(clicked(bool)),
                         this, SLOT(saveImage()));
    QObject::connect(ui->GreyScaleButton, SIGNAL(clicked(bool)),
                         this, SLOT(toGreyScale()));
    QObject::connect(ui->QuantizationButton, SIGNAL(clicked(bool)),
                         this, SLOT(quantize()));
    QObject::connect(ui->NegativeButton, SIGNAL(clicked(bool)),
                         this, SLOT(negative()));
    QObject::connect(ui->RotateButton, SIGNAL(clicked(bool)),
                         this, SLOT(rotate()));
    QObject::connect(ui->HistogramButton, SIGNAL(clicked(bool)),
                         this, SLOT(showHistogram()));
    QObject::connect(ui->ContrastButton, SIGNAL(clicked(bool)),
                         this, SLOT(enhanceContrast()));
    QObject::connect(ui->BrightnessButton, SIGNAL(clicked(bool)),
                         this, SLOT(enhanceBrightness()));
    QObject::connect(ui->EqualizeHistogramButton, SIGNAL(clicked(bool)),
                         this, SLOT(equalizeHistogram()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(){
    QString imagePath = ui->lineEdit->text();
    currentImage= new Image(imagePath.toLatin1().data());
    originalImage = new Image(imagePath.toLatin1().data());
    updateOriginalImageView(originalImage);
    updateEditedImageView(originalImage);
    ui->QuantizationNumber->setEnabled(false);
    ui->QuantizationButton->setEnabled(false);
    ui->HistogramButton->setEnabled(false);
    ui->EqualizeHistogramButton->setEnabled(false);
}

void MainWindow::flipVertically(){
   currentImage->flipVertically();
   updateEditedImageView(currentImage);
}

void MainWindow::flipHorizontally(){
    currentImage->flipHorizontally();
    updateEditedImageView(currentImage);
}

void MainWindow::updateEditedImageView(Image * image){
    QImage qimage = image->toQImage();
    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
    scene->addItem(item);
    ui->EditedImage->setScene(scene);
    ui->EditedImage->show();
}

void MainWindow::updateOriginalImageView(Image * image){
    QImage qimage = image->toQImage();
    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
    scene->addItem(item);
    ui->OriginalImage->setScene(scene);
    ui->OriginalImage->show();
}

void MainWindow::updateHistogramView(Image * image){
    QImage qimage = image->getHistogram();
    updateEditedImageView(image);
    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
    scene->addItem(item);
    ui->Histogram->setScene(scene);
    ui->Histogram->show();
}

void MainWindow::saveImage(){
    QString path = ui->PathToSave->text();
    currentImage->write(path.toLatin1().data());
}

void MainWindow::toGreyScale(){
    currentImage->toGreyScale();
    ui->QuantizationButton->setEnabled(true);
    ui->QuantizationNumber->setEnabled(true);
    ui->EqualizeHistogramButton->setEnabled(true);
    ui->HistogramButton->setEnabled(true);
    updateEditedImageView(currentImage);
}

void MainWindow::quantize(){
    int quantizationNumber = ui->QuantizationNumber->value();
    currentImage->quantize(quantizationNumber);
    updateEditedImageView(currentImage);
}

void MainWindow::negative(){
    currentImage->negative();
    updateEditedImageView(currentImage);
}

void MainWindow::rotate(){
    currentImage->rotate();
    updateEditedImageView(currentImage);
}

void MainWindow::showHistogram(){
    updateHistogramView(currentImage);
}

void MainWindow::enhanceBrightness(){
    int brightnessValue = ui->QuantizationNumber->value();
    currentImage->enhanceBrightness(brightnessValue);
    updateEditedImageView(currentImage);
}

void MainWindow::enhanceContrast(){
    double contrastValue = ui->ContrastValue->value();
    currentImage->enhanceContrast(contrastValue);
    updateEditedImageView(currentImage);
}

void MainWindow::equalizeHistogram(){
    currentImage->equalizeHistogram();
    showHistogram();
    updateEditedImageView(currentImage);
}
