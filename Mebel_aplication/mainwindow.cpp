#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    r = new Main_page(this);
    r->activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

