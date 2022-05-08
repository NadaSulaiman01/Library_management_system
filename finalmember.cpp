#include "finalmember.h"
#include "ui_finalmember.h"
#include <QMessageBox>
#include <QTime>

Finalmember::Finalmember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finalmember)
{
    ui->setupUi(this);
}

Finalmember::~Finalmember()
{
    delete ui;
}
void Finalmember::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/bck.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QDialog::resizeEvent(evt); // call inherited implementation
}

void Finalmember::on_pushButton_cancel_clicked()
{
    hide();
}


void Finalmember::on_pushButton_save_clicked()
{QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(database_path);
   if(!myDB.open()){
        QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
   }

QString first_name, last_name, sub_date, end_date, phone_num;
QDateTime datee = QDateTime::currentDateTime();
QString formattedTime = datee.toString("yyyy-MM-dd");
QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
first_name = ui->lineEdit_fname->text();
last_name = ui->lineEdit_lastname->text();
phone_num = ui->lineEdit_pnum->text();
sub_date = formattedTime;
end_date = ui->lineEdit_enddate->text();
QString full_name = first_name + " " + last_name;
QSqlQuery qry;
qry.prepare("INSERT INTO members ("
            "member_name,"
            "member_phone,"
            "sub_startDate,"
            "sub_endDate)"
            "VALUES (?,?,?,?);");
qry.addBindValue(full_name);
qry.addBindValue(phone_num);
qry.addBindValue(sub_date);
qry.addBindValue(end_date);

if(!qry.exec()){
QMessageBox::warning(this,"Couldn't add member", "Sorry, your request cannot be accomodated. Please make sure you enter valid data and the member phone number isn't used in another entry.");

}
else{
 myDB.close();
    hide();
}
}

