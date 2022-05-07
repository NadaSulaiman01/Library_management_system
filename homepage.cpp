#include "homepage.h"
#include "ui_homepage.h"

Homepage::Homepage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Homepage)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background-color:rgba(255,249,225,0.4);");
    QString sty2 = "QPushButton {"

            "font: 16pt 'Javanese Text';"
            " background-color: rgb(255, 251, 233);"
            "color:rgb(111, 76, 19);"
                 "}"
            "QPushButton:hover {"
            "color: rgb(255, 251, 233);"
            "background-color: rgb(111, 76, 19);"
            "}";
    ui->pushButton_7->setStyleSheet(sty2);
//    ui->pushButton->setStyleSheet(sty2);
   // ui->pushButton_2->setStyleSheet(sty2);
    ui->pushButton_3->setStyleSheet(sty2);
   // ui->pushButton_4->setStyleSheet(sty2);
   // ui->pushButton_5->setStyleSheet(sty2);
   // ui->pushButton_6->setStyleSheet(sty2);
    ui->pushButton_8->setStyleSheet(sty2);
}

Homepage::~Homepage()
{
    delete ui;
}
void Homepage::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/Revonextsoft_LMS_librarymanagementsystem2-1030x427.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QMainWindow::resizeEvent(evt); // call inherited implementation
}






void Homepage::on_pushButton_7_clicked()
{
    viewbooklist = new Viewbooklist(this);
    viewbooklist->show();
    hide();
}


void Homepage::on_pushButton_3_clicked()
{
    viewmemberlist = new Viewmemberlist(this);
    viewmemberlist->show();
    hide();
}


void Homepage::on_pushButton_8_clicked()
{
    returnbook = new Returnbook(this);
    returnbook->show();
    hide();
}

