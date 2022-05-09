#include "viewbooklist.h"
#include "ui_viewbooklist.h"
#include "homepage.h"
#include <QMessageBox>
int av_copies;
int bo_copies;
bool shared;
bool select_delete_book = false;
bool select_edit_book = false;
bool select_insert_book = false;
QString val;
int bookno;

Homepage *h2;

Viewbooklist::Viewbooklist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewbooklist)
{

    /* connOpen();*/
//    QPixmap pixmap(":/image/image/ref.png");
//            QIcon ButtonIcon(pixmap);
//    ui->pushButton_3->setIcon(ButtonIcon);
  //  ui->pushButton_3->setIconSize(pixmap.rect().size());
  //  ui->pushButton_3->setIcon(QIcon(":/image/image/ref.png"));
    shared = false;
    ui->setupUi(this);
    ui->pushButton->setToolTip("return");
       ui->pushButton_3->setToolTip("refresh");
    QPixmap bkgnd(":/image/image/bck.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

  //  QMainWindow::resizeEvent(evt); // call inherited implementation


        QPixmap pixmap(":/image/image/ref.png");
                QIcon ButtonIcon(pixmap);
        ui->pushButton_3->setIcon(ButtonIcon);
        QPixmap pixmap2(":/image/image/ret.png");
                QIcon ButtonIcon2(pixmap2);
        ui->pushButton->setIcon(ButtonIcon2);
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    qDebug()<< database_path;
    myDB = QSqlDatabase::addDatabase("QSQLITE");
   // QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);
    QString chosen_genre = ui->comboBox_gserach->currentText();
    if (chosen_genre=="All"){
//        qry->prepare("SELECT book_id, book_title, author_name, genre, book_place, available_quantity, borrowed_quantity,"
//                            "(available_quantity + borrowed_quantity) AS Total_quantity FROM books");
        qry->prepare("SELECT books.*,"
                     "(available_quantity + borrowed_quantity) AS Total_quantity FROM books");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();

    }
    else{
        qry->prepare("SELECT books.*,"
                   "(available_quantity + borrowed_quantity) AS Total_quantity FROM books where genre = '" + chosen_genre + "'");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }

}

Viewbooklist::~Viewbooklist()
{
    delete ui;
}

void Viewbooklist::on_pushButton_clicked()
{
  h2 = new Homepage(this);
  h2->show();
  hide();
//  connClose();
}


void Viewbooklist::on_pushButton_2_clicked()
{
    insert = new Insert(this);

    if (!select_insert_book){
       QMessageBox::warning(this,"Couldn't find book", "Please select a book to insert from the table.");
    }
    else{
       if (av_copies==0){
           select_insert_book = false;
           select_delete_book = false;
           select_edit_book = false;
        QMessageBox::warning(this,"Not enough books", "There aren't any available copies of that book to insert to members.");
       return;}
            myDB = QSqlDatabase::addDatabase("QSQLITE");
QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
            myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
     select_insert_book = false;
     select_delete_book = false;
     select_edit_book = false;
      insert->setModal(true);
       insert->show();

         connect(this, SIGNAL(sendData2(QStringList)), insert, SLOT(recieveData2(QStringList)));
      QStringList sl;
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+val+"' or book_title='"+val+"' or author_name='"+val+"' or available_quantity='"+val+"' or genre='"+val+"' or book_place='"+val+"' or borrowed_quantity='"+val+"'");
    if(qry.exec())
    {
     while(qry.next()){
         sl.append(qry.value(0).toString());
         sl.append(qry.value(1).toString());
         sl.append(qry.value(2).toString());
         sl.append(qry.value(3).toString());
         sl.append(qry.value(4).toString());
         sl.append(qry.value(5).toString());
         sl.append(qry.value(6).toString());

     }


    }



    emit sendData2(sl);
    myDB.close();
    }
}





