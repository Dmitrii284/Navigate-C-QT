//
// Created by dmitriy on 09.12.23.
//
#pragma once

#include <QWidget>
#include <QUdpSocket>
#include <QSlider>
#include <QLabel>
#include <QElapsedTimer>


class UdpServer : public  QWidget
{
    Q_OBJECT
public:
   explicit UdpServer(QWidget *parent = nullptr);
    virtual ~UdpServer();
private:
    QHostAddress clientAddress;

    QUdpSocket *udpSocket; //для отправки/получения данных
    QSlider *slider;
    QLabel *clientStatusLabel;
    QLabel *m_HeightLabel{nullptr};

private slots:
    void sendData();
    void processPendingDatagrams();
};
