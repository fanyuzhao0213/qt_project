#ifndef CONTROLMODULE_H
#define CONTROLMODULE_H

#include <QObject>

/**
 * @brief The ControlModule class
 * 控制模块类：用于管理设备（LED、风扇、报警器）的开关控制。
 *
 * - 提供公共接口函数（setLed / setFan / setAlarm），用于外部调用。
 * - 发射信号（ledStateChanged / fanStateChanged / alarmStateChanged），
 *   通知 UI 层或其他模块设备状态的变化。
 *
 * @note 目前只包含逻辑接口，具体硬件控制逻辑需要在实现文件中补充。
 */
class ControlModule : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象，默认为 nullptr
     */
    explicit ControlModule(QObject *parent = nullptr);

    // ================= 设备控制接口 =================
    /**
     * @brief 控制 LED 状态
     * @param on true = 打开，false = 关闭
     */
    void setLed(bool on);

    /**
     * @brief 控制风扇状态
     * @param on true = 打开，false = 关闭
     */
    void setFan(bool on);

    /**
     * @brief 控制报警器状态
     * @param on true = 打开，false = 关闭
     */
    void setAlarm(bool on);

signals:
    // ================= 状态变化信号 =================
    /**
     * @brief LED 状态发生变化
     * @param on true = 打开，false = 关闭
     */
    void ledStateChanged(bool on);

    /**
     * @brief 风扇状态发生变化
     * @param on true = 打开，false = 关闭
     */
    void fanStateChanged(bool on);

    /**
     * @brief 报警器状态发生变化
     * @param on true = 打开，false = 关闭
     */
    void alarmStateChanged(bool on);
};

#endif // CONTROLMODULE_H
