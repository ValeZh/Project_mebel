#ifndef MAINWINDOW_H

#include <QMainWindow>
#include "main_page.h"

#include <QLabel>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class  Product: public QWidget
{
    Q_OBJECT

public:

    QString product_name;
    float price;
    QString shop;
    QString articul;
    QString picture_path;
    QImage image;

    QVBoxLayout *layout;
    QLabel *name;
    QLabel *price1;
    QLabel *articul1;
    QLabel *shop1, *picture;
    QPushButton *buy;
    QPixmap pixmap1;

    QWidget* widget = new QWidget();

    Product(QWidget* parent, QString prod_name, float pric, QString artic, QString sh, QString picpat);

    ~Product(){}

    void MakeProduct(QWidget* parent);
    void drawImage(QLabel *label, QPixmap pixmap);

public slots:
    void show_but();
};



class MainWindow : public QMainWindow
#define MAINWINDOW_HainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Main_page *r;

    QMap<int,QLabel> butData;

    QDockWidget *productwindow;
    QWidget *productwidg;
    QGridLayout *productgrid;
    QScrollArea *scrol;

    QSqlDatabase myDB;
    int user_id;

    void makeProductWindow(QString product_name, QString price,QString articul,QString shop, int i);
    void openImage();

    void fillwithproducts();
    void open_bd();

public slots:

signals:
    void signal1();

private slots:
    void on_signUp_clicked();

    void on_pushButton_6_clicked();

    void on_addProdButt_clicked();

    void on_addShopBut_clicked();

private:
    Ui::MainWindow *ui;

    void BrowseChildren( QObject * parent );
};

#endif // MAINWINDOW_H
