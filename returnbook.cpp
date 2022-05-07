#include "returnbook.h"
#include "ui_returnbook.h"
#include "homepage.h"
#include <QMessageBox>
Homepage *h4;
bool select_return_book = false;
bool IDedit_rtrn = false;
QString val3;
QString val4;
Returnbook::Returnbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Returnbook)
{
    ui->setupUi(this);
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);
//    qry->prepare("SELECT borrow.member_id, borrow.borrowed_date, borrow.return_date, books.book_title, books.author_name FROM borrow"
//                 "LEFT JOIN books ON borrow.book_id = books.book_id");
    QString sort = ui->comboBox_sort->currentText();
      if (sort=="None"){
    qry->prepare("SELECT borrow.*,"
                  "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);}
      else {
    qry->prepare("SELECT borrow.*,"
                  "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow ORDER BY borrowed_daysLeft");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);}
      myDB.close();
}

Returnbook::~Returnbook()
{
    delete ui;
}

void Returnbook::on_pushButton_returnToHome_clicked()
{
    h4 = new Homepage(this);
    h4->show();
    hide();
}


void Returnbook::on_comboBox_sort_currentTextChanged(const QString &arg1)
{
    connect(this,SIGNAL(sendCombo()), this, SLOT(recieveCombo()));
    emit sendCombo();
}

void Returnbook::recieveCombo(){
    if (!IDedit_rtrn) {
        ui->lineEdit->clear();
    }
    QString sort = ui->comboBox_sort->currentText();
    QString searchedTxt = ui->lineEdit->text();
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
     QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
        myDB.setDatabaseName(database_path);
        if(!myDB.open()){
             QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
        }
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(myDB);
        if (sort=="None"){
      qry->prepare("SELECT borrow.*,"
                    "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow");
      qry->exec();
      modal->setQuery(*qry);
      ui->tableView->setModel(modal);}
        else {
      qry->prepare("SELECT borrow.*,"
                    "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow ORDER BY borrowed_daysLeft");
      qry->exec();
      modal->setQuery(*qry);
      ui->tableView->setModel(modal);}
        myDB.close();


}

void Returnbook::on_pushButton_returnbook_clicked()
{
    if (!select_return_book){
       QMessageBox::warning(this,"Couldn't return book", "Please select one book to return from the table.");
    }
    else{ QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
        QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
            myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
     select_return_book = false;
     QMessageBox msgBox;

     QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Confirm action", "Are you sure you want to return the highlighted book?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          QSqlQuery qry2;
          qry2.prepare("Delete from borrow where book_id='"+val3+"' AND member_id='"+val4+"'");
        if (!qry2.exec()){
            qDebug()<< "Couldn't return book";

      } else {

      }
      myDB.close();
    }

}
}

void Returnbook::on_tableView_clicked(const QModelIndex &index)
{
    select_return_book = true;
    //val3 = ui->tableView->model()->data(index).toString();
     val4 = ui->tableView->model()->index(index.row(),0).data().toString();
      val3 = ui->tableView->model()->index(index.row(),3).data().toString();
}


void Returnbook::on_pushButton_refresh_clicked()
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);
//    qry->prepare("SELECT borrow.member_id, borrow.borrowed_date, borrow.return_date, books.book_title, books.author_name FROM borrow"
//                 "LEFT JOIN books ON borrow.book_id = books.book_id");
    QString sort = ui->comboBox_sort->currentText();
      if (sort=="None"){
    qry->prepare("SELECT borrow.*,"
                  "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);}
      else {
    qry->prepare("SELECT borrow.*,"
                  "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow ORDER BY borrowed_daysLeft");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);}
      myDB.close();
}


void Returnbook::on_lineEdit_textEdited(const QString &arg1)
{
    IDedit_rtrn = true;
    ui->comboBox_sort->setCurrentText("None");
    QString searchedTxt = ui->lineEdit->text();
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);

    if (searchedTxt.isEmpty()) {
        qry->prepare("SELECT borrow.*,"
                      "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        myDB.close();
    }
    else {
        qry->prepare("SELECT borrow.*,"
                     "Cast ((JULIANDAY(return_date)-JULIANDAY('now')) As Integer)+1 AS borrowed_daysLeft FROM borrow"
                     " where Cast(member_id as varchar) like '%" + searchedTxt + "%' order by"
                     " case when Cast(member_id as varchar) = " + searchedTxt + " then 1"
                     " when Cast(member_id as varchar) like '" + searchedTxt + "%' then 2 else 4 end");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        myDB.close();
    }
    IDedit_rtrn = false;
}