void Viewbooklist::on_editbook_clicked()
{
    editbook = new Editbook(this);

    if (!select_edit_book){
       QMessageBox::warning(this,"Couldn't edit book details", "Please select a book to edit from the table.");
    }
    else{

            myDB = QSqlDatabase::addDatabase("QSQLITE");
QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
            myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
     select_edit_book = false;
     select_insert_book = false;
     select_delete_book = false;
     editbook->setModal(true);
       editbook->show();
         connect(this, SIGNAL(sendData(QStringList)), editbook, SLOT(recieveData(QStringList)));
      QStringList sl;
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+val+"' or book_title='"+val+"' or author_name='"+val+"' or available_quantity='"+val+"' or genre='"+val+"'or book_place='"+val+"' or borrowed_quantity='"+val+"'");
    if(qry.exec())
    {
     while(qry.next()){
         sl.append(qry.value(0).toString());
         sl.append(qry.value(1).toString());
         sl.append(qry.value(2).toString());
         sl.append(qry.value(3).toString());
         sl.append(qry.value(4).toString());
         sl.append(qry.value(5).toString());
         sl.append(qry.value(6).toString());

     }


    }



    emit sendData(sl);
    myDB.close();
    }
}


void Viewbooklist::on_Addbook_clicked()
{
    addbook = new Addbook(this);
    addbook->setModal(true);
    addbook->show();

}

void Viewbooklist::on_pushButton_3_clicked()
{ QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);
    QString chosen_genre = ui->comboBox_gserach->currentText();
    if (chosen_genre=="All"){
//        qry->prepare("SELECT book_id, book_title, author_name, genre, book_place, available_quantity, borrowed_quantity,"
//                            "(available_quantity + borrowed_quantity) AS Total_quantity FROM books");
        qry->prepare("SELECT books.*,"
                     "(available_quantity + borrowed_quantity) AS Total_quantity FROM books");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();

    }
    else{
        qry->prepare("SELECT books.*,"
                   "(available_quantity + borrowed_quantity) AS Total_quantity FROM books where genre = '" + chosen_genre + "'");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }

}


void Viewbooklist::on_pushButton_4_clicked()
{

}


void Viewbooklist::on_pushButton_deleteBook_clicked()
{
    if (!select_delete_book){
       QMessageBox::warning(this,"Couldn't delete book", "Please select a book to delete from the table.");
    }
    else{ QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
            myDB = QSqlDatabase::addDatabase("QSQLITE");
            myDB.setDatabaseName(database_path);
            if(!myDB.open()){
                 QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
            }
     select_delete_book = false;
     select_insert_book = false;
     select_edit_book = false;
     QMessageBox msgBox;
    // QString booknom = QString::number(bookno);
    // QString question ="Are you sure you want to delete book no." + booknom + "?";
     QMessageBox::StandardButton reply;
     if (bo_copies > 0){      reply = QMessageBox::question(this, "Confirm action", "This book is borrowed by one or many members, are you sure you want to delete it? If so, it will also be deleted from borrowed books list.",
                                                            QMessageBox::Yes|QMessageBox::No);
     }
    else{  reply = QMessageBox::question(this, "Confirm action", "Are you sure you want to delete the highlighted book?",
                                    QMessageBox::Yes|QMessageBox::No);}
      if (reply == QMessageBox::Yes) {
          QSqlQuery qry, qry2, qry3;
          QStringList sl;
          qry2.prepare("select * from books where book_id='"+val+"' or book_title='"+val+"' or author_name='"+val+"' or available_quantity='"+val+"' or genre='"+val+"'or book_place='"+val+"' or borrowed_quantity='"+val+"'");
          if(qry2.exec())
          {
           while(qry2.next()){
               sl.append(qry2.value(0).toString());
               sl.append(qry2.value(1).toString());
               sl.append(qry2.value(2).toString());
               sl.append(qry2.value(3).toString());
               sl.append(qry2.value(4).toString());
               sl.append(qry2.value(5).toString());



           }
           qry3.prepare("Delete from borrow where book_id='"+sl[0]+"'");
           if (!qry3.exec()){
               qDebug() << "Couldn't delete from borrow";}

//           QString borrow= sl[0];
//            qDebug() << borrow;
          }
          qry.prepare("Delete from books where book_id='"+val+"' or book_title='"+val+"' or author_name='"+val+"' or available_quantity='"+val+"' or genre='"+val+"'or book_place='"+val+"' or borrowed_quantity='"+val+"'");
           //connect(this, SIGNAL(sendRefresh(QStringList)), editbook, SLOT(recieveRefresh(QStringList)));
          if(!qry.exec()){
         // qDebug() << "Couldn't Delete the entry ";
         QMessageBox::warning(this,"Couldn't delete book", "Sorry, the book couldn't be deleted");
          }


      } else {

      }
      myDB.close();
    }
}


