#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>  // 必须包含，用于重写 paintEvent
#include "controlmodule.h"
#include "mqttmodule.h"
#include "serialmanager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMqttClient *m_client = nullptr;

public slots:
    void on_ledBtn_clicked(bool checked);
    void on_fanBtn_clicked(bool checked);
    void on_alarmBtn_clicked(bool checked);

    void updateMQTTMessage(const QString &topic, const QByteArray &msg);
    void updateMQTTPubMessage(QString topic, QString payload);
    void updateMQTTSubMessage(QString topic, QString payload);
    void updateMQTTState(QMqttClient::ClientState state);

protected:
    void paintEvent(QPaintEvent *event) override; // 重写 paintEvent
private slots:
    void on_connectMqttButton_clicked(bool checked);

    void on_openSerialBtn_clicked(bool checked);

    void on_clearPubBtn_clicked();

    void on_clearSubBtn_clicked();

    void on_clearMsgBtn_clicked();

private:
    Ui::MainWindow *ui;

    ControlModule *controlModule;
    MqttModule *mqttModule;
    bool mqttConnected;
    serialmanager *serialMgr;
};

#endif // MAINWINDOW_H
