#ifndef CART_H
#define CART_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
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
#include <QDateTime>

class  CartItem: public QWidget //Клас товару
{
    Q_OBJECT

public:

    QString product_name; //Речі з таблиці
    float price;
    QString picture_id;
    int quantity;

    QHBoxLayout *LShipment1; // Контейнер товару
    QLabel *label; //Назва товару
    QLabel *labelcost; //Ціна товару
    QLabel *shipmentimage; //Зображення товару
    QPixmap *shipment1; //Піксмап зображення товару
    QPushButton *button; //Кнопка видалення товару
    QSpinBox *spinbox; //Кількість товару

    CartItem(QWidget* parent, QString prod_name, QString pic_id, int quant, float pric);

    ~CartItem(){}

    void makeItem(QWidget* parent, QString prod_name, QString pic_id, int quant, float pric);

public slots:
    void delSlot(); //Видалення товару
    void SpinboxSlot(); //Зміна кількості
};

//----------------------------------------------------------------------------------

class Widget : public QDialog //Де-факто клас корзини
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QGridLayout *layout; //Контейнер усієї корзини
    QLabel *Cardlabel; //"Корзина"
    QVBoxLayout *CartLayout;
    QVBoxLayout *CartLayout2; //Лєяути для скролареї
    QScrollArea *CartScroll;
    QSqlDatabase db;
    QPushButton *button1; //Купити

    void makeBasket(); //Створення корзини
private:

public slots:
    void buySlot(); //Купити
};


#endif // CART_H
