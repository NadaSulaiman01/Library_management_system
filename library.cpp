#include "library.h"
#include "ui_library.h"
#include <QMessageBox>

Library::Library(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Library)
{
    ui->setupUi(this);
    this->setFixedSize(400,400);
    QString sty = "QGroupBox::title {"

            "subcontrol-position: top;"    // for second image:  top;

        "}";
    ui->groupBox->setStyleSheet(sty);
    QString sty2 = "QPushButton {"

            "font: 11pt;"
            "background-color: rgb(255, 246, 231);"
            "color:rgb(108, 69, 3);"
                 "}"
            "QPushButton:hover {"
            "color: rgb(255, 246, 231);"
            "background-color: rgb(171, 110, 58);"
            "}";
    ui->pushButton_login->setStyleSheet(sty2);
    ui->widget->setStyleSheet("background-color:rgba(245,220,182,0.3);");

}

Library::~Library()
{
    delete ui;
}

void Library::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/final.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QMainWindow::resizeEvent(evt); // call inherited implementation
}

void Library::on_pushButton_login_clicked()
{
// QSettings m("datab","Library");
// QString database_path= QCoreApplication::applicationDirPath() + "/llllibrary_system.db";
// m.setValue("DBPath",database_path);
// QString mona= m.value("DBPath").toString();

// qDebug() << mona;


//    QDateTime date = QDateTime::currentDateTime();
//    QString formattedTime = date.toString("yyyy-MM-dd");
//    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

//    qDebug() << formattedTime;
//    qDebug() << formattedTimeMsg;




    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if (username == "admin" && password == "123456789"){
        hide();


        homepage = new Homepage(this);

        homepage->show();

    }
    else if (username.isEmpty() && password.isEmpty()){
        QMessageBox::warning(this,"Log in failed", "Please enter username and password to login.");

     }
    else if (username.isEmpty()){
        QMessageBox::warning(this,"Log in failed", "Please enter your username to login.");

     }
    else if (password.isEmpty()){
        QMessageBox::warning(this,"Log in failed", "Please enter your password to login.");

     }
    else{
      QMessageBox::warning(this,"Log in failed", "Username or password is incorrect. Please try again.");
      ui->lineEdit_password->setText("");
    }
}

