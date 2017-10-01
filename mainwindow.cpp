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
    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
    scene->addItem(item);
    ui->OriginalImage->setScene(scene);
    ui->OriginalImage->show();
}
