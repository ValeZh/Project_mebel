#include "addprod.h"
#include "ui_addprod.h"
#include <QMessageBox>
#include <iostream>
#include <QDebug>


AddProd::AddProd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProd)
{
    ui->setupUi(this);
    open_bd();
    shopsCBfill();

}

AddProd::~AddProd()
{
    myDB.close();
    delete ui;
}

void AddProd::open_bd()
{
    //подключение к дб
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");


    // Перевірка на успішне відкриття бази даних
    if (!myDB.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }
}

void AddProd::shopsCBfill()
{
    //заполнение QCombobox магазинами
    QSqlQuery query;
    query.prepare("SELECT shop_name FROM shops;");
    if(query.exec())
    {
        std::cout<<"DB connection success YYYYYY"<<std::endl;
        while(query.next())
        {
            ui->shopCb->addItem(QString(query.value(0).toString()));
        }
    }
    else
    {
        std::cout<<"DB connection not success"<<std::endl;
    }
}


void AddProd::drawImage()
{

    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    image.load(fileName);
    pixmap = QPixmap::fromImage(image);
    ui->picture->setPixmap(pixmap.scaled(ui->picture->size()));
}

void AddProd::on_setPicBut_clicked()
{
    drawImage();
}


void AddProd::on_approvBut_clicked()
{
    //берем айди и магазина
    int id_shop;
    QSqlQuery query;
    query.prepare("SELECT id FROM shops WHERE shop_name = '"  + ui->shopCb->currentText() + "'");
    if(query.exec())
    {
        std::cout<<"DB connection SHOP success"<<std::endl;
        while(query.next())
        {
            id_shop = query.value(0).toInt();
        }
    }
    query.clear();
    //проверка на пустоту полей
    if(ui->nameLd->text().isEmpty(),ui->priceLd->text().isEmpty(),ui->articulLd->text().isEmpty(),image.isNull())
    {
        QMessageBox::critical(this, "Помилка","Пусте поле");
        return;
    }

    //запись значений полей в бд products
    query.prepare("INSERT INTO products (product_name,price,articul) VALUES (:product_name, :price, :articul)");
    std::cout<<"DB INSERT success"<<std::endl;
    std::cout<< ui->nameLd->text().isSimpleText() <<std::endl;

    query.bindValue(":product_name", ui->nameLd->text());
    query.bindValue(":price", ui->priceLd->text().toFloat());
    query.bindValue(":articul", ui->articulLd->text());

    if (!query.exec())
    {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
        return;
    }

    //берем айди добавленного продукта
    QString prod_guid;
    query.clear();
    query.prepare("SELECT guid FROM products WHERE articul = '" + ui->articulLd->text() + "'");
    if (query.exec())
    {
        std::cout<<"DB connection PICTURE success"<<std::endl;
        while(query.next())
        {
            prod_guid = query.value(0).toString();
        }
    }

    query.clear();

    //добавляем в таблицу которая отвечает в каком магазине какой товар
    query.prepare("INSERT INTO shop_product (product_guid,shop_id,quantity) VALUES (:product_guid,:shop_id,:quantity)");
        std::cout<<"SHOP_PRODUCT INSERT success"<<std::endl;
        query.bindValue(":product_guid", prod_guid);
        query.bindValue(":shop_id",id_shop);
        query.bindValue(":quantity",ui->spinBox->value());

    if (query.exec())
    {
        QMessageBox::information(this, "Успішно", "Товар додан до таблиці .");
        // Очистка полів вводу або інші дії, які вам потрібно виконати.
        myDB.commit();
    }
    else {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
    }

    //сохраняем картинку по пути
    image.save("D://Learning_2kurs//Project_mebel//Mebel_aplication//pictures//" +prod_guid  + ".jpg");

}

