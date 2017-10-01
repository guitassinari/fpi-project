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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *OpenImageButton;
    QPushButton *FlipButton;
    QGraphicsView *OriginalImage;
    QGraphicsView *EditedImage;
    QLineEdit *lineEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuTassinari_s_Phototool;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(633, 448);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 320, 89, 25));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 290, 89, 25));
        OpenImageButton = new QPushButton(centralWidget);
        OpenImageButton->setObjectName(QStringLiteral("OpenImageButton"));
        OpenImageButton->setGeometry(QRect(500, 10, 89, 25));
        FlipButton = new QPushButton(centralWidget);
        FlipButton->setObjectName(QStringLiteral("FlipButton"));
        FlipButton->setGeometry(QRect(30, 290, 89, 25));
        OriginalImage = new QGraphicsView(centralWidget);
        OriginalImage->setObjectName(QStringLiteral("OriginalImage"));
        OriginalImage->setGeometry(QRect(30, 60, 256, 192));
        EditedImage = new QGraphicsView(centralWidget);
        EditedImage->setObjectName(QStringLiteral("EditedImage"));
        EditedImage->setGeometry(QRect(340, 60, 256, 192));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 10, 461, 25));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 633, 22));
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
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        OpenImageButton->setText(QApplication::translate("MainWindow", "Open Image", Q_NULLPTR));
        FlipButton->setText(QApplication::translate("MainWindow", "Flip Image", Q_NULLPTR));
        menuTassinari_s_Phototool->setTitle(QApplication::translate("MainWindow", "Tassinari's Phototool", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
