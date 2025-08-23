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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_start_addr;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton_choose_file;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_clear;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_cpuid;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_erase_flash;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_burn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(585, 444);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label);

        lineEdit_start_addr = new QLineEdit(Widget);
        lineEdit_start_addr->setObjectName(QString::fromUtf8("lineEdit_start_addr"));

        horizontalLayout_3->addWidget(lineEdit_start_addr);

        horizontalLayout_3->setStretch(0, 5);
        horizontalLayout_3->setStretch(1, 4);

        horizontalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton_choose_file = new QPushButton(Widget);
        pushButton_choose_file->setObjectName(QString::fromUtf8("pushButton_choose_file"));

        horizontalLayout->addWidget(pushButton_choose_file);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_clear = new QPushButton(Widget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        horizontalLayout_2->addWidget(pushButton_clear);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_cpuid = new QPushButton(Widget);
        pushButton_cpuid->setObjectName(QString::fromUtf8("pushButton_cpuid"));

        horizontalLayout_2->addWidget(pushButton_cpuid);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_erase_flash = new QPushButton(Widget);
        pushButton_erase_flash->setObjectName(QString::fromUtf8("pushButton_erase_flash"));

        horizontalLayout_2->addWidget(pushButton_erase_flash);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton_burn = new QPushButton(Widget);
        pushButton_burn->setObjectName(QString::fromUtf8("pushButton_burn"));

        horizontalLayout_2->addWidget(pushButton_burn);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QApplication::translate("Widget", "\347\203\247\345\275\225\350\265\267\345\247\213\345\234\260\345\235\200\357\274\210Hex\357\274\211", nullptr));
        lineEdit_start_addr->setText(QApplication::translate("Widget", "0x8000000", nullptr));
        pushButton_choose_file->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\345\233\272\344\273\266", nullptr));
        pushButton_clear->setText(QApplication::translate("Widget", "\346\270\205\347\251\272\346\230\276\347\244\272", nullptr));
        pushButton_cpuid->setText(QApplication::translate("Widget", "\350\216\267\345\217\226CPUID", nullptr));
        pushButton_erase_flash->setText(QApplication::translate("Widget", "\346\223\246\351\231\244Flash", nullptr));
        pushButton_burn->setText(QApplication::translate("Widget", "\344\270\200\351\224\256\347\203\247\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
