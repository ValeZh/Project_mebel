#ifndef ADDSHOP_H
#define ADDSHOP_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AddShop;
}

class AddShop : public QDialog
{
    Q_OBJECT

public:
    explicit AddShop(QWidget *parent = nullptr);
    ~AddShop();

    QSqlDatabase myDB;
    void open_bd();
    void add_shop_func();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddShop *ui;
};

#endif // ADDSHOP_H
