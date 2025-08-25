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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
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
    QVBoxLayout *verticalLayout_13;
    QWidget *statuswidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *mqttStatusLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *connectlabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *connectMqttButton;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *clearMsgBtn;
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
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_Pub;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *clearPubBtn;
    QSpacerItem *horizontalSpacer_11;
    QTextEdit *TextEdit_Pub;
    QWidget *subwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_Sub;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *clearSubBtn;
    QSpacerItem *horizontalSpacer_14;
    QTextEdit *TextEdit_Sub;
    QWidget *controlwidget;
    QVBoxLayout *verticalLayout_12;
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
    QWidget *uartwidget;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_16;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QComboBox *comboBox_uartnum;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QComboBox *comboBox_baudrate;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QComboBox *comboBox_databit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QComboBox *comboBox_stopbit;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QComboBox *comboBox_checkbit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QPushButton *openSerialBtn;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_12;
    QComboBox *comboBox_sendmode;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QComboBox *comboBox_revmode;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_13;
    QTextBrowser *textBrowser_rev;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_14;
    QTextBrowser *textBrowser_send;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *serial_sendBtn;
    QPushButton *serial_clearsendBtn;
    QPushButton *serial_clearrevBtn;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_9;
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
        verticalLayout_13 = new QVBoxLayout(cloudWidget);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
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

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_15);

        clearMsgBtn = new QPushButton(statuswidget);
        clearMsgBtn->setObjectName(QString::fromUtf8("clearMsgBtn"));

        horizontalLayout_2->addWidget(clearMsgBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_13->addWidget(statuswidget);

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
        label_broker->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_broker, 0, 0, 1, 1);

        lineEdit_Broker = new QLineEdit(loginwidget);
        lineEdit_Broker->setObjectName(QString::fromUtf8("lineEdit_Broker"));

        gridLayout->addWidget(lineEdit_Broker, 0, 1, 1, 1);

        label_port = new QLabel(loginwidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        label_port->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_port, 1, 0, 1, 1);

        lineEdit_Port = new QLineEdit(loginwidget);
        lineEdit_Port->setObjectName(QString::fromUtf8("lineEdit_Port"));

        gridLayout->addWidget(lineEdit_Port, 1, 1, 1, 1);

        label_client_id = new QLabel(loginwidget);
        label_client_id->setObjectName(QString::fromUtf8("label_client_id"));
        label_client_id->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_client_id, 2, 0, 1, 1);

        lineEdit_Client_id = new QLineEdit(loginwidget);
        lineEdit_Client_id->setObjectName(QString::fromUtf8("lineEdit_Client_id"));

        gridLayout->addWidget(lineEdit_Client_id, 2, 1, 1, 1);

        label_username = new QLabel(loginwidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_username, 3, 0, 1, 1);

        lineEdit_Client_id_2 = new QLineEdit(loginwidget);
        lineEdit_Client_id_2->setObjectName(QString::fromUtf8("lineEdit_Client_id_2"));

        gridLayout->addWidget(lineEdit_Client_id_2, 3, 1, 1, 1);

        label_password = new QLabel(loginwidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_password, 4, 0, 1, 1);

        lineEdit_Client_id_3 = new QLineEdit(loginwidget);
        lineEdit_Client_id_3->setObjectName(QString::fromUtf8("lineEdit_Client_id_3"));

        gridLayout->addWidget(lineEdit_Client_id_3, 4, 1, 1, 1);


        horizontalLayout->addWidget(loginwidget);

        textEditMessage = new QTextEdit(messagewidget);
        textEditMessage->setObjectName(QString::fromUtf8("textEditMessage"));

        horizontalLayout->addWidget(textEditMessage);


        verticalLayout_13->addWidget(messagewidget);

        pubwidget = new QWidget(cloudWidget);
        pubwidget->setObjectName(QString::fromUtf8("pubwidget"));
        verticalLayout_4 = new QVBoxLayout(pubwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);

        label_Pub = new QLabel(pubwidget);
        label_Pub->setObjectName(QString::fromUtf8("label_Pub"));

        horizontalLayout_3->addWidget(label_Pub);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        clearPubBtn = new QPushButton(pubwidget);
        clearPubBtn->setObjectName(QString::fromUtf8("clearPubBtn"));

        horizontalLayout_3->addWidget(clearPubBtn);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);


        verticalLayout_2->addLayout(horizontalLayout_3);

        TextEdit_Pub = new QTextEdit(pubwidget);
        TextEdit_Pub->setObjectName(QString::fromUtf8("TextEdit_Pub"));

        verticalLayout_2->addWidget(TextEdit_Pub);


        verticalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_13->addWidget(pubwidget);

        subwidget = new QWidget(cloudWidget);
        subwidget->setObjectName(QString::fromUtf8("subwidget"));
        verticalLayout_3 = new QVBoxLayout(subwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_12);

        label_Sub = new QLabel(subwidget);
        label_Sub->setObjectName(QString::fromUtf8("label_Sub"));

        horizontalLayout_18->addWidget(label_Sub);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_13);

        clearSubBtn = new QPushButton(subwidget);
        clearSubBtn->setObjectName(QString::fromUtf8("clearSubBtn"));

        horizontalLayout_18->addWidget(clearSubBtn);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_14);


        verticalLayout_3->addLayout(horizontalLayout_18);

        TextEdit_Sub = new QTextEdit(subwidget);
        TextEdit_Sub->setObjectName(QString::fromUtf8("TextEdit_Sub"));

        verticalLayout_3->addWidget(TextEdit_Sub);


        verticalLayout_13->addWidget(subwidget);

        controlwidget = new QWidget(centralwidget);
        controlwidget->setObjectName(QString::fromUtf8("controlwidget"));
        controlwidget->setGeometry(QRect(600, 0, 680, 800));
        sizePolicy2.setHeightForWidth(controlwidget->sizePolicy().hasHeightForWidth());
        controlwidget->setSizePolicy(sizePolicy2);
        verticalLayout_12 = new QVBoxLayout(controlwidget);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
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


        verticalLayout_12->addWidget(smartwidget);

        uartwidget = new QWidget(controlwidget);
        uartwidget->setObjectName(QString::fromUtf8("uartwidget"));
        verticalLayout_11 = new QVBoxLayout(uartwidget);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        widget_3 = new QWidget(uartwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_8 = new QVBoxLayout(widget_3);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox = new QGroupBox(widget_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label);

        comboBox_uartnum = new QComboBox(groupBox);
        comboBox_uartnum->setObjectName(QString::fromUtf8("comboBox_uartnum"));

        horizontalLayout_4->addWidget(comboBox_uartnum);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_2);

        comboBox_baudrate = new QComboBox(groupBox);
        comboBox_baudrate->addItem(QString());
        comboBox_baudrate->addItem(QString());
        comboBox_baudrate->addItem(QString());
        comboBox_baudrate->addItem(QString());
        comboBox_baudrate->setObjectName(QString::fromUtf8("comboBox_baudrate"));

        horizontalLayout_6->addWidget(comboBox_baudrate);


        gridLayout_2->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_3);

        comboBox_databit = new QComboBox(groupBox);
        comboBox_databit->addItem(QString());
        comboBox_databit->addItem(QString());
        comboBox_databit->addItem(QString());
        comboBox_databit->addItem(QString());
        comboBox_databit->setObjectName(QString::fromUtf8("comboBox_databit"));

        horizontalLayout_7->addWidget(comboBox_databit);


        gridLayout_2->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_4);

        comboBox_stopbit = new QComboBox(groupBox);
        comboBox_stopbit->addItem(QString());
        comboBox_stopbit->addItem(QString());
        comboBox_stopbit->addItem(QString());
        comboBox_stopbit->setObjectName(QString::fromUtf8("comboBox_stopbit"));

        horizontalLayout_8->addWidget(comboBox_stopbit);


        gridLayout_2->addLayout(horizontalLayout_8, 3, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_5);

        comboBox_checkbit = new QComboBox(groupBox);
        comboBox_checkbit->addItem(QString());
        comboBox_checkbit->addItem(QString());
        comboBox_checkbit->addItem(QString());
        comboBox_checkbit->setObjectName(QString::fromUtf8("comboBox_checkbit"));

        horizontalLayout_9->addWidget(comboBox_checkbit);


        gridLayout_2->addLayout(horizontalLayout_9, 4, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label_6);

        openSerialBtn = new QPushButton(groupBox);
        openSerialBtn->setObjectName(QString::fromUtf8("openSerialBtn"));

        horizontalLayout_10->addWidget(openSerialBtn);


        gridLayout_2->addLayout(horizontalLayout_10, 5, 0, 1, 1);


        verticalLayout_8->addWidget(groupBox);

        groupBox_3 = new QGroupBox(widget_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_12 = new QHBoxLayout(groupBox_3);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(5, 5, 5, 5);
        comboBox_sendmode = new QComboBox(groupBox_3);
        comboBox_sendmode->addItem(QString());
        comboBox_sendmode->addItem(QString());
        comboBox_sendmode->setObjectName(QString::fromUtf8("comboBox_sendmode"));

        horizontalLayout_12->addWidget(comboBox_sendmode);


        verticalLayout_8->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(widget_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_11 = new QHBoxLayout(groupBox_2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(5, 5, 5, 5);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_7);

        comboBox_revmode = new QComboBox(groupBox_2);
        comboBox_revmode->addItem(QString());
        comboBox_revmode->addItem(QString());
        comboBox_revmode->setObjectName(QString::fromUtf8("comboBox_revmode"));

        horizontalLayout_11->addWidget(comboBox_revmode);


        verticalLayout_8->addWidget(groupBox_2);


        horizontalLayout_16->addWidget(widget_3);

        widget_4 = new QWidget(uartwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_9 = new QVBoxLayout(widget_4);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(widget_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_4);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(5, 5, 5, 5);
        textBrowser_rev = new QTextBrowser(groupBox_4);
        textBrowser_rev->setObjectName(QString::fromUtf8("textBrowser_rev"));

        horizontalLayout_13->addWidget(textBrowser_rev);


        verticalLayout_9->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(widget_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_14 = new QHBoxLayout(groupBox_5);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(5, 5, 5, 5);
        textBrowser_send = new QTextBrowser(groupBox_5);
        textBrowser_send->setObjectName(QString::fromUtf8("textBrowser_send"));

        horizontalLayout_14->addWidget(textBrowser_send);


        verticalLayout_9->addWidget(groupBox_5);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_15 = new QHBoxLayout(widget_2);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_4);

        serial_sendBtn = new QPushButton(widget_2);
        serial_sendBtn->setObjectName(QString::fromUtf8("serial_sendBtn"));

        horizontalLayout_15->addWidget(serial_sendBtn);

        serial_clearsendBtn = new QPushButton(widget_2);
        serial_clearsendBtn->setObjectName(QString::fromUtf8("serial_clearsendBtn"));

        horizontalLayout_15->addWidget(serial_clearsendBtn);

        serial_clearrevBtn = new QPushButton(widget_2);
        serial_clearrevBtn->setObjectName(QString::fromUtf8("serial_clearrevBtn"));

        horizontalLayout_15->addWidget(serial_clearrevBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_5);


        verticalLayout_9->addWidget(widget_2);


        horizontalLayout_16->addWidget(widget_4);


        verticalLayout_10->addLayout(horizontalLayout_16);

        widget_5 = new QWidget(uartwidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_17 = new QHBoxLayout(widget_5);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_8);

        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_17->addWidget(pushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_6);

        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_17->addWidget(pushButton_2);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_7);


        verticalLayout_10->addWidget(widget_5);


        verticalLayout_11->addLayout(verticalLayout_10);

        label_9 = new QLabel(uartwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_9);


        verticalLayout_12->addWidget(uartwidget);

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
        clearMsgBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\345\216\206\345\217\262log", nullptr));
        label_broker->setText(QCoreApplication::translate("MainWindow", "Broker", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        label_client_id->setText(QCoreApplication::translate("MainWindow", "ClientID", nullptr));
        label_username->setText(QCoreApplication::translate("MainWindow", "UserName", nullptr));
        label_password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_Pub->setText(QCoreApplication::translate("MainWindow", "PublishMessage", nullptr));
        clearPubBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244pub\344\277\241\346\201\257", nullptr));
        label_Sub->setText(QCoreApplication::translate("MainWindow", "SublishMessage", nullptr));
        clearSubBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244sub\344\277\241\346\201\257", nullptr));
        ledBtn->setText(QString());
        led_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        alarmBtn->setText(QString());
        alram_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        fanBtn->setText(QString());
        fan_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_baudrate->setItemText(0, QCoreApplication::translate("MainWindow", "921600", nullptr));
        comboBox_baudrate->setItemText(1, QCoreApplication::translate("MainWindow", "115200", nullptr));
        comboBox_baudrate->setItemText(2, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboBox_baudrate->setItemText(3, QCoreApplication::translate("MainWindow", "4800", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        comboBox_databit->setItemText(0, QCoreApplication::translate("MainWindow", "8", nullptr));
        comboBox_databit->setItemText(1, QCoreApplication::translate("MainWindow", "7", nullptr));
        comboBox_databit->setItemText(2, QCoreApplication::translate("MainWindow", "6", nullptr));
        comboBox_databit->setItemText(3, QCoreApplication::translate("MainWindow", "5", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        comboBox_stopbit->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBox_stopbit->setItemText(1, QCoreApplication::translate("MainWindow", "1.5", nullptr));
        comboBox_stopbit->setItemText(2, QCoreApplication::translate("MainWindow", "2", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        comboBox_checkbit->setItemText(0, QCoreApplication::translate("MainWindow", "NONE", nullptr));
        comboBox_checkbit->setItemText(1, QCoreApplication::translate("MainWindow", "EVEN", nullptr));
        comboBox_checkbit->setItemText(2, QCoreApplication::translate("MainWindow", "ODD", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        openSerialBtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\214\272\351\205\215\347\275\256", nullptr));
        comboBox_sendmode->setItemText(0, QCoreApplication::translate("MainWindow", "HEX\346\250\241\345\274\217", nullptr));
        comboBox_sendmode->setItemText(1, QCoreApplication::translate("MainWindow", "\346\226\207\346\234\254\346\250\241\345\274\217", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\345\214\272\351\205\215\347\275\256", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\346\250\241\345\274\217", nullptr));
        comboBox_revmode->setItemText(0, QCoreApplication::translate("MainWindow", "HEX\346\250\241\345\274\217", nullptr));
        comboBox_revmode->setItemText(1, QCoreApplication::translate("MainWindow", "\346\226\207\346\234\254\346\250\241\345\274\217", nullptr));

        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\345\214\272", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\214\272", nullptr));
        serial_sendBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        serial_clearsendBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\217\221\351\200\201\345\214\272", nullptr));
        serial_clearrevBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
