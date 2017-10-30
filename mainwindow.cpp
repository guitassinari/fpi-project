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
    QObject::connect(ui->ConvolutionButton, SIGNAL(clicked(bool)),
                         this, SLOT(convolute()));
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

void MainWindow::convolute(){
    float convolutionMatrix[9];
    convolutionMatrix[0] = ui->MatrixValue0->value();
    convolutionMatrix[1] = ui->MatrixValue1->value();
    convolutionMatrix[2] = ui->MatrixValue2->value();
    convolutionMatrix[3] = ui->MatrixValue3->value();
    convolutionMatrix[4] = ui->MatrixValue4->value();
    convolutionMatrix[5] = ui->MatrixValue5->value();
    convolutionMatrix[6] = ui->MatrixValue6->value();
    convolutionMatrix[7] = ui->MatrixValue7->value();
    convolutionMatrix[8] = ui->MatrixValue8->value();
    currentImage->convolute(convolutionMatrix);
    updateEditedImageView(currentImage);


}
