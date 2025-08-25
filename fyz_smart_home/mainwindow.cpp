#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QtMqtt/qmqttclient.h>
#include <qdebug.h>
#include <QDateTime>
#include <QTimer>

#define MQTT_AUTO_TOPIC "fyz/123/#"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化模块
    controlModule = new ControlModule(this);
    mqttModule = new MqttModule(this);
    mqttConnected = false;
    serialMgr = new serialmanager(this);

    // 左侧边栏相关定义
    ui->left_widget->setObjectName("left_widget");
    ui->statusBtn->setObjectName("statusBtn");
    ui->mqttBtn->setObjectName("mqttBtn");
    ui->uartBtn->setObjectName("uartBtn");

    /*mqtt连接服务器界面相关定义*/
    ui->statuswidget->setObjectName("connectWidget");
    ui->pubwidget->setObjectName("PubWidget");
    ui->subwidget->setObjectName("SubWidget");
    ui->loginwidget->setObjectName("loginWidget");
    ui->messagewidget->setObjectName("messageWidget");
    ui->controlwidget->setObjectName("controlWidget");

    ui->mqttStatusLabel->setObjectName("mqttStatusLabel");
    ui->label_broker->setObjectName("LabelBroker");
    ui->label_port->setObjectName("LabelPort");
    ui->label_client_id->setObjectName("LabelClientID");
    ui->label_username->setObjectName("LabelUserName");
    ui->label_password->setObjectName("LabelPassword");
    ui->label_Pub->setObjectName("LabelPub");
    ui->label_Sub->setObjectName("LabelSub");

    ui->connectMqttButton->setObjectName("connectMqtt");
    ui->clearPubBtn->setObjectName("clearPubBtn");
    ui->clearSubBtn->setObjectName("clearSubBtn");
    ui->clearMsgBtn->setObjectName("clearMsgBtn");
    ui->connectMqttButton->setObjectName("connectMqtt");

    /*mqtt控制界面相关定义*/
    ui->ledBtn->setObjectName("ledBtn");
    ui->fanBtn->setObjectName("fanBtn");
    ui->alarmBtn->setObjectName("alarmBtn");

    ui->led_label->setObjectName("led_label");
    ui->alram_label->setObjectName("alram_label");
    ui->fan_label->setObjectName("fan_label");
    ui->led_label->setText("LED OFF");
    ui->alram_label->setText("ALARM OFF");
    ui->fan_label->setText("ALARM OFF");


    /*UART界面相关定义*/
    ui->uartwidget->setObjectName("UartWidget");
    ui->comboBox_uartnum->setObjectName("comboBox_uartnum");
    ui->comboBox_databit->setObjectName("comboBox_databit");
    ui->comboBox_stopbit->setObjectName("comboBox_stopbit");
    ui->comboBox_checkbit->setObjectName("comboBox_checkbit");
    ui->comboBox_baudrate->setObjectName("comboBox_baudrate");
    ui->comboBox_sendmode->setObjectName("comboBox_sendmode");
    ui->comboBox_revmode->setObjectName("comboBox_revmode");
    ui->openSerialBtn->setObjectName("openSerialBtn");

    ui->comboBox_baudrate->setCurrentIndex(1);
    ui->comboBox_stopbit->setCurrentIndex(0);
    ui->comboBox_checkbit->setCurrentIndex(0);
    ui->comboBox_databit->setCurrentIndex(0);

    /*设置setCheckable是否有效*/
    ui->statusBtn->setCheckable(true);
    ui->mqttBtn->setCheckable(true);
    ui->uartBtn->setCheckable(true);

    ui->ledBtn->setCheckable(true);
    ui->fanBtn->setCheckable(true);
    ui->alarmBtn->setCheckable(true);

    // 设置statusBtn为默认选中状态
    ui->statusBtn->setChecked(false);
    ui->mqttBtn->setChecked(false);
    ui->uartBtn->setChecked(false);
    ui->ledBtn->setChecked(false);
    ui->fanBtn->setChecked(false);
    ui->alarmBtn->setChecked(false);

    // 设置固定窗口大小
    this->setFixedSize(1280, 800);
    // 设置窗口标题
    this->setWindowTitle("MQTT 智能家居控制中心");
    this->setWindowIcon(QIcon(":/src/window.png"));
    ui->connectMqttButton->setCheckable(true);  // 设置按钮可切换状态
    ui->connectMqttButton->setText("连接服务器");

    /*MQTT相关*/
    ui->connectlabel->setPixmap(QPixmap(":/src/switch_off.png"));
    ui->mqttStatusLabel->setText("服务器未连接!");

    // UI 与 ControlModule 信号槽连接
    connect(controlModule, &ControlModule::ledStateChanged, this, [=](bool on){
        ui->led_label->setText(on ? "LED ON" : "LED OFF");
        ui->ledBtn->setChecked(on);
        ui->ledBtn->setIcon(QIcon(on ? ":/src/light_on.png" : ":/src/light_off.png"));
        /*具体硬件部分待实现*/
    });
    connect(controlModule, &ControlModule::fanStateChanged, this, [=](bool on){
        ui->fan_label->setText(on ? "FAN ON" : "FAN OFF");
        ui->fanBtn->setChecked(on);
        ui->fanBtn->setIcon(QIcon(on ? ":/src/fan_on.png" : ":/src/fan_off.png"));
        /*具体硬件部分待实现*/
    });
    connect(controlModule, &ControlModule::alarmStateChanged, this, [=](bool on){
        ui->alram_label->setText(on ? "ALARM ON" : "ALARM OFF");
        ui->alarmBtn->setChecked(on);
        ui->alarmBtn->setIcon(QIcon(on ? ":/src/alarm_on.png" : ":/src/alarm_off.png"));
        /*具体硬件部分待实现*/
    });

    // UI 与 MqttModule 信号槽连接
    connect(mqttModule, &MqttModule::messageReceived, this, &MainWindow::updateMQTTMessage);
    connect(mqttModule, &MqttModule::stateChanged, this, &MainWindow::updateMQTTState);
    connect(mqttModule, &MqttModule::signal_publishMessage, this, &MainWindow::updateMQTTPubMessage);


    // UI 与 uart 信号槽连接
    connect(serialMgr, &serialmanager::dataReceived, this, [this](const QByteArray &data){
        ui->textEditMessage->append("收到数据: " + QString(data));
    });

    connect(serialMgr, &serialmanager::errorOccurred, this, [this](const QString &err){
        ui->textEditMessage->append("串口错误: " + err);
    });

    connect(serialMgr, &serialmanager::serialOpened, this, [this](){
        ui->openSerialBtn->setText("关闭串口");
    });

    connect(serialMgr, &serialmanager::serialClosed, this, [this](){
        ui->openSerialBtn->setText("打开串口");
    });

    // 连接扫描信号到 comboBox
    connect(serialMgr, &serialmanager::portListUpdated, this, [this](const QStringList &ports){
//        qDebug() << "Lambda triggered! Ports:" << ports;
        ui->comboBox_uartnum->clear();
        ui->comboBox_uartnum->addItems(ports);
    });


    // MQTT 连接
    mqttModule->connectToBroker("broker.emqx.io", 1883);
    QString str = QString("服务器开始连接! Broker: %1, Port: %2").arg("broker.emqx.io").arg(1883);
    ui->textEditMessage->append(str);
    mqttModule->startTestPublish(5000); // 5 秒测试发送
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 重写 paintEvent，让背景图片全屏铺满
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 背景深色
    painter.fillRect(this->rect(), QColor("#1e1e2f"));

    // 绘制图片，拉伸到整个窗口
    QPixmap pix(":/src/window_beijing_resized.png");
    if (!pix.isNull()) {
        painter.drawPixmap(this->rect(), pix);
    }

    QMainWindow::paintEvent(event);
}

