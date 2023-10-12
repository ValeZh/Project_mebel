#ifndef MAINWINDOW_H

#include <QMainWindow>
#include "main_page.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
#define MAINWINDOW_HainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Main_page *r;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
