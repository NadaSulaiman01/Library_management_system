#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class Editbook;
}

class Editbook : public QDialog
{
    Q_OBJECT

public:
    explicit Editbook(QWidget *parent = nullptr);
    ~Editbook();
protected:
 void resizeEvent(QResizeEvent* evt) override;

private slots:
   void recieveData(QStringList);
   void on_pushButton_cancel_clicked();

   void on_pushButton_save_clicked();

private:
    Ui::Editbook *ui;
};

#endif // EDITBOOK_H
