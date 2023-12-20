#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "QMainWindow"
#include "UdpServer.h"
#include "UdpClient.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    UdpServer* m_Server{nullptr};
    UdpClient* m_Client{nullptr};
public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
};

#endif //MAIN_WINDOW_HPP
