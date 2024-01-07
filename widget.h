#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <menu.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen() {
        connClose();
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/Yassir/Desktop/EMSI/QT Projects/Gestion_Des_Notes/Database/Database.db");

        if (!mydb.open()) {
                qDebug() << "Failed to open the database:";
                qDebug() << mydb.lastError().text(); // Print the specific error
                return false;
            } else {
                qDebug() << "Connecté à la base de données";
                return true;
            }
    }
    int sqlSize(QSqlQuery query)
    {
        int initialPos = query.at();
        // Very strange but for no records .at() returns -2
        int pos = 0;
        if (query.last())
            pos = query.at() + 1;
        else
            pos = 0;
        // Important to restore initial pos
        query.seek(initialPos);
        return pos;
    }

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
