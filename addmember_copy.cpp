#include "addmember_copy.h"
#include "ui_addmember_copy.h"

addmember_copy::addmember_copy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmember_copy)
{
    ui->setupUi(this);
}

addmember_copy::~addmember_copy()
{
    delete ui;
}
void Addmember_copy::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/image/image/back.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QDialog::resizeEvent(evt); // call inherited implementation
}
