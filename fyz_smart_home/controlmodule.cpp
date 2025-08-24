#include "ControlModule.h"

ControlModule::ControlModule(QObject *parent) : QObject(parent) {}

void ControlModule::setLed(bool on)
{
    // 这里可以加硬件控制逻辑
    emit ledStateChanged(on); // 通知 UI
}

void ControlModule::setFan(bool on)
{
    // 硬件控制
    emit fanStateChanged(on);
}

void ControlModule::setAlarm(bool on)
{
    // 硬件控制
    emit alarmStateChanged(on);
}
