#pragma once
#include <QWidget>

class HeightIndicatorWidget : public QWidget
{
    Q_OBJECT
private:
    int m_height = 0;
protected:
    void paintEvent(QPaintEvent* event) override;
public:
   explicit HeightIndicatorWidget(QWidget* parent = nullptr);

    void setHeight(int height);// Изменение высоты
signals:
    void heightChanged(int newHeight); //Сигнал об изменении высоты

};

