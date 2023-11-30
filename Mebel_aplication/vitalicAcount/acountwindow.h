
#ifndef ACOUNTWINDOW_H
#define ACOUNTWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class acountwindow;
}

class acountwindow : public QDialog
{
    Q_OBJECT

public:
    explicit acountwindow(int user_id, QWidget *parent = nullptr);
    ~acountwindow();

private slots:
    void on_gotomainwindowpushButton_clicked();

private:
    Ui::acountwindow *ui;
    int user_id;
    QString getUsernameFromDatabase(int user_id);
    QDate getDateOfBirthFromDatabase(int user_id);
    QString getPhoneNumberFromDatabase(int user_id);
    QString getProcentOfSaleFromDatabase(int user_id);
    QString getSpendMoneyFromDatabase(int user_id);
};

#endif // ACOUNTWINDOW_H
