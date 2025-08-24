#ifndef CONTROLMODULE_H
#define CONTROLMODULE_H

#include <QObject>

class ControlModule : public QObject
{
    Q_OBJECT
public:
    explicit ControlModule(QObject *parent = nullptr);

    // 控制接口
    void setLed(bool on);
    void setFan(bool on);
    void setAlarm(bool on);

signals:
    // 发射信号给 UI 更新
    void ledStateChanged(bool on);
    void fanStateChanged(bool on);
    void alarmStateChanged(bool on);
};

#endif // CONTROLMODULE_H
