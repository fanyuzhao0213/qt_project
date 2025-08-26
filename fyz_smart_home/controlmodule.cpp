#include "controlmodule.h"

/**
 * @brief 构造函数
 * @param parent 父对象
 */
ControlModule::ControlModule(QObject *parent)
    : QObject(parent)
{
    // 初始化时可以在这里添加硬件初始化逻辑（如 GPIO、驱动加载等）
}

/**
 * @brief 控制 LED 状态
 * @param on true = 打开，false = 关闭
 */
void ControlModule::setLed(bool on)
{
    // TODO: 在此添加实际硬件控制代码（例如写 GPIO）
    // e.g. gpio_write(LED_PIN, on ? HIGH : LOW);

    emit ledStateChanged(on);  ///< 发射信号通知 UI
}

/**
 * @brief 控制风扇状态
 * @param on true = 打开，false = 关闭
 */
void ControlModule::setFan(bool on)
{
    // TODO: 在此添加硬件控制逻辑
    emit fanStateChanged(on);
}

/**
 * @brief 控制报警器状态
 * @param on true = 打开，false = 关闭
 */
void ControlModule::setAlarm(bool on)
{
    // TODO: 在此添加硬件控制逻辑
    emit alarmStateChanged(on);
}
