#include "note_abs.h"
#include "widget.h"
#include <QMessageBox>
#include "ui_note_abs.h"

Note_Abs::Note_Abs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Note_Abs)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #F8FAE5;"); // Change to your desired background color
      ui->pushButton_ajouter_4->setStyleSheet("QPushButton { background-color: #28a745; color: white; border-radius: 5px; padding: 8px; }");
      ui->pushButton_modifier_4->setStyleSheet("QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 8px; }");
      ui->pushButton_supprimer_4->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border-radius: 5px; padding: 8px; }");
      ui->pushButton_afficher_4->setStyleSheet("QPushButton { background-color: #ffc107; color: black; border-radius: 5px; padding: 8px; }");
}

Note_Abs::~Note_Abs()
{
    delete ui;
}





void Note_Abs::on_pushButton_afficher_3_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);
    query->prepare("SELECT * FROM Abs");
    query->exec();
    Modal->setQuery(*query);
    ui -> tableView->setModel(Modal);
}





void Note_Abs::on_pushButton_ajouter_4_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE_Note -> text();
    QString Id_matiere = ui  ->  texte_Id_Note-> text();
    QString Note = ui  ->  texte_Note-> text();
    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.exec("CREATE TABLE Evaluation (CNE VARCHAR(20)	NOT NULL , "
       "Id_matiere INTEGER  NOT NULL , Note INTEGER,PRIMARY KEY (CNE,Id_matiere));");
query.prepare("insert into Evaluation values('"+CNE+"',"+Id_matiere+","+Note+");");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("L'étudiant a bien été engregistrer!");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("ERRORRRRRRRR"));
}

void Note_Abs::on_pushButton_afficher_4_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);
    query->prepare("SELECT * FROM Evaluation");
    query->exec();
    Modal->setQuery(*query);
    ui -> tableView->setModel(Modal);
}


void Note_Abs::on_pushButton_modifier_4_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE_Note -> text();
    QString Id_matiere = ui  ->  texte_Id_Note-> text();
    QString Note = ui  ->  texte_Note-> text();
    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.prepare("UPDATE Evaluation SET CNE ='"+CNE+"',Id_matiere="+Id_matiere+",Note="+Note+" WHERE CNE ='"+CNE+"' AND Id_matiere="+Id_matiere+" ;");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("L'étudiant a bien été modifier!");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("ERRORRRRRRRR"));
}

void Note_Abs::on_pushButton_supprimer_4_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE_Note -> text();
    QString Id_matiere = ui  ->  texte_Id_Note-> text();
    QString Note = ui  ->  texte_Note-> text();
    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;



query.prepare("DELETE FROM Evaluation WHERE CNE ='"+CNE+"';");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("The student has been deleted.");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("ERRORRRRRRRR"));
}
