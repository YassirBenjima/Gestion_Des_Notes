#include "widget.h"
#include "menu.h"
#include "ui_widget.h"
#include <QPixmap>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #F8FAE5;"); // Change to your desired background color
    ui->label->setStyleSheet("color: #333333; font-size: 18px; font-weight: bold;"); // Change text color and font properties
    ui->pushButton->setStyleSheet("background-color: #007bff; color: white; padding: 8px 12px; border-radius: 5px;"); // Change button background color, text color, padding, and border radius

    QPixmap pix(":/Ressourses/Picture/Login.png");
    ui->label_Picture2->setPixmap(pix);
    if (!connOpen())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("Connecté à la base de données");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString username = ui->lineEdit_Username->text();
    QString password = ui->lineEdit_Password->text();

    if (!connOpen()) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM ADMIN WHERE Username = :username AND Password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    qDebug() << query.lastQuery();

    if (query.exec() && query.next()) {
        qDebug() << "PASSWORD IS CORRECT";
        mydb.close();
        this->hide();
        Menu menu;
        menu.setModal(true);
        menu.exec();
    } else {
        ui->label_Login->setText("The username or password is incorrect.");
    }
}
