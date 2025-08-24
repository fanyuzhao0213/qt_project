/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *left_widget;
    QVBoxLayout *verticalLayout;
    QPushButton *statusBtn;
    QPushButton *mqttBtn;
    QPushButton *uartBtn;
    QWidget *cloudWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *statuswidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *mqttStatusLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *connectlabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *connectMqttButton;
    QSpacerItem *horizontalSpacer_3;
    QWidget *messagewidget;
    QHBoxLayout *horizontalLayout;
    QWidget *loginwidget;
    QGridLayout *gridLayout;
    QLabel *label_broker;
    QLineEdit *lineEdit_Broker;
    QLabel *label_port;
    QLineEdit *lineEdit_Port;
    QLabel *label_client_id;
    QLineEdit *lineEdit_Client_id;
    QLabel *label_username;
    QLineEdit *lineEdit_Client_id_2;
    QLabel *label_password;
    QLineEdit *lineEdit_Client_id_3;
    QTextEdit *textEditMessage;
    QWidget *pubwidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_Pub;
    QTextEdit *TextEdit_Pub;
    QWidget *subwidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_Sub;
    QTextEdit *TextEdit_Sub;
    QWidget *controlwidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *smartwidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QPushButton *ledBtn;
    QLabel *led_label;
    QVBoxLayout *verticalLayout_6;
    QPushButton *alarmBtn;
    QLabel *alram_label;
    QVBoxLayout *verticalLayout_7;
    QPushButton *fanBtn;
    QLabel *fan_label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        left_widget = new QWidget(centralwidget);
        left_widget->setObjectName(QString::fromUtf8("left_widget"));
        left_widget->setGeometry(QRect(0, 0, 100, 800));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(left_widget->sizePolicy().hasHeightForWidth());
        left_widget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(left_widget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 5, 1);
        statusBtn = new QPushButton(left_widget);
        statusBtn->setObjectName(QString::fromUtf8("statusBtn"));

        verticalLayout->addWidget(statusBtn);

        mqttBtn = new QPushButton(left_widget);
        mqttBtn->setObjectName(QString::fromUtf8("mqttBtn"));

        verticalLayout->addWidget(mqttBtn);

        uartBtn = new QPushButton(left_widget);
        uartBtn->setObjectName(QString::fromUtf8("uartBtn"));

        verticalLayout->addWidget(uartBtn);

        cloudWidget = new QWidget(centralwidget);
        cloudWidget->setObjectName(QString::fromUtf8("cloudWidget"));
        cloudWidget->setGeometry(QRect(100, 0, 500, 800));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cloudWidget->sizePolicy().hasHeightForWidth());
        cloudWidget->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(cloudWidget);
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 1, 1, 1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        statuswidget = new QWidget(cloudWidget);
        statuswidget->setObjectName(QString::fromUtf8("statuswidget"));
        horizontalLayout_2 = new QHBoxLayout(statuswidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mqttStatusLabel = new QLabel(statuswidget);
        mqttStatusLabel->setObjectName(QString::fromUtf8("mqttStatusLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mqttStatusLabel->sizePolicy().hasHeightForWidth());
        mqttStatusLabel->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(mqttStatusLabel);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        connectlabel = new QLabel(statuswidget);
        connectlabel->setObjectName(QString::fromUtf8("connectlabel"));

        horizontalLayout_2->addWidget(connectlabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        connectMqttButton = new QPushButton(statuswidget);
        connectMqttButton->setObjectName(QString::fromUtf8("connectMqttButton"));

        horizontalLayout_2->addWidget(connectMqttButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_4->addWidget(statuswidget);

        messagewidget = new QWidget(cloudWidget);
        messagewidget->setObjectName(QString::fromUtf8("messagewidget"));
        horizontalLayout = new QHBoxLayout(messagewidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loginwidget = new QWidget(messagewidget);
        loginwidget->setObjectName(QString::fromUtf8("loginwidget"));
        gridLayout = new QGridLayout(loginwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_broker = new QLabel(loginwidget);
        label_broker->setObjectName(QString::fromUtf8("label_broker"));

        gridLayout->addWidget(label_broker, 0, 0, 1, 1);

        lineEdit_Broker = new QLineEdit(loginwidget);
        lineEdit_Broker->setObjectName(QString::fromUtf8("lineEdit_Broker"));

        gridLayout->addWidget(lineEdit_Broker, 0, 1, 1, 1);

        label_port = new QLabel(loginwidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));

        gridLayout->addWidget(label_port, 1, 0, 1, 1);

        lineEdit_Port = new QLineEdit(loginwidget);
        lineEdit_Port->setObjectName(QString::fromUtf8("lineEdit_Port"));

        gridLayout->addWidget(lineEdit_Port, 1, 1, 1, 1);

        label_client_id = new QLabel(loginwidget);
        label_client_id->setObjectName(QString::fromUtf8("label_client_id"));

        gridLayout->addWidget(label_client_id, 2, 0, 1, 1);

        lineEdit_Client_id = new QLineEdit(loginwidget);
        lineEdit_Client_id->setObjectName(QString::fromUtf8("lineEdit_Client_id"));

        gridLayout->addWidget(lineEdit_Client_id, 2, 1, 1, 1);

        label_username = new QLabel(loginwidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));

        gridLayout->addWidget(label_username, 3, 0, 1, 1);

        lineEdit_Client_id_2 = new QLineEdit(loginwidget);
        lineEdit_Client_id_2->setObjectName(QString::fromUtf8("lineEdit_Client_id_2"));

        gridLayout->addWidget(lineEdit_Client_id_2, 3, 1, 1, 1);

        label_password = new QLabel(loginwidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        gridLayout->addWidget(label_password, 4, 0, 1, 1);

        lineEdit_Client_id_3 = new QLineEdit(loginwidget);
        lineEdit_Client_id_3->setObjectName(QString::fromUtf8("lineEdit_Client_id_3"));

        gridLayout->addWidget(lineEdit_Client_id_3, 4, 1, 1, 1);


        horizontalLayout->addWidget(loginwidget);

        textEditMessage = new QTextEdit(messagewidget);
        textEditMessage->setObjectName(QString::fromUtf8("textEditMessage"));

        horizontalLayout->addWidget(textEditMessage);


        verticalLayout_4->addWidget(messagewidget);

        pubwidget = new QWidget(cloudWidget);
        pubwidget->setObjectName(QString::fromUtf8("pubwidget"));
        verticalLayout_2 = new QVBoxLayout(pubwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        label_Pub = new QLabel(pubwidget);
        label_Pub->setObjectName(QString::fromUtf8("label_Pub"));

        verticalLayout_2->addWidget(label_Pub);

        TextEdit_Pub = new QTextEdit(pubwidget);
        TextEdit_Pub->setObjectName(QString::fromUtf8("TextEdit_Pub"));

        verticalLayout_2->addWidget(TextEdit_Pub);


        verticalLayout_4->addWidget(pubwidget);

        subwidget = new QWidget(cloudWidget);
        subwidget->setObjectName(QString::fromUtf8("subwidget"));
        verticalLayout_3 = new QVBoxLayout(subwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        label_Sub = new QLabel(subwidget);
        label_Sub->setObjectName(QString::fromUtf8("label_Sub"));

        verticalLayout_3->addWidget(label_Sub);

        TextEdit_Sub = new QTextEdit(subwidget);
        TextEdit_Sub->setObjectName(QString::fromUtf8("TextEdit_Sub"));

        verticalLayout_3->addWidget(TextEdit_Sub);


        verticalLayout_4->addWidget(subwidget);


        horizontalLayout_3->addLayout(verticalLayout_4);

        controlwidget = new QWidget(centralwidget);
        controlwidget->setObjectName(QString::fromUtf8("controlwidget"));
        controlwidget->setGeometry(QRect(600, 0, 680, 800));
        sizePolicy2.setHeightForWidth(controlwidget->sizePolicy().hasHeightForWidth());
        controlwidget->setSizePolicy(sizePolicy2);
        horizontalLayout_4 = new QHBoxLayout(controlwidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        smartwidget = new QWidget(controlwidget);
        smartwidget->setObjectName(QString::fromUtf8("smartwidget"));
        sizePolicy2.setHeightForWidth(smartwidget->sizePolicy().hasHeightForWidth());
        smartwidget->setSizePolicy(sizePolicy2);
        horizontalLayout_5 = new QHBoxLayout(smartwidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(20);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 5, 5, 5);
        ledBtn = new QPushButton(smartwidget);
        ledBtn->setObjectName(QString::fromUtf8("ledBtn"));
        sizePolicy3.setHeightForWidth(ledBtn->sizePolicy().hasHeightForWidth());
        ledBtn->setSizePolicy(sizePolicy3);

        verticalLayout_5->addWidget(ledBtn);

        led_label = new QLabel(smartwidget);
        led_label->setObjectName(QString::fromUtf8("led_label"));
        led_label->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_5->addWidget(led_label);


        horizontalLayout_5->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(20);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(5, 5, 5, 5);
        alarmBtn = new QPushButton(smartwidget);
        alarmBtn->setObjectName(QString::fromUtf8("alarmBtn"));

        verticalLayout_6->addWidget(alarmBtn);

        alram_label = new QLabel(smartwidget);
        alram_label->setObjectName(QString::fromUtf8("alram_label"));

        verticalLayout_6->addWidget(alram_label);


        horizontalLayout_5->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(20);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(5, 5, 5, 5);
        fanBtn = new QPushButton(smartwidget);
        fanBtn->setObjectName(QString::fromUtf8("fanBtn"));

        verticalLayout_7->addWidget(fanBtn);

        fan_label = new QLabel(smartwidget);
        fan_label->setObjectName(QString::fromUtf8("fan_label"));

        verticalLayout_7->addWidget(fan_label);


        horizontalLayout_5->addLayout(verticalLayout_7);


        horizontalLayout_4->addWidget(smartwidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        statusBtn->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
        mqttBtn->setText(QCoreApplication::translate("MainWindow", "\344\272\221\347\253\257", nullptr));
        uartBtn->setText(QCoreApplication::translate("MainWindow", "\351\200\232\344\277\241", nullptr));
        mqttStatusLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\346\234\252\350\277\236\346\216\245", nullptr));
        connectlabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        connectMqttButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_broker->setText(QCoreApplication::translate("MainWindow", "Broker", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        label_client_id->setText(QCoreApplication::translate("MainWindow", "ClientID", nullptr));
        label_username->setText(QCoreApplication::translate("MainWindow", "UserName", nullptr));
        label_password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_Pub->setText(QCoreApplication::translate("MainWindow", "PublishMessage", nullptr));
        label_Sub->setText(QCoreApplication::translate("MainWindow", "SublishMessage", nullptr));
        ledBtn->setText(QString());
        led_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        alarmBtn->setText(QString());
        alram_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        fanBtn->setText(QString());
        fan_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
