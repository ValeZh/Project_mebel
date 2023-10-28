#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>


Product::Product(QWidget* parent,QString prod_name, float pric,QString artic,QString sh) : QWidget(parent)
{
    product_name = prod_name;
    price = pric;
    articul = artic;
    shop = sh;
    MakeProduct(parent);
}

void Product::MakeProduct(QWidget* parent)
{
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
    picture->setGeometry(100, 100,300, 300);
    pixmap = QPixmap(picture->size());
    drawImage(picture,pixmap);
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
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    image.load(fileName);
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap.scaled(label->size()));
}

void Product::show_but()
{
        QMessageBox *qa;
        qa = new QMessageBox(this);

        qa->setText(shop);
        qa->show();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    QString pathToDB = QString("D:/Learning_2kurs/Project_mebel") + QString("/cursova.db");

    productgrid = new QGridLayout();
    productwidg = new QWidget();
    //записывать кнопки в кулист
    //записывать айди в ку лист

    int i = 0;
    for(i = 0;i<3;i++)
    {
        for(int k = 0; k<3;k++)
        {
            QWidget* widget45 = new QWidget();

            Product *pr;
            pr = new Product(widget45,"Stol",23.45,"fiewgfie",QString("shop"+ QString::number(i)));
            productgrid->addWidget(pr, k, i);
        }
    }

    productwidg->setLayout(productgrid);
    ui->scrollArea->setWidget(productwidg);

}

MainWindow::~MainWindow()
{
    delete ui;
}





