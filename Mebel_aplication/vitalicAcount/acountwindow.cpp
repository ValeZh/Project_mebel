#include "acountwindow.h"
#include "ui_acountwindow.h"

#include <QDebug>

acountwindow::acountwindow(int user_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acountwindow),
    user_id(user_id)
{
    ui->setupUi(this);

    this->setWindowTitle("Account");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");

    if (!db.open()) {
        qDebug() << "Failed to open database!";
        return;
    }

   setFixedSize(800, 500);

    QPixmap picon(":/resorses/profile_icon1.jpg");
    int w = ui->profilicon->width();
    int h = ui->profilicon->height();

    ui->profilicon->setPixmap(picon.scaled(w, h, Qt::KeepAspectRatio));

    QString username = getUsernameFromDatabase(user_id);
    QDate dateOfBirth = getDateOfBirthFromDatabase(user_id);
    QString phoneNumber = getPhoneNumberFromDatabase(user_id);
    QString procentofsale = getProcentOfSaleFromDatabase(user_id);
    QString spendmoney = getSpendMoneyFromDatabase(user_id);


    if (!username.isEmpty()) {
        ui->labelUsername->setText(username);
        ui->labelUsername->setFont(QFont("Arial", 15, QFont::Bold));
        ui->labelDateOfBirth->setText("Дата народження: " + dateOfBirth.toString("yyyy-MM-dd"));
        ui->labelDateOfBirth->setFont(QFont("Arial", 5, QFont::Bold));
        ui->labelPhoneNumber->setText("Номер телефону: " + phoneNumber);
        ui->labelPhoneNumber->setFont(QFont("Arial", 5, QFont::Bold));
        ui->labelbroatcash_2->setText( spendmoney + "грн");
        ui->labelbroatcash_2->setFont(QFont("Arial", 12, QFont::Bold));
        ui->labelsale_2->setText( procentofsale +"%");
        ui->labelsale_2->setFont(QFont("Arial", 12, QFont::Bold));
        ui->labelsale->setFont(QFont("Arial", 18, QFont::Bold));
        ui->labelbroatcash->setFont(QFont("Arial", 18, QFont::Bold));
    } else {
        qDebug() << "Не вдалося отримати ім'я користувача з бази даних";
    }

}

acountwindow::~acountwindow()
{
    delete ui;
}

QString acountwindow::getUsernameFromDatabase(int user_id)
{
    QSqlQuery query;
    query.prepare("SELECT user_name FROM users WHERE id = :user_id");
    query.bindValue(":user_id", user_id);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return QString();
}

QDate acountwindow::getDateOfBirthFromDatabase(int user_id)
{
    QSqlQuery query;
    query.prepare("SELECT date_of_birth FROM users WHERE id = :user_id");
    query.bindValue(":user_id", user_id);

    if (query.exec() && query.next()) {
        return query.value(0).toDate();
    }

    return QDate();
}

QString acountwindow::getPhoneNumberFromDatabase(int user_id)
{
    QSqlQuery query;
    query.prepare("SELECT phone_number FROM users WHERE id = :user_id");
    query.bindValue(":user_id", user_id);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return QString();
}

QString acountwindow::getSpendMoneyFromDatabase(int user_id)
{
    QSqlQuery query;
    query.prepare("SELECT spend_money FROM users WHERE id = :user_id");
    query.bindValue(":user_id", user_id);

    if (query.exec() && query.next()) {
        return QString::number(query.value(0).toFloat(), 'f', 2);
    }

    return QString();
}

QString acountwindow::getProcentOfSaleFromDatabase(int user_id)
{
    QSqlQuery query;
    query.prepare("SELECT procent_of_sale FROM users WHERE id = :user_id");
    query.bindValue(":user_id", user_id);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return QString();
}





void acountwindow::on_gotomainwindowpushButton_clicked()
{
    close();


}

