//
// Created by dmitriy on 09.12.23.
//
#pragma once

#include <QWidget>
#include <QUdpSocket>
#include <QLabel>

#include "UdpServer.h"
#include "HeightIndicatorWidget.h"

#ifndef TASK_QT_TREIN_UDPCLIENT_H
#define TASK_QT_TREIN_UDPCLIENT_H

class UdpClient : public QWidget
{
    Q_OBJECT
public:
    explicit UdpClient(QWidget* parent = nullptr) ;
    virtual ~UdpClient();

private slots:
    void processPendingDatagrams();
    void sendHeartbeat();
    void resizeEvent(QResizeEvent* event) override;

private:
    QUdpSocket *udpSocket;
    QLabel *serverStatusLabel;
    QLabel *heightLabel;
    HeightIndicatorWidget *heightIndicator;

    QHostAddress serverAddress;
    quint16 serverPort = 8001;
};

#endif //TASK_QT_TREIN_UDPCLIENT_H
