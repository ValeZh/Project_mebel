#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "./vitalikSign_up/signupwindow.h"
#include "./maratCart/cart.h"
#include "addprod.h"
#include "addshop.h"

QList<QString> artprod;

Product::Product(QWidget* parent,QString prod_name, float pric,QString artic,QString sh, QString picpat) : QWidget(parent)
{
    product_name = prod_name;
    price = pric;
    articul = artic;
    shop = sh;
    picture_path = picpat;
    MakeProduct(parent);
}

void Product::MakeProduct(QWidget* parent)
{
    this ->setFixedWidth(400);
    buy = new QPushButton(this);
    buy ->setText("buy");

    buy -> setObjectName("buy");
    name = new QLabel(parent);
    name -> setObjectName("name");
    name -> setText(product_name);
    price1 = new QLabel(parent);
    price1 -> setObjectName("price1");
    price1 -> setText(QString::number(price));
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

    this->setLayout(layout);
    connect(buy,SIGNAL(clicked()),this,SLOT(show_but()));
}


void Product::drawImage(QLabel *label, QPixmap pixmap)
{
    QImage image;
    image.load(picture_path);
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap.scaled(label->size()));
}


void Product::show_but()
{
    QMessageBox *qa;
    qa = new QMessageBox(this);

    qa->setText(shop);
    qa->show();
    artprod.append(shop);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    open_bd();
    fillwithproducts();
}

MainWindow::~MainWindow()
{
    delete ui;
    myDB.close();
}

void MainWindow::fillwithproducts()
{
    QSqlQuery query;
    query.prepare("SELECT id_product, product_name, price, articul, shop_name FROM shop_product INNER JOIN product_table ON shop_product.id_product = product_table.id INNER JOIN shop_table ON shop_product.id_shop = shop_table.id");

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
                               QString::number(query.value(0).toInt()) + ".jpg";
            QString name = query.value(1).toString();
            float price = query.value(2).toFloat();
            QString articul = query.value(3).toString();
            QString shopw = query.value(4).toString();
            Product *pr;
            pr = new Product(widget45,name,price,articul,shopw,pic_path);
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
    myDB.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");

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
    user_id = signwindow.user_id;
}


void MainWindow::on_pushButton_6_clicked()
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

