#include "insert.h"
#include "QSqlQuery"
#include "ui_insert.h"
#include "QSqlQueryModel"
#include <QTime>
//#include "viewbooklist.h"
#include <QMessageBox>
//Viewbooklist *viewbooklist;

Insert::Insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insert)
{
    ui->setupUi(this);
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
          QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
                myDB.setDatabaseName(database_path);
               if(!myDB.open()){
                    QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
               }
               QSqlQueryModel *modal = new QSqlQueryModel();
               QSqlQuery *qry = new QSqlQuery(myDB);

                   qry->prepare("select member_id from members ORDER BY member_id");
                   qry->exec();
                   modal->setQuery(*qry);
                   ui->comboBox_memberid->setModel(modal);

                   myDB.close();


}

Insert::~Insert()
{
    delete ui;
}
void Insert::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/back.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QDialog::resizeEvent(evt); // call inherited implementation
}
void Insert::recieveData2(QStringList sl){
     ui->lineEdit_bookid->setText(sl[0]);
    ui->lineEdit_title->setText(sl[1]);
    ui->lineEdit_author->setText(sl[2]);

}

void Insert::on_pushButton_insert_clicked()
{      QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
       QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
             myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
            QString  bookTitle, bookAuthor, borrowDate, returnDate, bookID, memberID, memberName;
               QDateTime datee = QDateTime::currentDateTime();
               QString formattedTime = datee.toString("yyyy-MM-dd");
               QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

               bookID= ui->lineEdit_bookid->text();
               bookTitle = ui->lineEdit_title->text();
               bookAuthor = ui->lineEdit_author->text();
               memberName = ui->lineEdit_membername->text();
               memberID = ui->comboBox_memberid->currentText();
               borrowDate = formattedTime;
               returnDate = ui->lineEdit_returndate->text();



    QSqlQuery qry;
    qry.prepare("INSERT INTO borrow ("
                "member_id,"
                "book_id,"
                "borrowed_date,"
                "return_date)"
                "VALUES (?,?,?,?);");
    qry.addBindValue(memberID);
    qry.addBindValue(bookID);
    qry.addBindValue(borrowDate);
    qry.addBindValue(returnDate);


    if(!qry.exec()){
    qDebug() << "Couldn't insert book to member";
    }
//    viewbooklist = new Viewbooklist(this);
       myDB.close();
      // emit sendRef();
       hide();
}


void Insert::on_pushButton_cancel_clicked()
{
    hide();
}


void Insert::on_comboBox_memberid_currentTextChanged(const QString &arg1)
{
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
          QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
                myDB.setDatabaseName(database_path);
               if(!myDB.open()){
                    QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
               }
                      QSqlQuery qry;
                  QString memberid = ui->comboBox_memberid->currentText();
                   qry.prepare("select * from members where member_id='"+memberid+"'");
                   if(qry.exec()){
                       while(qry.next()){
                       ui->lineEdit_membername->setText(qry.value(1).toString());}
                   }
                   myDB.close();

}

