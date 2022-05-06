#ifndef EDITMEMBER_H
#define EDITMEMBER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class EditMember;
}

class EditMember : public QDialog
{
    Q_OBJECT

public:
    explicit EditMember(QWidget *parent = nullptr);
    ~EditMember();

private slots:
   void recieveData(QStringList);

   void on_pushButton_cancel_clicked();

   void on_pushButton_save_clicked();

private:
    Ui::EditMember *ui;
};

#endif // EDITMEMBER_H
