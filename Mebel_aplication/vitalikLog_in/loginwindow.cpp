#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QVBoxLayout>
#include "../mycash.h"
#include "../vitalikSign_up/signupwindow.h"

loginwindow::loginwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginwindow)
{
    setFixedSize(252, 291);
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");

    // Перевірка на успішне відкриття бази даних
    if (!db.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }
    this->setWindowTitle("Логін");
    ui->warningLabel->hide();
    ui->warningLabel->setStyleSheet("QLabel { color : red; }");
}

loginwindow::~loginwindow()
{
    delete ui;
}


void loginwindow::on_ConfimpushButton_clicked()
{
    QString username = ui->LoginlineEdit->text();
    QString password = ui->LoginPasswordlineEdit->text();

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE user_name = :user_name AND password = :password");
    query.bindValue(":user_name", username);
    query.bindValue(":password", password);

    if (!query.exec() || !query.next()) {
        qDebug() << "Login failed!";
        ui->warningLabel->setText("Неправильне ім'я користувача або пароль");
        ui->warningLabel->show();
        return;
    }
     this->accept();
    int userId = query.value(0).toInt();
    MyCash::set_user_id(userId);

}


void loginwindow::on_gotosignuppushButton_clicked()
{
    signupwindow signupWindow;
    signupWindow.setModal(true);
    signupWindow.exec();
    this->close();
}

