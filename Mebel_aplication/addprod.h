#ifndef ADDPROD_H
#define ADDPROD_H

#include <QDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QtSql>


namespace Ui {
class AddProd;
}

class AddProd : public QDialog
{
    Q_OBJECT

public:
    explicit AddProd(QWidget *parent = nullptr);
    ~AddProd();
    void drawImage();

    QPixmap pixmap;
    QSqlDatabase myDB;
    QImage image;
    char shop_guid;

    void open_bd();
    void shopsCBfill();

private slots:
    void on_setPicBut_clicked();

    void on_approvBut_clicked();

private:
    Ui::AddProd *ui;
};

#endif // ADDPROD_H
