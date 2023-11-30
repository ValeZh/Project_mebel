#include "cart.h"
#include "D:/Learning_2kurs/Project_mebel/Mebel_aplication/mycash.h"

Widget::Widget(QWidget *parent)
    : QDialog(parent)
{
    makeBasket();
    connect(button1, &QPushButton::clicked, this, &Widget::buySlot);
}

Widget::~Widget()
{

}

void Widget::makeBasket()
{ 
    CartLayout = new QVBoxLayout(this);
    setStyleSheet("border: 1px solid gray;border-radius: 3px;background-color: #ffffff");
    Cardlabel = new QLabel("Корзина");
    Cardlabel->setStyleSheet("border:none;font: 700 11pt 'Segoe UI';");
    CartLayout->addWidget(Cardlabel); //Верхний напис

    CartScroll = new QScrollArea(this); //Скроларєя
    CartLayout->addWidget(CartScroll);
    CartScroll->setStyleSheet("border: 1px solid gray;border-radius: 3px;background-color: #dadada");

    CartScroll->setWidgetResizable(true);
    CartScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn ); //якісь штучки для скроларєї

    QWidget *wdg2 = new QWidget;
    CartScroll->setWidget(wdg2); //Віджєт для скроларєї

    CartLayout2 = new QVBoxLayout();
    wdg2->setLayout(CartLayout2); //Лєаут для скроларєї

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Learning_2kurs/Project_mebel/cursova.db");
    // Перевірка на успішне відкриття бази даних
    if (!db.open()) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити базу даних");
        return;
    }

    QSqlQuery query; //Отримання товарів
    query.prepare("SELECT product_name, products.guid, quantity, products.price FROM basket, products WHERE basket.product_guid = products.guid AND basket.user_id = ?");
    query.addBindValue(MyCash::get_user_id());
    query.exec();

    if(query.exec())
    {
        qDebug("click");
        while(query.next()) //Створення товару у корзині
        {
            CartItem *ci;
            ci = new CartItem(this, query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toFloat());
            CartLayout2->addWidget(ci);
        }
    }

    button1 = new QPushButton("Оформити заказ"); //кнопка для покупки
    button1->setStyleSheet("background-color: rgb(49, 166, 116);color: white;font: 700 9pt 'Segoe UI';");
    CartLayout->addWidget(button1);

    this->show();
}

void Widget::buySlot() //Слот покупки
{
    QDateTime date = QDateTime::currentDateTime();

    float boughtthisyear = 0.0; //Сума покупок клієнта у цьому році
    QSqlQuery query3;
    query3.prepare("SELECT SUM(products.price*order_items.quantity) FROM products, order_items WHERE order_items.product_guid = products.guid AND order_items.user_id = ? AND order_items.year = ?");
    query3.addBindValue(MyCash::get_user_id());
    query3.addBindValue(date.date().year());
    if(query3.exec())
    {
        qDebug("Counting ordered sum...");
        while(query3.next())
        {
            boughtthisyear += query3.value(0).toFloat(); //Формування суми покупок у цьому році
        }
    }

    QSqlQuery query; //Додавання заказу
    query.prepare("INSERT INTO order_items(user_id, product_guid, quantity, year, month, day) SELECT user_id, product_guid, quantity, ? AS year, ? AS month, ? AS day FROM basket WHERE basket.user_id = ?");
    query.addBindValue(date.date().year());
    query.addBindValue(date.date().month());
    query.addBindValue(date.date().day());
    query.addBindValue(MyCash::get_user_id());
    query.exec();

    QSqlQuery query2; //Отримання товарів з корзини на момент покупки
    query2.prepare("SELECT quantity, products.price FROM basket, products WHERE basket.product_guid = products.guid AND basket.user_id = ?");
    query2.addBindValue(MyCash::get_user_id());

    float wholeprice = 0.0; //Сума всіх товарів з корзини

    if(query2.exec())
    {
        qDebug("click");
        while(query2.next())
        {
            float priceofshipnow = query2.value(0).toFloat() * query2.value(1).toFloat();
            wholeprice += priceofshipnow; //Формування суми
            QSqlQuery queryprice1;
            queryprice1.prepare("SELECT id FROM order_items WHERE price IS NULL LIMIT 1");
            if (queryprice1.exec())
            {
                qDebug("Working1");
            }
            while(queryprice1.next())
            {
                QSqlQuery queryprice;
                queryprice.prepare("UPDATE order_items SET price = ? WHERE price IS NULL AND id = ?");
                if (boughtthisyear >= 300000.0) //Знижка
                {
                    priceofshipnow = priceofshipnow * 0.9;
                }
                else if (boughtthisyear >= 150000.0)
                {
                    priceofshipnow = priceofshipnow * 0.95;
                }
                queryprice.addBindValue(priceofshipnow);
                queryprice.addBindValue(queryprice1.value(0));
                //queryprice.addBindValue(MyCash::get_user_id());

                if(queryprice.exec())
                {
                    qDebug("Working2");
                }
            }
        }
    }

    if (boughtthisyear >= 300000.0) //Знижка
    {
        wholeprice = wholeprice*0.90;
        QSqlQuery queryprocent;
        queryprocent.prepare("UPDATE users SET procent_of_sale = 10 WHERE id = ?");
        queryprocent.addBindValue(MyCash::get_user_id());
        queryprocent.exec();
    }
    else if (boughtthisyear >= 150000.0)
    {
        wholeprice = wholeprice*0.95;
        QSqlQuery queryprocent;
        queryprocent.prepare("UPDATE users SET procent_of_sale = 5 WHERE id = ?");
        queryprocent.addBindValue(MyCash::get_user_id());
        queryprocent.exec();
    }
    else
    {
        QSqlQuery queryprocent;
        queryprocent.prepare("UPDATE users SET procent_of_sale = 0 WHERE id = ?");
        queryprocent.addBindValue(MyCash::get_user_id());
        queryprocent.exec();
    }

    QSqlQuery query5; //Очищення корзини
    query5.prepare("DELETE FROM basket WHERE basket.user_id = ?");
    query5.addBindValue(MyCash::get_user_id());

    if (query5.exec())
    {
        QMessageBox::information(this, "Успішно", "Покупка пройшла успішно! Сума заказу: " + QString::number(wholeprice));
    }

    this->close();
}




