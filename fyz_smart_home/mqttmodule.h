#ifndef MQTTMODULE_H
#define MQTTMODULE_H

#include <QObject>
#include <QtMqtt/qmqttclient.h>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


class MqttModule : public QObject
{
    Q_OBJECT
public:
    explicit MqttModule(QObject *parent = nullptr);
    ~MqttModule();

//    void connectToBroker(const QString &host, quint16 port, QLineEdit *lineEditBroker, QLineEdit *lineEditPort, QTextEdit *textEditLog);
    void connectToBroker(const QString &host, quint16 port);
    void subscribeTopic(const QString &topic);
    void publishMessage(const QString &topic, const QString &msg);
    void startTestPublish(int intervalMs = 5000);

signals:
    void messageReceived(const QString &topic, const QByteArray &msg);
    void stateChanged(QMqttClient::ClientState state);
    void connected();
    void disconnected();
    void signal_publishMessage(QString,QString);
    void signal_sublishMessage(QString,QString);

private slots:
    void handleMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void sendTestMessage();
    void onConnected();
    void onDisconnected();

private:
    QMqttClient *m_client;
    QTimer *mqttTestTimer;
    int testCounter;
};

#endif // MQTTMODULE_H
