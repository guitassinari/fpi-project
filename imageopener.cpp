#include "imageopener.h"
#include "ui_imageopener.h"

ImageOpener::ImageOpener(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageOpener)
{
    ui->setupUi(this);
}

ImageOpener::~ImageOpener()
{
    delete ui;
}
