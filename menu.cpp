#include "menu.h"
#include "ui_menu.h"
#include "widget.h"
#include <QMessageBox>
#include <note_abs.h>
#include <QPixmap>

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
      this->setStyleSheet("background-color: #F8FAE5;"); // Change to your desired background color
        ui->pushButton->setStyleSheet("background-color: #007bff; color: white; padding: 2px 12px; border-radius: 5px;"); // Change button background color, text color, padding, and border radius
        ui->pushButton_ajouter->setStyleSheet("QPushButton { background-color: #28a745; color: white; border-radius: 5px; padding: 8px; }");
        ui->pushButton_modifier->setStyleSheet("QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 8px; }");
        ui->pushButton_supprimer->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border-radius: 5px; padding: 8px; }");
        ui->pushButton_afficher->setStyleSheet("QPushButton { background-color: #ffc107; color: black; border-radius: 5px; padding: 8px; }");
        ui->pushButton_ajouter_3->setStyleSheet("QPushButton { background-color: #28a745; color: white; border-radius: 5px; padding: 8px; }");
        ui->pushButton_modifier_3->setStyleSheet("QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 8px; }");
        ui->pushButton_supprimer_3->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border-radius: 5px; padding: 8px; }");
        ui->pushButton_afficher_3->setStyleSheet("QPushButton { background-color: #ffc107; color: black; border-radius: 5px; padding: 8px; }");

    QPixmap pix(":/Ressourses/Picture/Plan.png");
    ui->label_Picture->setPixmap(pix);
    Widget conn;
    if (!conn.connOpen())
        ui->label_menu->setText("Failed to open the database");
    else
        ui->label_menu->setText("Conneted...");

}

Menu::~Menu()
{
    delete ui;
}



void Menu::on_pushButton_ajouter_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE -> text();
    QString Nom = ui  ->  texte_Nom-> text();
    QString Prenom = ui  ->  texte_prenom-> text();
    QDate DN = ui  ->  DN -> date();
    QString Birthday=DN.toString();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.exec("create table Etudiant(CNE Varchar(20) primary key, "
       "Nom varchar(20), Prénom varchar(20),Date_de_naissance int)");
query.prepare("insert into Etudiant values('"+CNE+"','"+Nom+"','"+Prenom+"','"+Birthday+"');");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("L'étudiant a bien été engregistrer!");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("Erreur"));



}


//--------------------------------------------------------------------------
void Menu::on_pushButton_modifier_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE -> text();
    QString Nom = ui  ->  texte_Nom-> text();
    QString Prenom = ui  ->  texte_prenom-> text();
    QDate DN = ui  ->  DN -> date();
    QString Birthday=DN.toString();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;


query.prepare("UPDATE Etudiant SET CNE ='"+CNE+"',Nom='"+Nom+"',Prénom='"+Prenom+"',Date_de_naissance='"+Birthday+"' WHERE CNE ='"+CNE+"';");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("L'étudiant a bien été modifier!");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("Erreur"));


}
//-----------------------------------------------------------------
void Menu::on_pushButton_supprimer_clicked()
{
    Widget conn;
    QString CNE = ui  -> texte_CNE -> text();
    QString Nom = ui  ->  texte_Nom-> text();
    QString Prenom = ui  ->  texte_prenom-> text();
    QDate DN = ui  ->  DN -> date();
    QString Birthday=DN.toString();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.prepare("DELETE FROM Etudiant WHERE CNE ='"+CNE+"';");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("L'étudiant a été supprimé.");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("Erreur"));

}
//-------------------------------------------------------------
void Menu::on_pushButton_afficher_clicked()
{
     Widget conn;
     QSqlQueryModel *Modal = new QSqlQueryModel();

     conn.connOpen();
     QSqlQuery *query = new QSqlQuery(conn.mydb);
     query->prepare("SELECT * FROM Etudiant");
     query->exec();
     Modal->setQuery(*query);
     ui -> tableView->setModel(Modal);



}

//*******************************************************************





//-------------------------------------------------------------------------


//*****************************************************************************
void Menu::on_pushButton_ajouter_3_clicked()
{
    Widget conn;
    QString ID = ui  -> texte_ID -> text();
    QString Libelle = ui  ->  texte_Libelle-> text();
    QString Coeff = ui  ->  texte_Coeff-> text();
    QString CIN = ui  ->  texte_CIN_3-> text();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.prepare("insert into Matiere values("+ID+",'"+Libelle+"','"+Coeff+"','"+CIN+"');");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("La matiere a bien été engregistrer.");
    msgBox.exec();
    conn.connClose();}

}


void Menu::on_pushButton_modifier_3_clicked()
{
    Widget conn;
    QString ID = ui  -> texte_ID -> text();
    QString Libelle = ui  ->  texte_Libelle-> text();
    QString Coeff = ui  ->  texte_Coeff-> text();
    QString CIN = ui  ->  texte_CIN_3-> text();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.prepare("UPDATE Matiere SET Id_matiere ="+ID+",Libelle='"+Libelle+"',Coeff='"+Coeff+"',CIN="+CIN+" WHERE CNE ="+ID+";");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("La matière a été modifiée.");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("Erreur"));
}

void Menu::on_pushButton_supprimer_3_clicked()
{
    Widget conn;
    QString ID = ui  -> texte_ID -> text();
    QString Libelle = ui  ->  texte_Libelle-> text();
    QString Coeff = ui  ->  texte_Coeff-> text();
    QString CIN = ui  ->  texte_CIN_3-> text();

    if (!conn.connOpen()){
             qDebug() <<"Failed to open database";
             return;}

conn.connOpen();
QSqlQuery query;

query.prepare("DELETE FROM Matiere WHERE Id_matiere ="+ID+";");
qDebug() << query.lastQuery();


if (query.exec()){
    QMessageBox msgBox;
    msgBox.setText("La matière a été supprimée.");
    msgBox.exec();
    conn.connClose();}

else
    QMessageBox::critical(this,tr("ERROR::"),tr("Erreur"));

}

void Menu::on_pushButton_afficher_3_clicked()
{
    Widget conn;
    QSqlQueryModel *Modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *query = new QSqlQuery(conn.mydb);
    query->prepare("SELECT * FROM Matiere");
    query->exec();
    Modal->setQuery(*query);
    ui -> tableView->setModel(Modal);
}

void Menu::on_pushButton_clicked()
{
    Note_Abs NoteAbs ;
    NoteAbs.setModal(true);
    NoteAbs.exec();
}
