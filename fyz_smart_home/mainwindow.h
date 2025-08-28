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
#include "musicmodule.h"
#include <QEvent>
#include <QMouseEvent>

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
    bool eventFilter(QObject *watched, QEvent *event) override;

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
    void on_subTopicBtn_clicked();

    // ================= 串口辅助槽 =================
    void onSerialOpened();                          ///< 串口打开成功回调
    void onSerialClosed();                          ///< 串口关闭回调
    void onAutoSendToggled(bool enabled);           ///< 定时发送复选框切换

    //================= MUSIC辅助槽 =================
    // 播放/暂停按钮点击槽 - 控制音乐的播放和暂停状态切换
    void on_toolButton_bofangzanting_clicked();
    // 打开文件按钮点击槽 - 打开文件对话框选择音乐文件
    void on_openMusicBtn_clicked();
    // 音乐音量滑块值变化槽 - 实时响应音量滑块的数值变化
    void on_verticalSlider_musci_valueChanged(int value);
    // 声音按钮点击槽 - 控制静音/取消静音功能
    void on_toolButton_sound_clicked();
    // 检查鼠标位置槽 - 延迟检查鼠标是否离开声音控制区域
    void checkMousePosition();
    // 显示音量滑块槽 - 当鼠标悬停在声音按钮时显示音量控制滑块
    void showVolumeSlider();
    // 隐藏音量滑块槽 - 当鼠标离开声音控制区域时隐藏音量滑块
    void hideVolumeSlider();
    // 处理静音切换槽 - 执行静音和取消静音的具体逻辑
    void handleMuteToggle();
    // 显示音乐滑块槽 - 显示音乐相关的控制滑块（如果有多个滑块）
    void showMusicSlider();
    // 隐藏音乐滑块槽 - 隐藏音乐相关的控制滑块
    void hideMusicSlider();
    // 音乐滑块值变化槽 - 专门处理音乐音量滑块的值变化事件
    void onMusicSliderValueChanged(int value);
    // 音乐滑块释放槽 - 当用户释放音乐滑块时触发的操作
    void onMusicSliderReleased();
    // 声音控制初始化函数 - 初始化声音相关的控件状态和信号连接
    void setupSoundControl();

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

    musicmodule *music;         // 播放模块
    int previousVolume = 50;
    bool isMuted = false;
    void setupVolumeControl();
    QTimer *hideTimer;            ///隐藏定时器

};

#endif // MAINWINDOW_H
