#ifndef MQTT_H
#define MQTT_H

#include <QWidget>
#include "mainwindow.h"

class mqtt : public QWidget
{
    Q_OBJECT
public:
    explicit mqtt(QWidget *parent = nullptr);

    void MyMQTTSubscribe(QString);
    void MyMQTTSendMessage(const QString, const QString);
    void startMQTTSendTest();
    void sendTestMessage();

signals:
private:
    QTimer *mqttTestTimer;
    int testCounter;
};

#endif // MQTT_H
