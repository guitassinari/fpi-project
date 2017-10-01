/********************************************************************************
** Form generated from reading UI file 'imageopener.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEOPENER_H
#define UI_IMAGEOPENER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_ImageOpener
{
public:
    QTreeView *treeView;

    void setupUi(QDialog *ImageOpener)
    {
        if (ImageOpener->objectName().isEmpty())
            ImageOpener->setObjectName(QStringLiteral("ImageOpener"));
        ImageOpener->resize(400, 300);
        treeView = new QTreeView(ImageOpener);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(0, 0, 401, 301));

        retranslateUi(ImageOpener);

        QMetaObject::connectSlotsByName(ImageOpener);
    } // setupUi

    void retranslateUi(QDialog *ImageOpener)
    {
        ImageOpener->setWindowTitle(QApplication::translate("ImageOpener", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageOpener: public Ui_ImageOpener {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEOPENER_H
