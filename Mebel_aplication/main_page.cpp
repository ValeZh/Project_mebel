#include "main_page.h"


Main_page::Main_page(QWidget *parent)
    : QWidget{parent}
{
    trybutton = new QPushButton(this);
    //trybutton -> size(QSize(100, 100));
    trybutton -> setSizeIncrement(100,100);
    trybutton -> move(50,90);
    trybutton -> setText("SVKGVSDIGBDUIEFVG");
}