void Viewbooklist::on_tableView_clicked(const QModelIndex &index)
{
    select_delete_book = true;
    select_edit_book = true;
    select_insert_book = true;
    //bookno = ui->tableView->model()->index();
    val = ui->tableView->model()->index(index.row(),0).data().toString();
    //val = ui->tableView->model()->data(index).toString();
    av_copies = ui->tableView->model()->index(index.row(),5).data().toInt();
    bo_copies =ui->tableView->model()->index(index.row(),6).data().toInt();

}
void Viewbooklist::recieveRef(){
    //ui->tableView->reset();
   // myDB.close();
QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);
    QString chosen_genre = ui->comboBox_gserach->currentText();
    if (chosen_genre=="All"){
        qry->prepare("SELECT * from books");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);

        myDB.close();

    }
    else{
        qry->prepare("SELECT * from books WHERE genre='"+chosen_genre+"'");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }
  //  qDebug() << "No refresh needed";
 //   modal->clear();
}


void Viewbooklist::on_comboBox_gserach_currentTextChanged(const QString &arg1)
{
   // qDebug()<< arg1;
    connect(this,SIGNAL(sendCombo()), this, SLOT(recieveCombo()));
    emit sendCombo();

}
void Viewbooklist::recieveCombo(){
    QString chosen_genre = ui->comboBox_gserach->currentText();
    QString searchedTxt = ui->lineEdit->text();
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
        myDB = QSqlDatabase::addDatabase("QSQLITE");
        myDB.setDatabaseName(database_path);
        if(!myDB.open()){
             QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
        }
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(myDB);

        if (chosen_genre == "All") {
            if (searchedTxt.isEmpty()) {
                //qry->prepare("select * from books");
                qry->prepare("SELECT books.*,"
                             "(available_quantity + borrowed_quantity) AS Total_quantity FROM books");
                qry->exec();
                modal->setQuery(*qry);
                ui->tableView->setModel(modal);
                ui->tableView->setColumnWidth(1,350);
                 ui->tableView->setColumnWidth(2,180);
                  ui->tableView->setColumnWidth(3,100);
                 ui->tableView->setColumnWidth(4,100);
                  ui->tableView->setColumnWidth(5,130);
                  ui->tableView->setColumnWidth(6,130);
                   ui->tableView->setColumnWidth(7,120);
                myDB.close();
            } else {
                qry->prepare("SELECT books.*,"
                             "(available_quantity + borrowed_quantity) AS Total_quantity from books where lower(book_title) like '%" + searchedTxt.toLower() + "%' order by case when lower(book_title) = '" + searchedTxt.toLower() + "' then 1 when lower(book_title) like '" + searchedTxt + "' then 2 else 4 end");


//                qry->prepare("SELECT books.*,"
//                           "(available_quantity + borrowed_quantity) AS Total_quantity FROM books WHERE genre= '" + chosen_genre + "'");


                qry->exec();
                modal->setQuery(*qry);
                ui->tableView->setModel(modal);
                ui->tableView->setColumnWidth(1,350);
                 ui->tableView->setColumnWidth(2,180);
                  ui->tableView->setColumnWidth(3,100);
                 ui->tableView->setColumnWidth(4,100);
                  ui->tableView->setColumnWidth(5,130);
                  ui->tableView->setColumnWidth(6,130);
                   ui->tableView->setColumnWidth(7,120);
                myDB.close();
            }
        } else {
            if (searchedTxt.isEmpty()) {
               // qry->prepare("select * from books where genre = '" + chosen_genre + "'");
                qry->prepare("SELECT books.*,"
                           "(available_quantity + borrowed_quantity) AS Total_quantity FROM books WHERE genre= '" + chosen_genre + "'");


                qry->exec();
                modal->setQuery(*qry);
                ui->tableView->setModel(modal);
                ui->tableView->setColumnWidth(1,350);
                 ui->tableView->setColumnWidth(2,180);
                  ui->tableView->setColumnWidth(3,100);
                 ui->tableView->setColumnWidth(4,100);
                  ui->tableView->setColumnWidth(5,130);
                  ui->tableView->setColumnWidth(6,130);
                   ui->tableView->setColumnWidth(7,120);
                myDB.close();
            } else {
                qry->prepare("SELECT books.*,"
                             "(available_quantity + borrowed_quantity) AS Total_quantity from books where lower(book_title) like '%" + searchedTxt.toLower() + "%' and genre = '" + chosen_genre + "' order by case when lower(book_title) = '" + searchedTxt.toLower() + "' then 1 when lower(book_title) like '" + searchedTxt + "' then 2 else 4 end");
                qry->exec();
                modal->setQuery(*qry);
                ui->tableView->setModel(modal);
                myDB.close();
            }
        }

//    if (chosen_genre=="All"){
//        qry->prepare("SELECT * from books");
//        qry->exec();
//        modal->setQuery(*qry);
//        ui->tableView->setModel(modal);

//        myDB.close();
//    }
//    else{

//        qry->prepare("SELECT * from books WHERE genre='"+chosen_genre+"'");
//        qry->exec();
//        modal->setQuery(*qry);
//        ui->tableView->setModel(modal);
//        myDB.close();
//    }
}

