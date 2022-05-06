#include "addmember.h"
#include "ui_addmember.h"

Addmember::Addmember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addmember)
{
    ui->setupUi(this);
}

Addmember::~Addmember()
{
    delete ui;
}
//void Addmember::resizeEvent(QResizeEvent* evt)
//{
//    QPixmap bkgnd(":/image/image/back.jpg");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//    QPalette palette;

//    palette.setBrush(QPalette::Window, bkgnd);
//    this->setPalette(palette);

//    QDialog::resizeEvent(evt); // call inherited implementation
//}
