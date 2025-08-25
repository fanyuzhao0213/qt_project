#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QtMqtt/qmqttclient.h>
#include <qdebug.h>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>

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
    sendTimer = new QTimer(this);


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

    ui->serial_sendBtn->setObjectName("serial_sendBtn");
    ui->serial_clearrevBtn->setObjectName("serial_clearrevBtn");
    ui->serial_clearsendBtn->setObjectName("serial_clearsendBtn");
    ui->checkBox_uarttimesend->setObjectName("checkBox_uarttimesend");
    ui->lineEdit_uarttime->setObjectName("lineEdit_uarttime");
    ui->textBrowser_rev->setObjectName("textBrowser_rev");

    // 设置默认选中项
    ui->comboBox_uartnum->setCurrentIndex(0);
    ui->comboBox_baudrate->setCurrentIndex(1);
    ui->comboBox_databit->setCurrentIndex(3); // 默认8位
    ui->comboBox_stopbit->setCurrentIndex(0);
    ui->comboBox_checkbit->setCurrentIndex(0);

    // ================= 初始状态 =================
    // 串口未打开，ComboBox可修改
    ui->comboBox_uartnum->setEnabled(true);
    ui->comboBox_baudrate->setEnabled(true);
    ui->comboBox_databit->setEnabled(true);
    ui->comboBox_stopbit->setEnabled(true);
    ui->comboBox_checkbit->setEnabled(true);


    /*设置setCheckable是否有效*/
    ui->statusBtn->setCheckable(true);
    ui->mqttBtn->setCheckable(true);
    ui->uartBtn->setCheckable(true);

    ui->ledBtn->setCheckable(true);
    ui->fanBtn->setCheckable(true);
    ui->alarmBtn->setCheckable(true);
    ui->openSerialBtn->setCheckable(true);
    /*以下3个按钮不需要checked行为*/
    ui->serial_sendBtn->setCheckable(false);
    ui->serial_clearrevBtn->setCheckable(false);
    ui->serial_clearsendBtn->setCheckable(false);

    // 设置statusBtn为默认选中状态
    ui->statusBtn->setChecked(false);
    ui->mqttBtn->setChecked(false);
    ui->uartBtn->setChecked(false);
    ui->ledBtn->setChecked(false);
    ui->fanBtn->setChecked(false);
    ui->alarmBtn->setChecked(false);


    ui->openSerialBtn->setEnabled(true);       // 打开按钮默认可用
    ui->serial_sendBtn->setEnabled(false);    // 发送按钮默认禁用
    ui->serial_clearrevBtn->setEnabled(false);// 清除接收按钮默认禁用
    ui->serial_clearsendBtn->setEnabled(false);// 清除发送按钮默认禁用
    ui->checkBox_uarttimesend->setEnabled(false);
    ui->lineEdit_uarttime->setEnabled(false);

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


    // 构造函数中 uart 定时更新串口列表
    connect(ui->comboBox_uartnum, &QComboBox::showPopup, this, [this]() {
        qDebug() << "ComboBoxUart 被点击，开始扫描串口";
        serialMgr->scanPorts(); // 调用 serialmanager 扫描
    });


    // 将 serialmanager 的 dataReceived 信号连接到 lambda 函数
    // 当串口接收到数据时，会触发这个槽函数
    connect(serialMgr, &serialmanager::dataReceived, this, [this](const QByteArray &data){

        // 获取 UI 上用于选择接收模式的 ComboBox（文本模式或 HEX 模式）
        QComboBox *modeCombo = ui->comboBox_revmode;

        // 判断用户是否选择了 HEX 模式，如果选择了就显示十六进制，否则显示文本
        bool isHex = (modeCombo && modeCombo->currentText() == "HEX模式");

        QString displayStr; // 用于存放最终要显示的字符串

        if (isHex) {
            // 如果是 HEX 模式，将接收到的 QByteArray 转成 HEX 字符串，每个字节用空格分隔，并转换成大写
            displayStr = data.toHex(' ').toUpper();
        } else {
            // 如果是文本模式，将 QByteArray 按 UTF-8 编码转换为 QString
            displayStr = QString::fromUtf8(data);
        }

        // 将显示内容插入到 QTextBrowser 末尾（累积显示，避免覆盖之前内容）
        ui->textBrowser_rev->moveCursor(QTextCursor::End);      // 将光标移动到文本末尾
        ui->textBrowser_rev->insertPlainText(displayStr);       // 插入内容，不自动换行
        ui->textBrowser_rev->moveCursor(QTextCursor::End);      // 插入后再次移动光标到末尾，保证滚动到最新内容
    });


    connect(serialMgr, &serialmanager::errorOccurred, this, [this](const QString &err){
        QMessageBox::critical(this, "串口错误", err);
    });

    connect(serialMgr, &serialmanager::serialOpened, this, [this](){
        ui->serial_sendBtn->setEnabled(true);    // 发送按钮使能
        ui->serial_clearrevBtn->setEnabled(true);// 清除接收按钮使能
        ui->serial_clearsendBtn->setEnabled(true);// 清除发送按钮使能
        ui->checkBox_uarttimesend->setEnabled(true);
        ui->lineEdit_uarttime->setEnabled(true);

        // 串口打开后
        ui->comboBox_uartnum->setEnabled(false);    // 禁用串口选择
        ui->comboBox_baudrate->setEnabled(false);   // 禁用波特率选择
        ui->comboBox_databit->setEnabled(false);    // 数据位
        ui->comboBox_stopbit->setEnabled(false);    // 停止位
        ui->comboBox_checkbit->setEnabled(false);   // 校验位
        ui->openSerialBtn->setText("关闭串口");
    });

    connect(serialMgr, &serialmanager::serialClosed, this, [this](){
        ui->serial_sendBtn->setEnabled(false);    // 发送按钮默认禁用
        ui->serial_clearrevBtn->setEnabled(false);// 清除接收按钮默认禁用
        ui->serial_clearsendBtn->setEnabled(false);// 清除发送按钮默认禁用
        ui->comboBox_uartnum->setEnabled(true);
        ui->comboBox_baudrate->setEnabled(true);
        ui->comboBox_databit->setEnabled(true);
        ui->comboBox_stopbit->setEnabled(true);
        ui->comboBox_checkbit->setEnabled(true);
        ui->checkBox_uarttimesend->setEnabled(false);
        ui->lineEdit_uarttime->setEnabled(false);

        ui->openSerialBtn->setText("打开串口");
    });

    /*定时器控制发送，定时器由自动发送checkbox来控制*/
    connect(sendTimer, &QTimer::timeout, this, &MainWindow::on_serial_sendBtn_clicked);
    // 定时发送复选框控制
    connect(ui->checkBox_uarttimesend, &QCheckBox::toggled, this, [=](bool checked){
        if (!serialMgr->isOpen()) {
            QMessageBox::warning(this, "错误", "串口未打开，无法启动定时发送");
            ui->checkBox_uarttimesend->setChecked(false);
            return;
        }

        if (checked) {
            bool ok;
            int interval = ui->lineEdit_uarttime->text().toInt(&ok); // 获取定时间隔(ms)
            if (!ok || interval <= 0) {
                QMessageBox::warning(this, "错误", "请输入有效的定时间隔（毫秒）");
                ui->checkBox_uarttimesend->setChecked(false);
                return;
            }
            sendTimer->start(interval);   // 启动定时器
            ui->serial_sendBtn->setEnabled(false); // 禁用手动发送
            ui->lineEdit_uarttime->setEnabled(false);
            qDebug() << "定时发送已启用，间隔：" << interval << "ms";
        } else {
            sendTimer->stop();
            ui->lineEdit_uarttime->setEnabled(true);
            ui->serial_sendBtn->setEnabled(true);  // 恢复手动发送
            qDebug() << "定时发送已停止";
        }
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

void MainWindow::on_serial_sendBtn_clicked()
{
    if (!serialMgr->isOpen()) {
        qDebug() << "串口未打开，无法发送数据";
        return;
    }

    bool isHex = (ui->comboBox_sendmode->currentText() == "HEX模式");
    qDebug() << "发送模式:" << (isHex ? "HEX模式" : "文本模式");

    QByteArray data;
    QString text = ui->textEdit_serialsend->toPlainText();
    qDebug() << "原始输入:" << text;

    if (isHex) {
        // 去掉所有空格并转换为大写
        QString hexStr = text;
        hexStr.remove(' ');
        hexStr = hexStr.toUpper();

        // 如果长度是奇数，自动补0在前面
        if (hexStr.length() % 2 != 0) {
            hexStr.prepend('0');
        }

        // 每两个字符解析成一个字节
        for (int i = 0; i < hexStr.length(); i += 2) {
            bool ok;
            char byte = hexStr.mid(i, 2).toUInt(&ok, 16);
            if (ok) {
                data.append(byte);
            } else {
                qDebug() << "无效的 HEX 字符:" << hexStr.mid(i, 2);
            }
        }

        qDebug() << "解析后的 HEX 数据:" << data.toHex(' ').toUpper();
    } else {
        data = text.toUtf8();
        qDebug() << "解析后的文本数据:" << data;
    }

    serialMgr->sendData(data);
    qDebug() << "发送完成, 长度:" << data.size();
}


void MainWindow::on_serial_clearrevBtn_clicked()
{
    ui->textBrowser_rev->clear();
}


// 接收 serialmanager 发送过来的数据，并根据模式在 TextEdit 显示
void MainWindow::onSerialDataToSend(const QByteArray &data, bool isHex)
{
    if (isHex) {
        // HEX 模式：把 QByteArray 转成带空格的大写十六进制字符串显示
        ui->textBrowser_rev->append(data.toHex(' ').toUpper());
    } else {
        // 文本模式：直接按 UTF-8 字符串显示
        ui->textBrowser_rev->append(QString::fromUtf8(data));
    }
}


void MainWindow::on_serial_clearsendBtn_clicked()
{
    ui->textEdit_serialsend->clear();
}