void Viewbooklist::on_lineEdit_textEdited(const QString &arg1)
{
    QString chosen_genre = ui->comboBox_gserach->currentText();
    QString searchedTxt = ui->lineEdit->text();
    QString database_path= QCoreApplication::applicationDirPath() + "/library_system.db";
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(database_path);
    if(!myDB.open()){
         QMessageBox::warning(this,"Problem in database", "Failed to open the database.");
    }
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDB);

    if (searchedTxt.isEmpty() && chosen_genre == "All") {
        qry->prepare("SELECT books.*,"
                     "(available_quantity + borrowed_quantity) AS Total_quantity FROM books");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }
    else if (searchedTxt.isEmpty()) {
        qry->prepare("SELECT books.*,"
                     "(available_quantity + borrowed_quantity) AS Total_quantity from books where genre = '" + chosen_genre + "'");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }
    else if (chosen_genre == "All") {
        qry->prepare("SELECT books.*,"
                     "(available_quantity + borrowed_quantity) AS Total_quantity from books where lower(book_title) like '%" + searchedTxt.toLower() + "%' order by case when lower(book_title) = '" + searchedTxt.toLower() + "' then 1 when lower(book_title) like '" + searchedTxt + "' then 2 else 4 end");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }
    else {
        qry->prepare("SELECT books.*,"
                     "(available_quantity + borrowed_quantity) AS Total_quantity from books where lower(book_title) like '%" + searchedTxt.toLower() + "%' and genre = '" + chosen_genre + "' order by case when lower(book_title) = '" + searchedTxt.toLower() + "' then 1 when lower(book_title) like '" + searchedTxt + "' then 2 else 4 end");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->setColumnWidth(1,350);
         ui->tableView->setColumnWidth(2,180);
          ui->tableView->setColumnWidth(3,100);
         ui->tableView->setColumnWidth(4,100);
          ui->tableView->setColumnWidth(5,130);
          ui->tableView->setColumnWidth(6,130);
           ui->tableView->setColumnWidth(7,120);
        myDB.close();
    }
}

