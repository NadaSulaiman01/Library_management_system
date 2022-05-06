#include "editmember.h"
#include "ui_editmember.h"
#include <QMessageBox>

EditMember::EditMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMember)
{
    ui->setupUi(this);
}

EditMember::~EditMember()
{
    delete ui;
}
void EditMember::recieveData(QStringList sl){
    ui->lineEdit_mID->setText(sl[0]);
    ui->lineEdit_name->setText(sl[1]);

    ui->lineEdit_pnum->setText(sl[2]);
    ui->lineEdit_subdate->setText(sl[3]);
    ui->lineEdit_enddate->setText(sl[4]);

}

void EditMember::on_pushButton_cancel_clicked()
{
    hide();
}


void EditMember::on_pushButton_save_clicked()
{
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
          myDB.setDatabaseName(database_path);
         if(!myDB.open()){
              QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
         }
         QString name, sub_date, end_date, phone_num, id;

         name = ui->lineEdit_name->text();
         id = ui->lineEdit_mID->text();
         phone_num = ui->lineEdit_pnum->text();
         sub_date = ui->lineEdit_subdate->text();
         end_date = ui->lineEdit_enddate->text();
      //   QString full_name = first_name + " " + last_name;

    QSqlQuery qry;
    qry.prepare("update members set member_name='"+name+"',member_phone='"+ phone_num+"',sub_startDate='"+sub_date+"',sub_endDate='"+end_date+"' where member_id='"+id+"'");


    if(!qry.exec()){
    qDebug() << "Couldn't edit the entry";
    }

     myDB.close();

     hide();

}

