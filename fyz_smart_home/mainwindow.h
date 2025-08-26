#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>       // 用于重写 paintEvent
#include <QTimer>            // 用于定时发送
#include <QMessageBox>       // 弹窗提示
#include <QComboBox>
#include <QTextBrowser>
#include <QTextCursor>
#include <QIcon>
#include <QPixmap>
#include <QCheckBox>

#include "controlmodule.h"   // 控制模块（LED/Fan/Alarm）
#include "mqttmodule.h"      // MQTT 模块
#include "serialmanager.h"   // 串口管理模块


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief 主窗口类
 * 管理 UI 显示、按钮操作、MQTT 和串口模块交互
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); ///< 构造函数
    ~MainWindow();                                  ///< 析构函数

    QMqttClient *m_client = nullptr;               ///< MQTT 客户端指针（可选直接操作）

protected:
    /**
     * @brief paintEvent
     * 重写窗口绘制事件，用于绘制全屏背景图片和背景色
     */
    void paintEvent(QPaintEvent *event) override;

private slots:
    // ================= UI 控件槽函数 =================
    void on_ledBtn_clicked(bool checked);          ///< LED 按钮点击
    void on_fanBtn_clicked(bool checked);          ///< 风扇按钮点击
    void on_alarmBtn_clicked(bool checked);        ///< 警报按钮点击
    void on_connectMqttButton_clicked(bool checked); ///< MQTT 连接按钮
    void on_openSerialBtn_clicked(bool checked);   ///< 打开/关闭串口按钮
    void on_clearPubBtn_clicked();                 ///< 清空发布文本框
    void on_clearSubBtn_clicked();                 ///< 清空订阅文本框
    void on_clearMsgBtn_clicked();                 ///< 清空消息文本框
    void on_serial_sendBtn_clicked();              ///< 串口发送按钮
    void on_serial_clearsendBtn_clicked();        ///< 清空串口发送文本框
    void on_serial_clearrevBtn_clicked();          ///< 清空串口接收文本框

    // ================= 模块数据更新槽 =================
    void updateMQTTMessage(const QString &topic, const QByteArray &msg); ///< 更新订阅消息显示
    void updateMQTTPubMessage(QString topic, QString payload);           ///< 更新发布消息显示
    void updateMQTTSubMessage(QString topic, QString payload);           ///< 更新订阅消息显示
    void updateMQTTState(QMqttClient::ClientState state);                ///< 更新 MQTT 连接状态
    void onSerialDataToSend(const QByteArray &data, bool isHex);        ///< 串口接收数据显示

    // ================= 串口辅助槽 =================
    void onSerialOpened();                          ///< 串口打开成功回调
    void onSerialClosed();                          ///< 串口关闭回调
    void onAutoSendToggled(bool enabled);           ///< 定时发送复选框切换

private:
    // ================= 初始化函数 =================
    void initUI();          ///< 初始化窗口布局、图标和标题
    void initButtons();     ///< 初始化按钮属性（Checkable/默认状态）
    void initSerialUI();    ///< 初始化串口相关 UI 控件
    void initMqttUI();      ///< 初始化 MQTT 相关 UI 控件和状态显示

    // ================= 信号槽绑定 =================
    void connectControlModule();  ///< 绑定 ControlModule 信号槽
    void connectMqttModule();     ///< 绑定 MQTT 模块信号槽
    void connectSerialModule();   ///< 绑定串口模块信号槽

private:
    Ui::MainWindow *ui;           ///< UI 指针

    ControlModule *controlModule; ///< 控制模块（LED / Fan / Alarm）
    MqttModule *mqttModule;       ///< MQTT 模块
    serialmanager *serialMgr;     ///< 串口管理模块

    QTimer *sendTimer;            ///< 串口定时发送定时器
    bool mqttConnected;           ///< MQTT 连接状态标志
};

#endif // MAINWINDOW_H
