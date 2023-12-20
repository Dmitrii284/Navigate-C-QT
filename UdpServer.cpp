//
// Created by dmitriy on 09.12.23.
//
#include "UdpServer.h"
#include <QTimer>
#include <QDateTime>
#include <QString>
#include <QVBoxLayout>

#pragma pack(push, 1)
struct Message1 {
    quint16 header = 0xABCD;
    quint16 height{};
};
#pragma pack(pop)

struct Message2 {
    quint16 header = 0x1234;
};

int WindowFlags;

UdpServer::UdpServer(QWidget* parent) : QWidget(parent)
{
    // Инициализация UDP сокета
    udpSocket = new QUdpSocket(this);

     //Сигналы и слоты лучше подключить.
    connect(udpSocket, &QUdpSocket::readyRead, this,
            &UdpServer::processPendingDatagrams);
    udpSocket->bind(QHostAddress{"127.0.0.1"}, 8001);

    //Сервер передает  сообщения высоты  Клиенту с частотой 25 Гц
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UdpServer::sendData);
    timer->start(1000./25.);


    slider = new QSlider{Qt::Horizontal, this};
    slider->setValue(0);
    slider->setRange(0, 9999);

    connect(slider, &QSlider::valueChanged, this, [this](int value)
    {
        m_HeightLabel->setText("Высота: " + QString::number(value));
    });

    m_HeightLabel = new QLabel{"Высота: " + QString::number(slider->value())};


    clientStatusLabel = new QLabel{"Статус клиента",this};

    auto layout = new QVBoxLayout;

    layout->addWidget(slider);
    layout->addWidget(m_HeightLabel);
    layout->addWidget(clientStatusLabel);

    this->setLayout(layout);
}

// Метод принятия сообщения чястоты от сервера С частотой соответсвенно 25Гц
void UdpServer::sendData()
{
    Message1 msg;
    msg.header = 0xABCD;
    msg.height = slider->value();

    QByteArray datagram;

    QDataStream stream(&datagram, QIODevice::WriteOnly);
    stream << msg.header << msg.height;

    udpSocket->writeDatagram(datagram, QHostAddress{"127.0.0.1"}, 8002);
}

//Метод обрабатывает входящие данные от Клиента и определяет наличие связи с Клиентом
void UdpServer::processPendingDatagrams()
{
   while (udpSocket->hasPendingDatagrams())
   {
        // Обрабатываем сообщение
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress senderAddr;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddr, &senderPort);
   }
}

UdpServer::~UdpServer() = default;