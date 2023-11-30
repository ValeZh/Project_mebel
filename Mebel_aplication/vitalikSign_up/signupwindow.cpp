#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QtSql>
#include <QMessageBox>

signupwindow::signupwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signupwindow)
{
    setFixedSize(312, 290);
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");

    // Перевірка на успішне відкриття бази даних
    if (!db.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }
    this->setWindowTitle("Реєстрація");
    ui->warningLabel->hide();
    ui->warningLabel->setStyleSheet("QLabel { color : red; }");
}

signupwindow::~signupwindow()
{
    delete ui;
}

void signupwindow::on_ConfirmPushButton_clicked()
{
    QString user_name = ui->NameLineEdit->text();
    QString password = ui->PasswordLineEditd->text();
    QString phone_number = ui->PhoneNumberLineEdit->text();
    QDate date_of_birth = ui->DateOfBirthEdit->date();

    if (user_name.isEmpty() || password.isEmpty() || phone_number.isEmpty() || date_of_birth.isNull()) {
        ui->warningLabel->setText("Будьласка перевірте чи заповнені всі поля.");
        ui->warningLabel->show();
        return;
    }

    if (phone_number.length() != 10) {
        ui->warningLabel->setText("Номер телефону повинен містити 10 цифир");
        ui->warningLabel->show();
        return;
    }

    QString spend_money = "0";
    QString procent_of_sale = "0";

    QSqlQuery query;
    query.prepare("INSERT INTO users (user_name, password, phone_number, date_of_birth, spend_money, procent_of_sale) "
                  "VALUES (:user_name, :password, :phone_number, :date_of_birth, :spend_money, :procent_of_sale)");
    query.bindValue(":user_name", user_name);
    query.bindValue(":password", password);
    query.bindValue(":phone_number", phone_number);
    query.bindValue(":date_of_birth", date_of_birth);
    query.bindValue(":spend_money", spend_money);
    query.bindValue(":procent_of_sale", procent_of_sale);

    if (query.exec()) {
       qDebug() << "Користувача додано до таблиці.";
       this->close();
    } else {
        qDebug() << "Ерор.";
    }
}


