#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto main_window = new MainWindow;

    main_window->show();

    return app.exec();
}