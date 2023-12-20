#include "MainWindow.hpp"
#include "QVBoxLayout"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    auto center_widget = new QWidget;

    auto main_layout = new QVBoxLayout{center_widget};

    m_Server = new UdpServer{this};
    m_Client = new UdpClient{this};

    main_layout->addWidget(m_Client);
    main_layout->addWidget(m_Server);

    this->setCentralWidget(center_widget);
}

MainWindow::~MainWindow() = default;