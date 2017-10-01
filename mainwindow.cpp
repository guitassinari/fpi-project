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
    QObject::connect(ui->OpenImageButton, SIGNAL(clicked(bool)),
                         this, SLOT(openImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(){
    QString imagePath = ui->lineEdit->text();
    Image * image = new Image(imagePath.toLatin1().data());
    currentImage = image;
    QImage qimage = image->toQImage();
    QGraphicsScene * originalImageScene = new QGraphicsScene;
    QGraphicsScene * editedImageScene = new QGraphicsScene;
    QGraphicsPixmapItem * originalImageItem = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
    QGraphicsPixmapItem * editedImageItem = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
    originalImageScene->addItem(originalImageItem);
    editedImageScene->addItem(editedImageItem);
    ui->OriginalImage->setScene(originalImageScene);
    ui->OriginalImage->show();
    ui->EditedImage->setScene(editedImageScene);
    ui->EditedImage->show();
}

void MainWindow::flipVertically(){

}
