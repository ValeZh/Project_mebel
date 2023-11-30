#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QScrollArea>
#include <QtSql>
#include <QPushButton>
#include <QShortcut>

#define DB_PATH "D:/Learning_2kurs/Project_mebel/cursova.db"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class  Product: public QFrame
{
    Q_OBJECT

public:

    QString product_name;
    float price;
    QString shop;
    QString articul;
    QString picture_path;
    QString guid;
    QImage image;

    QVBoxLayout *layout,*mainlayout;
    QLabel *name;
    QLabel *price1;
    QLabel *articul1;
    QLabel *shop1, *picture;
    QPushButton *buy;
    QPixmap pixmap1;

    Product(QWidget* parent, QString prod_name, float pric, QString artic, QString sh, QString picpat);

    ~Product(){}

    void setStyle();
    void MakeProduct(QWidget* parent);
    void drawImage(QLabel *label, QPixmap pixmap);

public slots:
    void add_basket();
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDockWidget *productwindow;
    QWidget *productwidg;
    QGridLayout *productgrid;
    QScrollArea *scrol;

    QSqlDatabase myDB;

    void makeProductWindow(QString product_name, QString price,QString articul,QString shop, int i);
    void openImage();

    void fillwithproducts();
    void open_bd();

private slots:
    void on_signUp_clicked();

    void on_basket_clicked();

    void on_addProdButt_clicked();

    void on_addShopBut_clicked();

    void on_login_clicked();

    void on_acount_clicked();

    void give_admin();

private:
    Ui::MainWindow *ui;

    QShortcut       *keyAdmin;
};

#endif // MAINWINDOW_H
