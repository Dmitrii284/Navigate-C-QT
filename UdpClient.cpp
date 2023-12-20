//
// Created by dmitriy on 09.12.23.
//
#include "UdpClient.h"

#include <QTimer>
#include <QDateTime>
#include <QResizeEvent>
#include "QVBoxLayout"

#pragma pack(push, 1)
struct Message1 {
    quint16 header = 0xABCD;
    quint16 height{};
};
struct Message2 {
    quint16 header = 0x1234;
};
#pragma pack(pop)

UdpClient::UdpClient(QWidget *parent) : QWidget(parent)
{
    auto main_layout = new QVBoxLayout;

    udpSocket = new QUdpSocket(this);

    udpSocket->bind(QHostAddress{"127.0.0.1"}, 8002);

    serverStatusLabel = new QLabel("Статус сервера: ", this);

    heightLabel = new QLabel("Индикатор высоты", this);

    heightIndicator = new HeightIndicatorWidget(this);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClient::processPendingDatagrams);

    auto *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &UdpClient::sendHeartbeat);
    timer->start(1000./2.);

    main_layout->addWidget(serverStatusLabel);
    main_layout->addWidget(heightLabel);
    main_layout->addWidget(heightIndicator);

    this->setLayout(main_layout);
}

void UdpClient::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {

        QByteArray datagram;
        Message1 message;

        datagram.resize(udpSocket->pendingDatagramSize());

        udpSocket->readDatagram(datagram.data(), datagram.size());

        QDataStream stream(datagram);

        //There is no point to read height here because we are not sure that message is not broken
        //stream >> message.header >> message.height; //Wrong
        stream >> message.header;

      if (message.header != 0xABCD) return;

            //Read height if message is not broken
        stream >> message.height;

        heightIndicator->setHeight(message.height);
        heightLabel->setText(QString("Height: %1").arg(message.height));

        serverStatusLabel->setText(QString{"Подключение: есть"});

        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress senderAddr;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                             &senderAddr, &senderPort);

        if (sizeof(Message1) == datagram.size()) {
            Message1 msg;
            memcpy(&msg, datagram.data(), sizeof(msg));

            // Получили данные высоты от сервера
            if (msg.header == 0xABCD) {
                heightIndicator->setHeight(msg.height);
                heightLabel->setText(QString("%1 см").arg(msg.height));
                serverStatusLabel->setText("---------Есть связь!!!----------");
            }
        }
    }
}

void UdpClient::sendHeartbeat() {
    Message2 msg;
    msg.header = 0x1234;
    udpSocket->writeDatagram((char*)&msg, sizeof(msg),
                          serverAddress, serverPort);
}

void UdpClient::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    // обрабатываем изменение размера
    // Размеры виджета

    int newWidth = event->size().width();
    int newHeight = event->size().height();

    // Устанавливаем положение надписей
    serverStatusLabel->move(10, 10);
    heightLabel->move(10, 30);

    // Размер и положение индикатора высоты
    heightIndicator->setGeometry(0, 50, newWidth, newHeight - 50);
    update();
}

UdpClient::~UdpClient() = default;