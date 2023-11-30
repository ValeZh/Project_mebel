#include "addshop.h"
#include "ui_addshop.h"
#include <QMessageBox>
#include <iostream>

AddShop::AddShop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddShop)
{
    ui->setupUi(this);
    open_bd();

}
void AddShop::open_bd()
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");


    // Перевірка на успішне відкриття бази даних
    if (!myDB.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }

}



void AddShop::add_shop_func()
{
    if(ui->shopNameLD->text().isEmpty())
    {
        QMessageBox::critical(this, "Помилка","Пусте поле");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO shops (shop_name) VALUES (:shop_name)");
    std::cout<<"DB INSERT success"<<std::endl;
    query.bindValue(":shop_name", ui->shopNameLD->text());

    if (query.exec())
    {
        QMessageBox::information(this, "Успішно", "Магазин додан до таблиці .");
        // Очистка полів вводу або інші дії, які вам потрібно виконати.
        myDB.commit();
    }
    else {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
    }
}

AddShop::~AddShop()
{
    delete ui;
    myDB.close();
}

void AddShop::on_pushButton_clicked()
{
    add_shop_func();
}

