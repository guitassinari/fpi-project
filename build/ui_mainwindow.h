/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *FlipHorizontallyButton;
    QPushButton *GreyScaleButton;
    QPushButton *OpenImageButton;
    QPushButton *FlipVerticallyButton;
    QGraphicsView *OriginalImage;
    QGraphicsView *EditedImage;
    QLineEdit *lineEdit;
    QPushButton *SaveImageButton;
    QLineEdit *PathToSave;
    QPushButton *QuantizationButton;
    QSpinBox *QuantizationNumber;
    QPushButton *NegativeButton;
    QPushButton *RotateButton;
    QGraphicsView *Histogram;
    QPushButton *HistogramButton;
    QPushButton *ContrastButton;
    QPushButton *BrightnessButton;
    QDoubleSpinBox *ContrastValue;
    QPushButton *EqualizeHistogramButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuTassinari_s_Phototool;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1195, 727);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FlipHorizontallyButton = new QPushButton(centralWidget);
        FlipHorizontallyButton->setObjectName(QStringLiteral("FlipHorizontallyButton"));
        FlipHorizontallyButton->setGeometry(QRect(880, 80, 261, 25));
        GreyScaleButton = new QPushButton(centralWidget);
        GreyScaleButton->setObjectName(QStringLiteral("GreyScaleButton"));
        GreyScaleButton->setGeometry(QRect(880, 230, 261, 25));
        OpenImageButton = new QPushButton(centralWidget);
        OpenImageButton->setObjectName(QStringLiteral("OpenImageButton"));
        OpenImageButton->setGeometry(QRect(280, 10, 171, 25));
        FlipVerticallyButton = new QPushButton(centralWidget);
        FlipVerticallyButton->setObjectName(QStringLiteral("FlipVerticallyButton"));
        FlipVerticallyButton->setGeometry(QRect(880, 50, 261, 25));
        OriginalImage = new QGraphicsView(centralWidget);
        OriginalImage->setObjectName(QStringLiteral("OriginalImage"));
        OriginalImage->setGeometry(QRect(30, 50, 421, 301));
        EditedImage = new QGraphicsView(centralWidget);
        EditedImage->setObjectName(QStringLiteral("EditedImage"));
        EditedImage->setGeometry(QRect(455, 50, 401, 301));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 10, 241, 25));
        SaveImageButton = new QPushButton(centralWidget);
        SaveImageButton->setObjectName(QStringLiteral("SaveImageButton"));
        SaveImageButton->setGeometry(QRect(720, 10, 131, 25));
        PathToSave = new QLineEdit(centralWidget);
        PathToSave->setObjectName(QStringLiteral("PathToSave"));
        PathToSave->setGeometry(QRect(460, 10, 251, 25));
        QuantizationButton = new QPushButton(centralWidget);
        QuantizationButton->setObjectName(QStringLiteral("QuantizationButton"));
        QuantizationButton->setGeometry(QRect(1010, 330, 131, 25));
        QuantizationNumber = new QSpinBox(centralWidget);
        QuantizationNumber->setObjectName(QStringLiteral("QuantizationNumber"));
        QuantizationNumber->setGeometry(QRect(880, 300, 121, 51));
        NegativeButton = new QPushButton(centralWidget);
        NegativeButton->setObjectName(QStringLiteral("NegativeButton"));
        NegativeButton->setGeometry(QRect(880, 140, 261, 25));
        RotateButton = new QPushButton(centralWidget);
        RotateButton->setObjectName(QStringLiteral("RotateButton"));
        RotateButton->setGeometry(QRect(880, 170, 261, 25));
        Histogram = new QGraphicsView(centralWidget);
        Histogram->setObjectName(QStringLiteral("Histogram"));
        Histogram->setGeometry(QRect(460, 360, 256, 256));
        HistogramButton = new QPushButton(centralWidget);
        HistogramButton->setObjectName(QStringLiteral("HistogramButton"));
        HistogramButton->setGeometry(QRect(880, 200, 261, 25));
        ContrastButton = new QPushButton(centralWidget);
        ContrastButton->setObjectName(QStringLiteral("ContrastButton"));
        ContrastButton->setGeometry(QRect(1010, 260, 131, 25));
        BrightnessButton = new QPushButton(centralWidget);
        BrightnessButton->setObjectName(QStringLiteral("BrightnessButton"));
        BrightnessButton->setGeometry(QRect(1010, 300, 131, 25));
        ContrastValue = new QDoubleSpinBox(centralWidget);
        ContrastValue->setObjectName(QStringLiteral("ContrastValue"));
        ContrastValue->setGeometry(QRect(880, 260, 121, 31));
        EqualizeHistogramButton = new QPushButton(centralWidget);
        EqualizeHistogramButton->setObjectName(QStringLiteral("EqualizeHistogramButton"));
        EqualizeHistogramButton->setGeometry(QRect(880, 110, 261, 25));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1195, 22));
        menuTassinari_s_Phototool = new QMenu(menuBar);
        menuTassinari_s_Phototool->setObjectName(QStringLiteral("menuTassinari_s_Phototool"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuTassinari_s_Phototool->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        FlipHorizontallyButton->setText(QApplication::translate("MainWindow", "Flip Horizontally", Q_NULLPTR));
        GreyScaleButton->setText(QApplication::translate("MainWindow", "Shades of grey", Q_NULLPTR));
        OpenImageButton->setText(QApplication::translate("MainWindow", "Open Image", Q_NULLPTR));
        FlipVerticallyButton->setText(QApplication::translate("MainWindow", "Flip Vertically", Q_NULLPTR));
        SaveImageButton->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        QuantizationButton->setText(QApplication::translate("MainWindow", "Quantization", Q_NULLPTR));
        NegativeButton->setText(QApplication::translate("MainWindow", "Negative", Q_NULLPTR));
        RotateButton->setText(QApplication::translate("MainWindow", "Rotate", Q_NULLPTR));
        HistogramButton->setText(QApplication::translate("MainWindow", "Calculate Histogram", Q_NULLPTR));
        ContrastButton->setText(QApplication::translate("MainWindow", "Contrast", Q_NULLPTR));
        BrightnessButton->setText(QApplication::translate("MainWindow", "Brightness", Q_NULLPTR));
        EqualizeHistogramButton->setText(QApplication::translate("MainWindow", "Equalize Histogram", Q_NULLPTR));
        menuTassinari_s_Phototool->setTitle(QApplication::translate("MainWindow", "Tassinari's Phototool", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
