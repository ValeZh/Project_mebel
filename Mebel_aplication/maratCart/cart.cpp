#include "cart.h"

Widget::Widget(QWidget *parent)
    : QDialog(parent)
{
    int whatnow = 0;
    makeBasket();
    connect(button1, &QPushButton::clicked, this, &Widget::buySlot);
}

Widget::~Widget()
{

}

void Widget::makeBasket()
{ 
    CartLayout = new QVBoxLayout(this);
    Cardlabel = new QLabel("Корзина як вона є");
    CartLayout->addWidget(Cardlabel); //верхний напис

    CartScroll = new QScrollArea(this); //СКРОЛАРЄА
    CartLayout->addWidget(CartScroll);

    CartScroll->setWidgetResizable(true);
    CartScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn ); //якісь штучки для скроларєї

    QWidget *wdg2 = new QWidget;
    CartScroll->setWidget(wdg2); //віджєт для скроларєї

    CartLayout2 = new QVBoxLayout();
    wdg2->setLayout(CartLayout2); //лєаут для скроларєї

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");
    // Перевірка на успішне відкриття бази даних
    if (!db.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT product_name, products.guid, quantity FROM basket, products WHERE basket.product_guid = products.guid");
    query.exec();

    if(query.exec())
    {
        qDebug("click");
        while(query.next())
        {
            CartItem *ci;
            ci = new CartItem(this, query.value(0).toString(), query.value(1).toString(), query.value(2).toInt());
            CartLayout2-> addWidget(ci);
        }
    }

    button1 = new QPushButton("покупаем"); //кнопка
    CartLayout->addWidget(button1);


    this->show();
}

void Widget::buySlot()
{
    qDebug("click");
    QSqlQuery query;
    query.prepare("DELETE FROM basket");
    query.exec();
    this->close();
}



CartItem::CartItem(QWidget* parent, QString prod_name, QString pic_id, int quant) : QWidget(parent)
{
    product_name = prod_name;
    picture_id = pic_id;
    quantity = quant;
    makeItem(parent, product_name, picture_id, quantity);
}

void CartItem::makeItem(QWidget* parent, QString prod_name, QString pic_id, int quant)
{
    LShipment1 = new QHBoxLayout(this); //контернейрйен який тримає у собі товар. і їх типу багато

    shipmentlabel1 = new QLabel();
    QString pic_path = "D:/Learning_2kurs/Project_mebel/Mebel_aplication/pictures/" + pic_id + ".jpg";
    QPixmap shipment1(pic_path);
    shipmentlabel1->setPixmap(shipment1.scaled(100, 100));
    LShipment1->addWidget(shipmentlabel1);

    label = new QLabel();
    label->setText(prod_name);
    label->setFrameStyle(QFrame::Panel | QFrame::Raised); //шоб красіва
    label->setFixedWidth(200); //шоб красіва
    LShipment1->addWidget(label); //оо, товар якийсь

    spinbox = new QSpinBox();
    spinbox->setValue(quant);
    LShipment1->addWidget(spinbox);

    button = new QPushButton("убери товар етот к черту");
    button->setFixedHeight(100); //шоб красіва
    LShipment1->addWidget(button);

    connect(button,SIGNAL(clicked()),this,SLOT(delSlot()));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(SpinboxSlot()));
    qDebug("creatin");
}

void CartItem::delSlot()
{
    qDebug("click1");
    QSqlQuery query2;
    query2.prepare("DELETE FROM basket WHERE id = ?");
    query2.addBindValue(picture_id);
    query2.exec();
    this->deleteLater();
}

void CartItem::SpinboxSlot()
{
    qDebug("click2");
    QSqlQuery query2;
    query2.prepare("UPDATE basket SET quantity = ? WHERE id = ?");
    query2.addBindValue(spinbox->value());
    query2.addBindValue(picture_id);
    query2.exec();
}
