#ifndef VIEWBOOKLIST_H
#define VIEWBOOKLIST_H

#include <QMainWindow>
#include "insert.h"
#include "editbook.h"
#include "addbook.h"
//#include "shared.h"
#include <QtSql>
#include <QDebug>
#include <QFileInfo>



namespace Ui {
class Viewbooklist;
}

class Viewbooklist : public QMainWindow
{
    Q_OBJECT

public:
    explicit Viewbooklist(QWidget *parent = nullptr);
    ~Viewbooklist();
//signals:
//  void sendSignal();
signals:
  void sendSignal(QString textt);
  void sendData(QStringList);
  void sendData2(QStringList);
  void sendCombo();
private slots:
   void recieveCombo();
   void recieveRef();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

//    void on_horizontalSlider_actionTriggered(int action);


    void on_editbook_clicked();

    void on_Addbook_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    //void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_deleteBook_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_gserach_currentTextChanged(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

public:
    QSqlDatabase myDB;

    void connClose(){
        myDB.close();
        myDB.removeDatabase(QSqlDatabase::defaultConnection);
        if(!myDB.open()){
             qDebug() << ("Database disconnected successfully.");}
    }
    bool connOpen(){
        myDB = QSqlDatabase::addDatabase("QSQLITE");
        myDB.setDatabaseName("C:/Users/Nadas/Downloads/library_system.db");
        if(!myDB.open()){
             qDebug() << ("Failed to open database.");
             return false;
        }
        else{
            qDebug() << ("Database connected successfully.");
            return true;}

    }
private:
    Ui::Viewbooklist *ui;
    Insert *insert;
    Editbook *editbook;
    Addbook *addbook;


};

#endif // VIEWBOOKLIST_H
