#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "./vitalikSign_up/signupwindow.h"
#include "./maratCart/cart.h"
#include "addprod.h"
#include "addshop.h"
#include "./vitalikLog_in/loginwindow.h"
#include "./mycash.h"
#include "vitalikSign_up/signupwindow.h"
#include "./vitalicAcount/acountwindow.h"
QList<QString> artprod;

Product::Product(QWidget* parent,QString prod_name, float pric,QString artic,QString sh, QString picpat) : QFrame(parent)
{
    product_name = prod_name;
    price = pric;
    articul = artic;
    shop = sh;
    picture_path = picpat;

    MakeProduct(parent);
    setStyle();
}

void Product::MakeProduct(QWidget* parent)
{
    this ->setFixedWidth(400);

    buy = new QPushButton(this);
    buy ->setText("buy");

    buy -> setObjectName("add to card");
    name = new QLabel(parent);
    name -> setObjectName("name");
    name -> setText(product_name);
    price1 = new QLabel(parent);
    price1 -> setObjectName("price1");
    price1 -> setText(QString::number(price) + " грн");
    articul1 = new QLabel(parent);
    articul1 -> setObjectName("articul1");
    articul1 -> setText(articul);
    shop1 = new QLabel(parent);
    shop1 -> setObjectName("shop1");
    shop1  -> setText(shop);

    picture = new QLabel(parent);
    picture -> setObjectName("picture ");
    picture->setGeometry(100, 100,400, 300);
    pixmap1 = QPixmap(picture->size());

    drawImage(picture,pixmap1);
    layout = new QVBoxLayout(parent);
    layout ->addWidget(picture);
    layout ->addWidget(name);
    layout ->addWidget(price1);
    layout ->addWidget(shop1);
    layout ->addWidget(articul1);
    layout ->addWidget(buy);
    this ->setLayout(layout);


    connect(buy,SIGNAL(clicked()),this,SLOT(add_basket()));

}

void Product::setStyle()
{
    setStyleSheet("border: 1px solid gray;border-radius: 3px;background-color: #ffffff");
    name->setStyleSheet("border:none;font: 700 11pt 'Segoe UI';");
    price1->setStyleSheet("border:none;font: 700 9pt 'Segoe UI';");
    articul1->setStyleSheet("border:none;");
    shop1->setStyleSheet("border:none;");
    buy->setStyleSheet("background-color: rgb(49, 166, 116);color: white;font: 700 9pt 'Segoe UI';");
}

void Product::drawImage(QLabel *label, QPixmap pixmap)
{
    QImage image;
    image.load(picture_path);
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap.scaled(label->size()));
}


void Product::add_basket()
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");

    // Перевірка на успішне відкриття бази даних
    if (!myDB.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }
    QMessageBox *qa;
    qa = new QMessageBox(this);
    int qua = 1;
    if(MyCash::get_user_id() != 0)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO basket (product_guid,quantity,user_id) VALUES (:product_guid,:quantity,:user_id)");
        query.bindValue(":product_guid",guid);
        query.bindValue(":quantity", qua);
        query.bindValue(":user_id", MyCash::get_user_id());
        if (query.exec())
        {
            QMessageBox::information(this, "Успішно", "Товар додан до корзини");
            // Очистка полів вводу або інші дії, які вам потрібно виконати.
            myDB.commit();
        }
        else {
            QMessageBox::critical(this, "Помилка", query.lastError().text());
        }
        }
    else
    {
        QMessageBox::critical(this, "Помилка","Треба зареєструватися щоб додати до корзини");
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addProdButt->hide();
    ui->addShopBut->hide();
    keyAdmin = new QShortcut(this);
    keyAdmin->setKey(Qt::CTRL + Qt::Key_A);
    open_bd();
    fillwithproducts();
    connect(keyAdmin, SIGNAL(activated()), this, SLOT(give_admin()));
}

MainWindow::~MainWindow()
{
    delete ui;
    myDB.close();
}

void MainWindow::fillwithproducts()
{
    QSqlQuery query;
    //названия таблиц в виде переменных сделать
    query.prepare("SELECT product_guid, product_name, price, articul, shop_name, guid FROM shop_product INNER JOIN products ON shop_product.product_guid = products.guid INNER JOIN shops ON shop_product.shop_id = shops.id");

    productgrid = new QGridLayout();
    productwidg = new QWidget();

    if(query.exec())
    {
        std::cout<<"DB connection success SET PRODUCTS"<<std::endl;
        std::cout<<query.size()<<std::endl;
        int i = 0;
        int k = 0;
        while(query.next())
        {

            QWidget* widget45 = new QWidget();
            QString pic_path = "D://Learning_2kurs//Project_mebel//Mebel_aplication//pictures//" +
                               query.value(0).toString() + ".jpg";
            QString name = query.value(1).toString();
            float price = query.value(2).toFloat();
            QString articul = query.value(3).toString();
            QString shopw = query.value(4).toString();
            Product *pr;
            pr = new Product(widget45,name,price,articul,shopw,pic_path);
            pr->guid = query.value(5).toString();
            productgrid->addWidget(pr, k, i);
            i++;
            if(i==3)
            {
                k = k  + 1;
                i = 0;
            }
        }
    }
    else
    {
        std::cout<<"DB connection NOT success SET PRODUCTS"<<std::endl;
    }

    productwidg->setLayout(productgrid);
    ui->scrollArea->setWidget(productwidg);
}

void MainWindow::open_bd()
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(DB_PATH);

    // Перевірка на успішне відкриття бази даних
    if (!myDB.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }
}

void MainWindow::on_signUp_clicked()
{
    signupwindow signwindow;
    signwindow.setModal(true);
    signwindow.exec();
}


void MainWindow::on_basket_clicked()
{
    Widget r;
    r.setModal(true);
    r.exec();
}


void MainWindow::on_addProdButt_clicked()
{
    AddProd prodw;
    prodw.setModal(true);
    prodw.exec();
}


void MainWindow::on_addShopBut_clicked()
{
    AddShop shopw;
    shopw.setModal(true);
    shopw.exec();
}


void MainWindow::on_login_clicked()
{
    loginwindow logwind;
    logwind.setModal(true);
    logwind.exec();
}



void MainWindow::on_acount_clicked()
{

    if(MyCash::get_user_id() != 0)
    {

        acountwindow acowind(MyCash::get_user_id());
        acowind.setModal(true);
        acowind.exec();
    }
    else
    {
        ui->login->click();
    }


}

void MainWindow::give_admin()
{
    ui->addProdButt->show();
    ui->addShopBut->show();
}

