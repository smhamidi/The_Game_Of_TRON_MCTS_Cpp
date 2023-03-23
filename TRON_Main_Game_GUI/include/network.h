#ifndef NETWORK_H
#define NETWORK_H


#include <iostream>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "extern.h"

class BroadCast : public QThread
{
    Q_OBJECT
public:
    BroadCast(QThread* parent = nullptr);
    ~BroadCast();

    void run() override;
    QUdpSocket* udp;

private:

    // shortcuts to extern variables
    QString& ip;
    int& port;
    Board& board;
    Tron& blue;
    Tron& red;

};


class ReceiveCommand : public QObject
{
    Q_OBJECT
public:
    ReceiveCommand(QObject* parent = nullptr);
    ~ReceiveCommand();

    QUdpSocket* blue_udp;
    QUdpSocket* red_udp;

    QTimer* timer;
    float blue_command_freq;
    float red_command_freq;

public slots:
    void connect_to_hosts();

private:
    int blue_receive_counter;
    int red_receive_counter;
    // shortcuts to extern variables
    QString& ip;
    int& blue_port;
    int& red_port;
    Tron& blue;
    Tron& red;

private slots:
    void handle_blue_command();
    void handle_red_command();

    void handle_timer();
};


#endif // NETWORK_H