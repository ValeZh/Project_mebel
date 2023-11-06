#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QPixmap>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QGridLayout *layout;
    QHBoxLayout *LShipment1;
    QLabel *Cardlabel;
    QLabel *label;
    QLabel *shipmentlabel1;
    QPixmap *shipment1;
    QPushButton *button;
    QPushButton *button1;
    QLineEdit *textedit;
    QVBoxLayout *CartLayout;
    QVBoxLayout *CartLayout2;
    QScrollArea *CartScroll;
    void makeBasket();
    //та я хрін його знає чо їх так багато
private:

private slots:
    //void ClickedSlot();
    void EndSlot();
};
#endif // WIDGET_H
