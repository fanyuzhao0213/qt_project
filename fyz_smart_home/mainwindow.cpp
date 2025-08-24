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

    // 在 MainWindow 构造函数里初始化
    mqttTestTimer = new QTimer(this);
    testCounter = 0;
    startMQTTSendTest();

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

    ui->label_broker->setObjectName("LabelBroker");
    ui->label_port->setObjectName("LabelPort");
    ui->label_client_id->setObjectName("LabelClientID");
    ui->label_username->setObjectName("LabelUserName");
    ui->label_password->setObjectName("LabelPassword");
    ui->label_Pub->setObjectName("LabelPub");
    ui->label_Sub->setObjectName("LabelSub");
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


    /*设置setCheckable是否有效*/
    ui->statusBtn->setCheckable(true);
    ui->mqttBtn->setCheckable(true);
    ui->uartBtn->setCheckable(true);

    ui->ledBtn->setCheckable(true);
    ui->fanBtn->setCheckable(true);
    ui->alarmBtn->setCheckable(true);

//    ui->left_widget->setStyleSheet(
//        "background-color: #2c2f4a;"
//    );

//    ui->statusBtn->setStyleSheet(
//        "QPushButton { background-color: #3a3f5c; color: #fff; border-radius: 12px; min-height: 80px; }"
//        "QPushButton:checked { background-color: #7c83c0; }"
//    );
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

    /*MQTT相关*/

    ui->connectlabel->setPixmap(QPixmap(":/src/switch_off.png"));
    ui->mqttStatusLabel->setText("服务器未连接!");


    m_client = new QMqttClient(this);           // 创建一个 MQTT 客户端对象，父对象为 MainWindow
    m_client->setHostname("broker.emqx.io");        // 设置 MQTT 服务器的主机地址（这里是broker.emqx.io）
    ui->lineEdit_Broker->setText("broker.emqx.io");
    QString brokerAddr = ui->lineEdit_Broker->text();       // 从 lineEdit 取出文本
    QString log = QString("服务器地址: %1").arg(brokerAddr);    // 拼接成日志字符串
    ui->textEditMessage->append(log);    // 追加到 textEdit
    m_client->setPort(1883);    // 设置 MQTT 服务器的端口号（默认 1883）
    ui->lineEdit_Port->setText("1883");
    ui->lineEdit_Broker->setText("broker.emqx.io");
    brokerAddr = ui->lineEdit_Broker->text();    // 从 lineEdit 取出文本
    log = QString("服务器端口: %1").arg(brokerAddr);    // 拼接成日志字符串
    ui->textEditMessage->append(log);    // 追加到 textEdit


    // 尝试连接到 MQTT 服务器
    m_client->connectToHost();
    ui->textEditMessage->append("start mqtt 服务器连接!");


    // 当客户端成功连接到 MQTT Broker 时，触发 brokerConnected 槽函数
    connect(m_client, &QMqttClient::connected, this, &MainWindow::brokerConnected);
    // 当客户端状态发生变化时，触发 updateLogStateChange 槽函数
    // 例如：正在连接、已连接、断开等状态
    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    // 当客户端断开连接时，触发 brokerDisconnected 槽函数
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);

    // 构造函数中连接一次
    connect(m_client, &QMqttClient::messageReceived, this, &MainWindow::receiveMess);

    // 当客户端收到 Broker 的 PING 响应时执行 Lambda 函数
    // 用于检测连接是否保持活跃（心跳机制）
    connect(m_client, &QMqttClient::pingResponseReceived, this, []() {
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(" PingResponse")
        + QLatin1Char('\n');
    qDebug() << content;
});

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

void MainWindow::MyMQTTSubscribe(QString str)
{
    auto subscription = m_client->subscribe(str, 0);
    if (!subscription) {
        qDebug() << "Could not subscribe. Is there a valid connection?";
        ui->textEditMessage->append("Could not subscribe. Is there a valid connection?");
        return;
    }
}

void MainWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
    ui->textEditMessage->append(content);
    qDebug() << content;

    if (m_client->state() == QMqttClient::Connected) {
        ui->mqttStatusLabel->setText("服务器已连接!");
        ui->connectlabel->setPixmap(QPixmap(":/src/switch_on.png"));
    } else {
        ui->mqttStatusLabel->setText("服务器未连接!");
        ui->connectlabel->setPixmap(QPixmap(":/src/switch_off.png"));
    }

}

void MainWindow::brokerConnected()
{
    qDebug() << "Connected!";
    ui->textEditMessage->append("Connected!");
    if(m_client->state() == QMqttClient::Connected){
        m_client->subscribe(QString(MQTT_AUTO_TOPIC), 0);
    }
}

void MainWindow::brokerDisconnected()
{
    qDebug() << "server Disconnected!";
    ui->textEditMessage->append("server Disconnected!");

    // 尝试连接到 MQTT 服务器
    // 延迟重连，避免递归
    QTimer::singleShot(1000, this, [this](){
        if(m_client && m_client->state() == QMqttClient::Disconnected)
            m_client->connectToHost();
    });
}

void MainWindow::receiveMess(const QByteArray &message, const QMqttTopicName &topic)
{
   QString content;
   content = QDateTime::currentDateTime().toString() + QLatin1Char('\n');
   content += QLatin1String(" Received Topic: ") + topic.name() + QLatin1Char('\n');
   content += QLatin1String(" Message: ") + message + QLatin1Char('\n');
   ui->textEditMessage->append(content);
   ui->TextEdit_Sub->append(content);
   qDebug() << content;
}

void MainWindow::MyMQTTSendMessage(const QString topic, const QString message)
{
    if (m_client->publish(topic, message.toUtf8()) == -1){
        qDebug() << "Could not publish message";
        ui->textEditMessage->append("Could not publish message");
    }
}


void MainWindow::on_ledBtn_clicked(bool checked)
{
    ui->ledBtn->setIcon(QIcon(checked ? ":/src/light_on.png" : ":/src/light_off.png"));
    ui->led_label->setText(checked ? "LED ON" : "LED OFF");
}


void MainWindow::on_alarmBtn_clicked(bool checked)
{

    ui->alarmBtn->setIcon(QIcon(checked ? ":/src/alarm_on.png" : ":/src/alarm_off.png"));
    ui->alram_label->setText(checked ? "ALARM ON" : "ALARM OFF");
}

void MainWindow::on_fanBtn_clicked(bool checked)
{
    ui->fanBtn->setIcon(QIcon(checked ? ":/src/fan_on.png" : ":/src/fan_off.png"));
    ui->fan_label->setText(checked ? "FAN ON" : "FAN OFF");
}


// 定时发送槽函数
void MainWindow::sendTestMessage()
{
    if (!m_client || m_client->state() != QMqttClient::Connected) {
        qDebug() << "MQTT not connected!";
        return;
    }

    QString topic = "fyz/123/test";
    QString message = QString("Test message #%1").arg(testCounter++);

    if (m_client->publish(topic, message.toUtf8()) == -1) {
        qDebug() << "Could not publish message";
        ui->textEditMessage->append("Could not publish message");
    } else {
        qDebug() << "Published:" << message;
        ui->textEditMessage->append("Published: " + message);
    }
}

// 启动定时器函数
void MainWindow::startMQTTSendTest()
{
    connect(mqttTestTimer, &QTimer::timeout, this, &MainWindow::sendTestMessage);
    mqttTestTimer->start(5000); // 每 5 秒触发一次
}

