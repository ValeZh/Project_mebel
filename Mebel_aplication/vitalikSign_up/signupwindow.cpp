#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QtSql>
#include <QMessageBox>

signupwindow::signupwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signupwindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");

    // Перевірка на успішне відкриття бази даних
    if (!db.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }
}

signupwindow::~signupwindow()
{
    delete ui;
}

void signupwindow::on_ConfirmPushButton_clicked()
{
    QString user_name = ui->NameLineEdit->text();
    QString password = ui->PasswordLineEdit->text();
    QString phone_number = ui->PhoneNumberLineEdit->text();
    QDate date_of_birth = ui->DateOfBirthEdit->date();

    int bonus_id = 1;

    double spend_money = 0.0;

    QSqlQuery query;
    query.prepare("INSERT INTO user_table (user_name, password, phone_number, date_of_birth, bonus_id, spend_money) "
                  "VALUES (:user_name, :password, :phone_number, :date_of_birth, :bonus_id, :spend_money)");
    query.bindValue(":user_name", user_name);
    query.bindValue(":password", password);
    query.bindValue(":phone_number", phone_number);
    query.bindValue(":date_of_birth", date_of_birth);
    query.bindValue(":bonus_id", bonus_id);
    query.bindValue(":spend_money", spend_money);

    if (query.exec()) {
        QMessageBox::information(this, "Успішно", "Користувача додано до таблиці.");
        user_id = 9999;
        // Очистка полів вводу або інші дії, які вам потрібно виконати.
        db.commit();
    } else {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
    }

    db.close();
}


