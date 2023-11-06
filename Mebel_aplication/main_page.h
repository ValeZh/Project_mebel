#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QWidget>
#include <QPushButton>



class Main_page : public QWidget
{
    Q_OBJECT
public:
    explicit Main_page(QWidget *parent = nullptr);

private:
    QPushButton *trybutton;


signals:

};

#endif // MAIN_PAGE_H
