#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    makeBasket();
}

Widget::~Widget()
{

}

void Widget::makeBasket()
{
    QWidget *wdg = new QWidget;

    CartLayout = new QVBoxLayout(wdg);
    Cardlabel = new QLabel("Корзина як вона є");
    CartLayout->addWidget(Cardlabel); //верхний напис

    CartScroll = new QScrollArea(wdg); //СКРОЛАРЄА
    CartLayout->addWidget(CartScroll);

    CartScroll->setWidgetResizable(true);
    CartScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn ); //якісь штучки для скроларєї

    QWidget *wdg2 = new QWidget;
    CartScroll->setWidget(wdg2); //віджєт для скроларєї

    CartLayout2 = new QVBoxLayout();
    wdg2->setLayout(CartLayout2); //лєаут для скроларєї

    int howmany = 10; //наскіки багато товарів. чисто тестова змінна, потім треба буде замінити на дані з дб

    for (int i = 0; i < howmany; i++) //створеня товарів))
    {
        LShipment1 = new QHBoxLayout(wdg); //контернейрйен який тримає у собі товар. і їх типу багато

        shipmentlabel1 = new QLabel();
        QPixmap shipment1 ("C:/Users/paixc/Documents/Cart/coach.jpg"); //Цей код збудований на кістках другої лабораторної работи
        shipment1 = shipment1.scaled(100, 100, Qt::KeepAspectRatio); //якась рандомна штука, хз нащо потрібна
        shipmentlabel1->setPixmap(shipment1); //я хз чесно говорячи, потім треба буде замінити на картинку товара з дб
        LShipment1->addWidget(shipmentlabel1);

        label = new QLabel("оооо товар якийсь"); //я хз чесно говорячи 2, потім треба буде замінити на назву товара з дб
        label->setFrameStyle(QFrame::Panel | QFrame::Raised); //шоб красіва
        label->setFixedWidth(230); //шоб красіва
        LShipment1->addWidget(label); //оо, товар якийсь

        button = new QPushButton("убери товар етот к черту (не працює)))"); //я хз чесно говорячи 3. потім треба буде... ну ви зрозуміли
        button->setFixedHeight(100); //шоб красіва
        LShipment1->addWidget(button);
        CartLayout2->addLayout(LShipment1); //хз чо за кнопка, усе одно не працює

    }

    button1 = new QPushButton("покупаем"); //кнопка
    CartLayout->addWidget(button1);
    connect(button1, SIGNAL(clicked()), wdg, SLOT(close())); //конект

    wdg->show();

    qDebug("click");
}

void Widget::EndSlot()
{
//тут типа должен был быть слот с покупкой но я к ДБ не подключал такшто ну хз удачи вам с этим))))
}
