#include "editbook.h"
#include "ui_editbook.h"
#include <QMessageBox>
Editbook::Editbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editbook)
{
    ui->setupUi(this);
}

Editbook::~Editbook()
{
    delete ui;
}
void Editbook::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/back.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QDialog::resizeEvent(evt); // call inherited implementation
}
void Editbook::recieveData(QStringList sl){
    ui->lineEdit_ID->setText(sl[0]);
    ui->lineEdit_title->setText(sl[1]);
    ui->lineEdit_author->setText(sl[2]);
    ui->lineEdit_quantity->setText(sl[3]);
    ui->comboBox_genre->setCurrentText(sl[4]);
    ui->lineEdit_location->setText(sl[5]);

}

void Editbook::on_pushButton_cancel_clicked()
{
    hide();
}


void Editbook::on_pushButton_save_clicked()
{
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
          myDB.setDatabaseName(database_path);
         if(!myDB.open()){
              QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
         }
    QString title, author, genre, location;
    QString Quantity, id;
    id = ui->lineEdit_ID->text();
    title = ui->lineEdit_title->text();
    author = ui->lineEdit_author->text();
    location = ui->lineEdit_location->text();
    genre =  ui -> comboBox_genre->currentText();
    // ui -> comboBox->currentText();
    Quantity = ui->lineEdit_quantity->text();
    QSqlQuery qry;
    qry.prepare("update books set book_title='"+title+"',author_name='"+author+"',quantity='"+Quantity+"',genre='"+genre+"',book_place='"+location+"' where book_id='"+id+"'");


    if(!qry.exec()){
    qDebug() << "Couldn't edit the entry";
    }

     myDB.close();

     hide();

}

