#ifndef CART_H
#define CART_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QPixmap>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSpinBox>
#include <QMessageBox>

class  CartItem: public QWidget
{
    Q_OBJECT

public:

    QString product_name;
    float price;
    QString picture_id;
    int quantity;

    QHBoxLayout *LShipment1;
    QLabel *label;
    QLabel *shipmentlabel1;
    QPixmap *shipment1;
    QPushButton *button;
    QLineEdit *textedit;
    QSpinBox *spinbox;

    QWidget* widget09 = new QWidget();

    CartItem(QWidget* parent, QString prod_name, QString pic_id, int quant);

    ~CartItem(){}

    void makeItem(QWidget* parent, QString prod_name, QString pic_id, int quant);

public slots:
    void delSlot();
    void SpinboxSlot();
};

//----------------------------------------------------------------------------------

class Widget : public QDialog
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QGridLayout *layout;
    QLabel *Cardlabel;
    QVBoxLayout *CartLayout;
    QVBoxLayout *CartLayout2;
    QScrollArea *CartScroll;
    QSqlDatabase db;
    QPushButton *button1;

    int whatnow;
    void makeBasket();
private:

public slots:
    void buySlot();
};


#endif // CART_H
