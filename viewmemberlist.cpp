#include "viewmemberlist.h"
#include "ui_viewmemberlist.h"
#include "homepage.h"
#include <QMessageBox>
Homepage *h3;

bool select_delete_member =false;
bool select_edit_member = false;
bool edit = false;
QString val2;
Viewmemberlist::Viewmemberlist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewmemberlist)
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
    QString sort = ui->comboBox_sort->currentText();
    if (sort=="None"){
    qry->prepare("SELECT members.*,"
                 "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    myDB.close();
    }
    else if (sort=="Alphabetically"){
    qry->prepare("SELECT members.*,"
                 "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members ORDER BY member_name");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    myDB.close();
    }
    else{
        qry->prepare("SELECT members.*,"
                     "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members ORDER BY sub_daysLeft");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        myDB.close();
        }

}

Viewmemberlist::~Viewmemberlist()
{
    delete ui;
}

void Viewmemberlist::on_pushButton_clicked()
{
    finalmember = new Finalmember(this);
    finalmember->show();
}


void Viewmemberlist::on_pushButton_return_clicked()
{
    h3 = new Homepage(this);
    h3->show();
    hide();
}


void Viewmemberlist::on_tableView_clicked(const QModelIndex &index)
{
    select_delete_member = true;
     select_edit_member = true;
     if (index.column() == 5){
     val2 = ui->tableView->model()->index(index.row(),1).data().toString();
         return;
     }
    //bookno = ui->tableView->model()->index();
    val2 = ui->tableView->model()->data(index).toString();


}


void Viewmemberlist::on_pushButton_deletemember_clicked()
{
    if (!select_delete_member){
       QMessageBox::warning(this,"Couldn't delete member", "Please select a member to delete from the table.");
    }
    else{
            myDB = QSqlDatabase::addDatabase("QSQLITE");
            QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
            myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
     select_delete_member = false;
     QMessageBox msgBox;
    // QString booknom = QString::number(bookno);
    // QString question ="Are you sure you want to delete book no." + booknom + "?";
     QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Confirm action", "Are you sure you want to delete the highlighted member?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          QSqlQuery qry;
          qry.prepare("Delete from members where member_id='"+val2+"' or member_name='"+val2+"' or member_phone	='"+val2+"' or sub_startDate='"+val2+"' or sub_endDate='"+val2+"'");
          if(!qry.exec()){
          qDebug() << "Couldn't Delete the entry ";

          }

      } else {

      }
      myDB.close();
    }

}


void Viewmemberlist::on_pushButton_editMember_clicked()
{
    editmember = new EditMember(this);

    if (!select_edit_member){
       QMessageBox::warning(this,"Couldn't edit member details", "Please select a member to edit from the table.");
    }
    else{

            myDB = QSqlDatabase::addDatabase("QSQLITE");
            QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
            myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
     select_edit_member = false;
       editmember->show();
         connect(this, SIGNAL(sendData(QStringList)), editmember, SLOT(recieveData(QStringList)));
      QStringList sl;
    QSqlQuery qry;
    qry.prepare("select * from members where member_id='"+val2+"' or member_name='"+val2+"' or member_phone	='"+val2+"' or sub_startDate='"+val2+"' or sub_endDate='"+val2+"'");
    if(qry.exec())
    {
     while(qry.next()){
         sl.append(qry.value(0).toString());
         sl.append(qry.value(1).toString());
         sl.append(qry.value(2).toString());
         sl.append(qry.value(3).toString());
         sl.append(qry.value(4).toString());
         sl.append(qry.value(5).toString());
     }
    }
    emit sendData(sl);
    myDB.close();
    }
}


void Viewmemberlist::on_pushButton_refresh_clicked()
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);
    qry->prepare("SELECT member_id, member_name,member_phone,sub_startDate, sub_endDate,"
                 "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    myDB.close();
}


void Viewmemberlist::on_comboBox_sort_currentTextChanged(const QString &arg1)
{
    connect(this,SIGNAL(sendCombo()), this, SLOT(recieveCombo()));
    emit sendCombo();
}

void Viewmemberlist::recieveCombo(){
    if (!edit) {
        ui->lineEdit->clear();
    }
    QString sort = ui->comboBox_sort->currentText();
    QString searchedTxt = ui->lineEdit->text();
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
        myDB = QSqlDatabase::addDatabase("QSQLITE");
        myDB.setDatabaseName(database_path);
        if(!myDB.open()){
             QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
        }
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(myDB);

        if (sort == "None") {
            qry->prepare("SELECT members.*,"
                         "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView->setModel(modal);
            myDB.close();
            }
            else if (sort=="Alphabetically"){
            qry->prepare("SELECT members.*,"
                         "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members ORDER BY member_name");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView->setModel(modal);
            myDB.close();
            }
            else{
                qry->prepare("SELECT members.*,"
                             "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members ORDER BY sub_daysLeft");
                qry->exec();
                modal->setQuery(*qry);
                ui->tableView->setModel(modal);
                myDB.close();
            }
}

void Viewmemberlist::on_lineEdit_textEdited(const QString &arg1)
{
    edit = true;
    ui->comboBox_sort->setCurrentText("None");
    QString searchedTxt = ui->lineEdit->text();
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);

    if (searchedTxt.isEmpty()) {
        qry->prepare("SELECT members.*,"
                     "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        myDB.close();
    }
    else {
        qry->prepare("SELECT members.*,"
                     "Cast ((JULIANDAY(sub_endDate)-JULIANDAY('now')) As Integer)+1 AS sub_daysLeft FROM members"
                     " where Cast(member_id as varchar) like '%" + searchedTxt + "%' order by"
                     " case when Cast(member_id as varchar) = " + searchedTxt + " then 1"
                     " when Cast(member_id as varchar) like '" + searchedTxt + "%' then 2 else 4 end");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        myDB.close();
    }
    edit = false;
}

