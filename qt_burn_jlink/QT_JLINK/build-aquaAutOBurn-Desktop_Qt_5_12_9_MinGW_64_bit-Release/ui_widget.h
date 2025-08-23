/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QPushButton *selectFileBtn;
    QLineEdit *lineEdit_startaddr;
    QPushButton *pushButton;
    QPushButton *StartBurnBtn;
    QProgressBar *progressBar;
    QPushButton *BLEBurnBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 80, 281, 151));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 270, 113, 20));
        selectFileBtn = new QPushButton(Widget);
        selectFileBtn->setObjectName(QString::fromUtf8("selectFileBtn"));
        selectFileBtn->setGeometry(QRect(160, 270, 75, 23));
        lineEdit_startaddr = new QLineEdit(Widget);
        lineEdit_startaddr->setObjectName(QString::fromUtf8("lineEdit_startaddr"));
        lineEdit_startaddr->setGeometry(QRect(20, 300, 113, 20));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 300, 91, 21));
        StartBurnBtn = new QPushButton(Widget);
        StartBurnBtn->setObjectName(QString::fromUtf8("StartBurnBtn"));
        StartBurnBtn->setGeometry(QRect(250, 270, 75, 23));
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 360, 118, 23));
        progressBar->setValue(24);
        BLEBurnBtn = new QPushButton(Widget);
        BLEBurnBtn->setObjectName(QString::fromUtf8("BLEBurnBtn"));
        BLEBurnBtn->setGeometry(QRect(270, 300, 75, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        selectFileBtn->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\345\233\272\344\273\266", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\347\203\247\345\275\225\350\265\267\345\247\213\345\234\260\345\235\200", nullptr));
        StartBurnBtn->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\347\203\247\345\275\225", nullptr));
        BLEBurnBtn->setText(QApplication::translate("Widget", "BLE\347\203\247\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
