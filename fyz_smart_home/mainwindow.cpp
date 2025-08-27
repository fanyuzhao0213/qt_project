#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QtMqtt/qmqttclient.h>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>

#define PROGRAM_DEV_ID          "DEV_2025-01"

#define MQTT_AUTO_TOPIC         "fyz/123/#"
#define MQTT_BORKER_URL         "aqua.mqtt.istarix.com"
#define MQTT_PORT               "20018"
#define MQTT_CLIENT_ID          "washer"
#define MQTT_USER_NAME          "aqua_mu"
#define MQTT_PASSWORD           "fyz12345"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mqttConnected(false)
{
    ui->setupUi(this);

    // 初始化模块
    controlModule = new ControlModule(this);
    mqttModule    = new MqttModule(this);
    serialMgr     = new serialmanager(this);
    sendTimer     = new QTimer(this);

    // ====== 封装函数调用，保持主构造简洁 ======
    initUI();
    initButtons();
    initSerialUI();
    initMqttUI();

    connectControlModule();
    connectMqttModule();
    connectSerialModule();

    // 启动 MQTT 测试连接
    // mqttModule->connectToBroker("broker.emqx.io", 1883, "hhh_123");
    // ui->textEditMessage->append("服务器开始连接! Broker: broker.emqx.io, Port: 1883");
    mqttModule->startTestPublish(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ==============================
 * 初始化 UI 布局和界面元素
 * ============================== */
void MainWindow::initUI()
{
    // 窗口属性
    setFixedSize(1280, 800);
    setWindowTitle("MQTT 智能家居控制中心");
    setWindowIcon(QIcon(":/src/window.png"));
}

/* ==============================
 * 初始化按钮（Checkable / 状态）
 * ============================== */
void MainWindow::initButtons()
{
    // 设置 checkable 属性
    ui->statusBtn->setCheckable(true);
    ui->mqttBtn->setCheckable(true);
    ui->uartBtn->setCheckable(true);

    ui->ledBtn->setCheckable(true);
    ui->fanBtn->setCheckable(true);
    ui->alarmBtn->setCheckable(true);
    ui->openSerialBtn->setCheckable(true);

    // 默认未选中
    ui->statusBtn->setChecked(false);
    ui->mqttBtn->setChecked(false);
    ui->uartBtn->setChecked(false);
    ui->ledBtn->setChecked(false);
    ui->fanBtn->setChecked(false);
    ui->alarmBtn->setChecked(false);

    // 串口相关按钮默认禁用
    ui->openSerialBtn->setEnabled(true);
    ui->serial_sendBtn->setEnabled(false);
    ui->serial_clearrevBtn->setEnabled(false);
    ui->serial_clearsendBtn->setEnabled(false);
    ui->checkBox_uarttimesend->setEnabled(false);
    ui->lineEdit_uarttime->setEnabled(false);

    // MQTT 连接按钮
    ui->connectMqttButton->setCheckable(true);
    ui->connectMqttButton->setText("连接服务器");
}

/* ==============================
 * 初始化串口相关 UI
 * ============================== */
void MainWindow::initSerialUI()
{
    // 设置默认串口参数
    ui->comboBox_uartnum->setCurrentIndex(0);
    ui->comboBox_baudrate->setCurrentIndex(1);
    ui->comboBox_databit->setCurrentIndex(3); // 默认8位
    ui->comboBox_stopbit->setCurrentIndex(0);
    ui->comboBox_checkbit->setCurrentIndex(0);
}

/* ==============================
 * 初始化 MQTT 相关 UI
 * ============================== */
void MainWindow::initMqttUI()
{
    // 状态提示
    ui->connectlabel->setPixmap(QPixmap(":/src/switch_off.png"));
    ui->mqttStatusLabel->setText("服务器未连接!");

    ui->lineEdit_UsrName->setText(MQTT_USER_NAME);
    ui->lineEdit_PassWrd->setText(MQTT_PASSWORD);
    ui->lineEdit_Broker->setText(MQTT_BORKER_URL);
    ui->lineEdit_Port->setText(MQTT_PORT);
    QString clientId = QString("%1_%2").arg(MQTT_CLIENT_ID).arg(PROGRAM_DEV_ID);
    ui->lineEdit_Client_id->setText(clientId);

    // 控制界面默认标签
    ui->led_label->setText("LED OFF");
    ui->alram_label->setText("ALARM OFF");
    ui->fan_label->setText("FAN OFF");
}

/* ==============================
 * 信号槽绑定 - 控制模块
 * ============================== */
void MainWindow::connectControlModule()
{

    connect(controlModule, &ControlModule::ledStateChanged, this, [=](bool on){
        ui->led_label->setText(on ? "LED ON" : "LED OFF");
        ui->ledBtn->setChecked(on);
        ui->ledBtn->setIcon(QIcon(on ? ":/src/light_on.png" : ":/src/light_off.png"));
    });
    connect(controlModule, &ControlModule::fanStateChanged, this, [=](bool on){
        ui->fan_label->setText(on ? "FAN ON" : "FAN OFF");
        ui->fanBtn->setChecked(on);
        ui->fanBtn->setIcon(QIcon(on ? ":/src/fan_on.png" : ":/src/fan_off.png"));
    });
    connect(controlModule, &ControlModule::alarmStateChanged, this, [=](bool on){
        ui->alram_label->setText(on ? "ALARM ON" : "ALARM OFF");
        ui->alarmBtn->setChecked(on);
        ui->alarmBtn->setIcon(QIcon(on ? ":/src/alarm_on.png" : ":/src/alarm_off.png"));
    });
}

/* ==============================
 * 信号槽绑定 - MQTT 模块
 * ============================== */
void MainWindow::connectMqttModule()
{
    connect(mqttModule, &MqttModule::messageReceived, this, &MainWindow::updateMQTTMessage);
    connect(mqttModule, &MqttModule::stateChanged, this, &MainWindow::updateMQTTState);
    connect(mqttModule, &MqttModule::signal_publishMessage, this, &MainWindow::updateMQTTPubMessage);
}

/* ==============================
 * 信号槽绑定 - 串口模块
 * ============================== */
void MainWindow::connectSerialModule()
{
    // 点击串口下拉框时刷新列表
    connect(ui->comboBox_uartnum, &QComboBox::showPopup, this, [this]() {
        serialMgr->scanPorts();
    });

    // 接收数据
    connect(serialMgr, &serialmanager::dataReceived, this, [this](const QByteArray &data){
        bool isHex = (ui->comboBox_revmode->currentText() == "HEX模式");
        QString displayStr = isHex ? data.toHex(' ').toUpper() : QString::fromUtf8(data);
        ui->textBrowser_rev->moveCursor(QTextCursor::End);
        ui->textBrowser_rev->insertPlainText(displayStr);
        ui->textBrowser_rev->moveCursor(QTextCursor::End);
    });

    // 错误提示
    connect(serialMgr, &serialmanager::errorOccurred, this, [this](const QString &err){
        QMessageBox::critical(this, "串口错误", err);
    });

    // 串口打开/关闭
    connect(serialMgr, &serialmanager::serialOpened, this, &MainWindow::onSerialOpened);
    connect(serialMgr, &serialmanager::serialClosed, this, &MainWindow::onSerialClosed);

    // 定时发送
    connect(sendTimer, &QTimer::timeout, this, &MainWindow::on_serial_sendBtn_clicked);
    connect(ui->checkBox_uarttimesend, &QCheckBox::toggled, this, &MainWindow::onAutoSendToggled);

    // 更新串口下拉框
    connect(serialMgr, &serialmanager::portListUpdated, this, [this](const QStringList &ports){
        ui->comboBox_uartnum->clear();
        ui->comboBox_uartnum->addItems(ports);
    });
}



// ======================== 重绘事件 ========================
/**
 * @brief paintEvent
 * 重写窗口绘制事件：设置背景色 + 背景图全屏铺满
 */
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 背景深色填充
    painter.fillRect(this->rect(), QColor("#1e1e2f"));

    // 绘制背景图片（拉伸至窗口大小）
    QPixmap pix(":/src/window_beijing_resized.png");
    if (!pix.isNull()) {
        painter.drawPixmap(this->rect(), pix);
    }

    QMainWindow::paintEvent(event);
}

// ======================== 控制模块相关 ========================
/**
 * @brief LED 控制按钮点击
 * @param checked true=开启, false=关闭
 */
void MainWindow::on_ledBtn_clicked(bool checked)
{
    controlModule->setLed(checked);
}

/**
 * @brief 风扇控制按钮点击
 */
void MainWindow::on_fanBtn_clicked(bool checked)
{
    controlModule->setFan(checked);
}

/**
 * @brief 报警器控制按钮点击
 */
void MainWindow::on_alarmBtn_clicked(bool checked)
{
    controlModule->setAlarm(checked);
}

// ======================== MQTT 模块相关 ========================
/**
 * @brief 接收到 MQTT 消息时更新 UI
 * @param topic 主题
 * @param msg 消息内容
 */
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

/**
 * @brief 更新发布消息显示区
 */
void MainWindow::updateMQTTPubMessage(QString topic, QString payload)
{
    ui->TextEdit_Pub->append(topic);
    ui->TextEdit_Pub->append(payload);
}

/**
 * @brief 更新订阅消息显示区
 */
void MainWindow::updateMQTTSubMessage(QString topic, QString payload)
{
    ui->TextEdit_Sub->append(topic);
    ui->TextEdit_Sub->append(payload);
}

/**
 * @brief 更新 MQTT 连接状态
 */
void MainWindow::updateMQTTState(QMqttClient::ClientState state)
{
    if (state == QMqttClient::Connected) {
        ui->textEditMessage->append("服务器已连接!");
        ui->statusbar->showMessage("服务器已连接!", 2000);
        ui->mqttStatusLabel->setText("服务器已连接!");
        ui->connectlabel->setPixmap(QPixmap(":/src/switch_on.png"));
    } else {
        ui->textEditMessage->append("服务器断开!");
        ui->mqttStatusLabel->setText("服务器未连接!");
        ui->statusbar->showMessage("服务器未连接!", 2000);
        ui->connectlabel->setPixmap(QPixmap(":/src/switch_off.png"));
    }
}

/**
 * @brief 连接/断开 MQTT 按钮点击
 */
void MainWindow::on_connectMqttButton_clicked(bool checked)
{
    Q_UNUSED(checked)  // 防止未使用参数警告

    if (!mqttConnected) {
        // 获取界面输入的服务器信息
        QString host     = ui->lineEdit_Broker->text().trimmed();
        QString portStr  = ui->lineEdit_Port->text().trimmed();
        QString clientId = ui->lineEdit_Client_id->text().trimmed();
        QString username = ui->lineEdit_UsrName->text().trimmed();
        QString password = ui->lineEdit_PassWrd->text(); // 密码允许空格

        // 检查输入是否为空
        if (host.isEmpty() || portStr.isEmpty() || clientId.isEmpty() ||
            username.isEmpty() || password.isEmpty())
        {
            QMessageBox::warning(this, "MQTT 连接错误",
                                 "请确保 Broker、Port、ClientID、Username 和 Password 都已填写！");
            return;
        }

        bool ok = false;
        quint16 port = portStr.toUShort(&ok);
        if (!ok || port == 0) {
            QMessageBox::warning(this, "MQTT 连接错误", "Port 必须是有效的数字！");
            return;
        }

        // 调用 MQTT 模块连接
        mqttModule->connectToBroker(host, port, clientId, username, password);
        // 调用 MQTT 模块连接前，输出连接信息
        QString msg = QString("服务器开始连接!\nBroker: %1\nPort: %2\nClientID: %3\nUsername: %4")
                            .arg(host)
                            .arg(port)
                            .arg(clientId)
                            .arg(username);
        ui->textEditMessage->append(msg);
        ui->statusbar->showMessage(msg, 2000);
        mqttConnected = true;
        ui->connectMqttButton->setText("断开连接");
    } else {
        // 断开
        mqttModule->disconnectFromBroker();   // 调用新接口
        mqttConnected = false;
        ui->connectMqttButton->setText("连接服务器");
        ui->textEditMessage->append("已断开 MQTT 连接");
        ui->statusbar->showMessage("已断开 MQTT 连接", 2000);
    }
}

// ======================== 串口模块相关 ========================
/**
 * @brief 打开/关闭串口按钮点击
 */
void MainWindow::on_openSerialBtn_clicked(bool checked)
{
    if (checked) {
        qDebug() << "尝试打开串口";
        serialMgr->openSerial(
            ui->comboBox_uartnum->currentText(),
            ui->comboBox_baudrate->currentText().toInt()
        );
    } else {
        qDebug() << "关闭串口";
        serialMgr->closeSerial();
    }
}

/**
 * @brief 清空发布区
 */
void MainWindow::on_clearPubBtn_clicked()
{
    ui->TextEdit_Pub->clear();
}

/**
 * @brief 清空订阅区
 */
void MainWindow::on_clearSubBtn_clicked()
{
    ui->TextEdit_Sub->clear();
}

/**
 * @brief 清空消息区
 */
void MainWindow::on_clearMsgBtn_clicked()
{
    ui->textEditMessage->clear();
}

/**
 * @brief 串口发送按钮点击
 * 根据选择的模式（文本 / HEX）解析输入并发送
 */
void MainWindow::on_serial_sendBtn_clicked()
{
    if (!serialMgr->isOpen()) {
        qDebug() << "串口未打开，无法发送数据";
        return;
    }

    bool isHex = (ui->comboBox_sendmode->currentText() == "HEX模式");
    QByteArray data;
    QString text = ui->textEdit_serialsend->toPlainText();

    if (isHex) {
        // 去掉空格并转换为大写
        QString hexStr = text;
        hexStr.remove(' ');
        hexStr = hexStr.toUpper();

        // 如果长度是奇数，前面补0
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

        qDebug() << "HEX 模式发送:" << data.toHex(' ').toUpper();
    } else {
        data = text.toUtf8();
        qDebug() << "文本模式发送:" << data;
    }

    serialMgr->sendData(data);
    qDebug() << "发送完成, 数据长度:" << data.size();
}

/**
 * @brief 清空串口接收区
 */
void MainWindow::on_serial_clearrevBtn_clicked()
{
    ui->textBrowser_rev->clear();
}

/**
 * @brief 接收 serialmanager 发来的数据并显示
 * @param data 串口数据
 * @param isHex 是否使用 HEX 模式
 */
void MainWindow::onSerialDataToSend(const QByteArray &data, bool isHex)
{
    if (isHex) {
        ui->textBrowser_rev->append(data.toHex(' ').toUpper());
    } else {
        ui->textBrowser_rev->append(QString::fromUtf8(data));
    }
}

/**
 * @brief 清空串口发送区
 */
void MainWindow::on_serial_clearsendBtn_clicked()
{
    ui->textEdit_serialsend->clear();
}

// 串口打开成功回调
void MainWindow::onSerialOpened()
{
    // 这里可以更新UI，比如启用串口发送按钮
    ui->serial_sendBtn->setEnabled(true);
    ui->serial_clearrevBtn->setEnabled(true);
    ui->serial_clearsendBtn->setEnabled(true);
    ui->checkBox_uarttimesend->setEnabled(true);
    ui->lineEdit_uarttime->setEnabled(true);

    ui->textBrowser_rev->append("串口已打开");
    ui->statusbar->showMessage("串口已打开", 3000);
}

// 串口关闭回调
void MainWindow::onSerialClosed()
{
    // 禁用串口相关按钮
    ui->serial_sendBtn->setEnabled(false);
    ui->serial_clearrevBtn->setEnabled(false);
    ui->serial_clearsendBtn->setEnabled(false);
    ui->checkBox_uarttimesend->setEnabled(false);
    ui->lineEdit_uarttime->setEnabled(false);

    ui->textBrowser_rev->append("串口已关闭");
    ui->statusbar->showMessage("串口已关闭", 3000);
}

// 定时发送复选框切换
void MainWindow::onAutoSendToggled(bool enabled)
{
    if (!sendTimer) return;

    if (enabled) {
        QString intervalStr = ui->lineEdit_uarttime->text().trimmed();

        // 判断是否为空
        if (intervalStr.isEmpty()) {
            QMessageBox::warning(this, "定时发送错误", "请输入有效的时间间隔（毫秒）！");
            ui->checkBox_uarttimesend->setChecked(false); // 取消勾选
            return;
        }

        bool ok = false;
        int interval = intervalStr.toInt(&ok);
        if (!ok || interval <= 0) {
            QMessageBox::warning(this, "定时发送错误", "请输入正确的正整数时间间隔（毫秒）！");
            ui->checkBox_uarttimesend->setChecked(false); // 取消勾选
            return;
        }

        // 启动定时器
        sendTimer->start(interval);
    } else {
        // 停止定时器
        sendTimer->stop();
    }
}




void MainWindow::on_subTopicBtn_clicked()
{
    // 获取输入的 Topic
    QString topic = ui->lineEdit_subtopic->text().trimmed(); // 假设你有个 QLineEdit 输入订阅的 Topic
    if (topic.isEmpty()) {
        QMessageBox::warning(this, "订阅失败", "订阅主题为空！");
        return;
    }

    if (!mqttModule->isConnected()) {
        QMessageBox::warning(this, "订阅失败", "MQTT 未连接！");
        return;
    }

    mqttModule->subscribeTopic(topic);
    ui->textEditMessage->append(QString("已订阅主题: %1").arg(topic));

    //  提示订阅成功
    //message：要显示的文本内容。timeout：显示时间（毫秒），表示消息在状态栏中显示多久后自动消失。
    ui->statusbar->showMessage(QString("已订阅 Topic: %1").arg(topic), 3000);
}