CartItem::CartItem(QWidget* parent, QString prod_name, QString pic_id, int quant, float pric) : QWidget(parent)
{
    product_name = prod_name;
    picture_id = pic_id;
    quantity = quant;
    price = pric;
    makeItem(parent, product_name, picture_id, quantity, price); //Створення товару, якщо він є у таблиці корзини
}

void CartItem::makeItem(QWidget* parent, QString prod_name, QString pic_id, int quant, float pric)
{
    LShipment1 = new QHBoxLayout(this); //Контейнер, що тримає у собі товар

    setStyleSheet("border: 1px solid gray;border-radius: 3px;background-color: #ffffff");

    shipmentimage = new QLabel(); //Зображення товару
    shipmentimage->setStyleSheet("border:none;font: 700 11pt 'Segoe UI';");
    QString pic_path = "D:/Learning_2kurs/Project_mebel/Mebel_aplication/pictures/" + pic_id + ".jpg";
    QPixmap shipment1(pic_path);
    shipmentimage->setPixmap(shipment1.scaled(100, 100));
    LShipment1->addWidget(shipmentimage);

    label = new QLabel(); //Назва товару
    label->setStyleSheet("border:none;font: 700 11pt 'Segoe UI';");
    label->setText(prod_name);
    label->setFrameStyle(QFrame::Panel | QFrame::Raised);
    label->setFixedWidth(200);
    LShipment1->addWidget(label);

    float boughtthisyear = 0.0; //Сума покупок клієнта у цьому році
    QDateTime date = QDateTime::currentDateTime();
    QSqlQuery query;
    query.prepare("SELECT SUM(products.price*order_items.quantity) FROM products, order_items WHERE order_items.product_guid = products.guid AND order_items.user_id = ? AND order_items.year = ?");
    query.addBindValue(MyCash::get_user_id());
    query.addBindValue(date.date().year());
    if(query.exec())
    {
        qDebug("Counting ordered sum...");
        while(query.next())
        {
            boughtthisyear += query.value(0).toFloat(); //Формування суми покупок у цьому році
        }
    }
    labelcost = new QLabel(); //Ціна товару
    labelcost->setStyleSheet("border:none;font: 700 11pt 'Segoe UI';");
    if (boughtthisyear >= 300000.0) //Знижка
    {
        labelcost->setText(QString::number(pric*quant*0.90));
    }
    else if (boughtthisyear >= 150000.0)
    {
        labelcost->setText(QString::number(pric*quant*0.95));
    }
    else
    {
        labelcost->setText(QString::number(pric*quant));
    }
    LShipment1->addWidget(labelcost);

    spinbox = new QSpinBox(); //Кількість товару
    spinbox->setStyleSheet("border:none;font: 700 11pt 'Segoe UI';");
    spinbox->setValue(quant);
    spinbox->setMinimum(1);
    spinbox->setMaximum(255);
    LShipment1->addWidget(spinbox);

    button = new QPushButton("Прибрати");
    button->setStyleSheet("background-color: rgb(49, 166, 116);color: white;font: 700 9pt 'Segoe UI';");
    button->setFixedHeight(100);
    LShipment1->addWidget(button);

    connect(button,SIGNAL(clicked()),this,SLOT(delSlot()));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(SpinboxSlot()));
    qDebug("Created a shipment");
}

void CartItem::delSlot() //Видалення товару
{
    qDebug("Shipment deleted");
    QSqlQuery query2;
    query2.prepare("DELETE FROM basket WHERE product_guid = ?");
    query2.addBindValue(picture_id);
    query2.exec();
    this->deleteLater(); //Дуже зручна функція, мені сподобалось
}

void CartItem::SpinboxSlot() //Зміна кількості товару
{

    qDebug("Quantity changed");
    QSqlQuery query2;
    query2.prepare("UPDATE basket SET quantity = ? WHERE product_guid = ?");
    query2.addBindValue(spinbox->value());
    query2.addBindValue(picture_id);
    query2.exec();

    float boughtthisyear = 0.0; //Сума покупок клієнта у цьому році
    QDateTime date = QDateTime::currentDateTime();
    QSqlQuery query;
    query.prepare("SELECT SUM(products.price*order_items.quantity) FROM products, order_items WHERE order_items.product_guid = products.guid AND order_items.user_id = ? AND order_items.year = ?");
    query.addBindValue(MyCash::get_user_id());
    query.addBindValue(date.date().year());
    if(query.exec())
    {
        qDebug("Counting ordered sum...");
        while(query.next())
        {
            boughtthisyear += query.value(0).toFloat(); //Формування суми покупок у цьому році
        }
    }
    if (boughtthisyear >= 300000.0) //Знижка
    {
        labelcost->setText(QString::number(price*spinbox->value()*0.90));
    }
    else if (boughtthisyear >= 150000.0)
    {
        labelcost->setText(QString::number(price*spinbox->value()*0.95));
    }
    else
    {
        labelcost->setText(QString::number(price*spinbox->value()));
    }
}
