#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include "qsqldatabase.h"
#include <QDialog>


namespace Ui {
class signupwindow;
}

class signupwindow : public QDialog
{
    Q_OBJECT

public:
    explicit signupwindow(QWidget *parent = nullptr);
    ~signupwindow();

    QSqlDatabase db;
    int user_id;

private slots:
    void on_ConfirmPushButton_clicked();

private:
    Ui::signupwindow *ui;
};

#endif // SIGNUPWINDOW_H
