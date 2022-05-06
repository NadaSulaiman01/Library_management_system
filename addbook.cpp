#include "addbook.h"
#include "ui_addbook.h"
#include "viewbooklist.h"
#include "QSqlQuery"
#include <QMessageBox>
Viewbooklist *viewbooklist;
//QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
Addbook::Addbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addbook)
{
    ui->setupUi(this);
}

Addbook::~Addbook()
{
    delete ui;
}
void Addbook::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/back.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QDialog::resizeEvent(evt); // call inherited implementation
}

void Addbook::on_pushButton_clicked()
{

    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
          myDB.setDatabaseName(database_path);
         if(!myDB.open()){
              QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
         }
    QString title, author, genre, location;
    QString Quantity;
    title = ui->lineEdit_title->text();
    author = ui->lineEdit_author->text();
    location = ui->lineEdit_location->text();
    genre =  ui -> comboBox->currentText();
    // ui -> comboBox->currentText();
    Quantity = ui->lineEdit_quantity->text();
    QSqlQuery qry;
    qry.prepare("INSERT INTO books ("
                "book_title,"
                "author_name,"
                "quantity,"
                "genre,"
                "book_place)"
                "VALUES (?,?,?,?,?);");
    qry.addBindValue(title);
    qry.addBindValue(author);
    qry.addBindValue(Quantity);
    qry.addBindValue(genre);
    qry.addBindValue(location);

    if(!qry.exec()){
    qDebug() << "Couldn't add new entries ";
    }
    viewbooklist = new Viewbooklist(this);
     connect(this, SIGNAL(sendRef()), viewbooklist, SLOT(recieveRef()));

     myDB.close();
     emit sendRef();
     hide();

}


void Addbook::on_pushButton_2_clicked()
{
    hide();
}

