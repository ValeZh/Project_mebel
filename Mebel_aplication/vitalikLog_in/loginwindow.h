#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QLabel>

namespace Ui {
class loginwindow;
}

class loginwindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();

private slots:
    void on_ConfimpushButton_clicked();
    void on_gotosignuppushButton_clicked();

private:
    Ui::loginwindow *ui;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QSqlDatabase db;

    void setupUi();
    void setupDatabase();
};

#endif // LOGINWINDOW_H