void MainWindow::on_ledBtn_clicked(bool checked)
{
    controlModule->setLed(checked);
}

void MainWindow::on_fanBtn_clicked(bool checked)
{
    controlModule->setFan(checked);
}

void MainWindow::on_alarmBtn_clicked(bool checked)
{
    controlModule->setAlarm(checked);
}


void MainWindow::updateMQTTMessage(const QString &topic, const QByteArray &msg)
{
    QString content = QString("[%1] Topic: %2 Message: %3")
                        .arg(QDateTime::currentDateTime().toString())
                        .arg(topic)
                        .arg(QString(msg));
    ui->textEditMessage->append(content);
    ui->TextEdit_Sub->append(content);
    qDebug() << content;
}


void MainWindow::updateMQTTPubMessage(QString topic, QString payload)
{
    ui->TextEdit_Pub->append(topic);
    ui->TextEdit_Pub->append(payload);
}

void MainWindow::updateMQTTSubMessage(QString topic, QString payload)
{
    ui->TextEdit_Pub->append(topic);
    ui->TextEdit_Pub->append(payload);
}


void MainWindow::updateMQTTState(QMqttClient::ClientState state)
{
    if(state == QMqttClient::Connected){
        ui->textEditMessage->append("服务器已连接!");
        ui->mqttStatusLabel->setText("服务器已连接!");
        ui->connectlabel->setPixmap(QPixmap(":/src/switch_on.png"));
    } else {
        ui->textEditMessage->append("服务器断开!");
        ui->mqttStatusLabel->setText("服务器未连接!");
        ui->connectlabel->setPixmap(QPixmap(":/src/switch_off.png"));
    }
}


void MainWindow::on_connectMqttButton_clicked(bool checked)
{
    (void)checked;  // 防止 unused parameter 警告
    if (!mqttConnected) {
        // 获取界面输入的服务器信息
        QString host = ui->lineEdit_Broker->text();
        quint16 port = ui->lineEdit_Port->text().toUShort();

        mqttModule->connectToBroker(host, port);
//        mqttModule->connectToBroker(host, port, ui->lineEdit_Broker, ui->lineEdit_Port, ui->textEditMessage);
        mqttConnected = true;
        ui->connectMqttButton->setText("断开连接");
    } else {
        mqttModule->disconnected();
        mqttConnected = false;
        ui->connectMqttButton->setText("连接服务器");
    }
}

void MainWindow::on_openSerialBtn_clicked(bool checked)
{
    if (checked) {
        qDebug() << "on_openSerialBtn_clicked:" << endl;
        serialMgr->openSerial(ui->comboBox_uartnum->currentText(),
                              ui->comboBox_baudrate->currentText().toInt());
    } else {
        qDebug() << "on_openSerialBtn_unpressed:" << endl;
        serialMgr->closeSerial();
    }
}

void MainWindow::on_clearPubBtn_clicked()
{
    ui->TextEdit_Pub->clear();
}

void MainWindow::on_clearSubBtn_clicked()
{
    ui->TextEdit_Sub->clear();
}

void MainWindow::on_clearMsgBtn_clicked()
{
    ui->textEditMessage->clear();
}
