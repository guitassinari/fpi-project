#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "image.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void openImage();
    void flipVertically();
private:
    Ui::MainWindow *ui;
    Image * currentImage;
    void updateEditedImageView(Image * image);
    void updateOriginalImageView(Image * image);
};

#endif // MAINWINDOW_H
