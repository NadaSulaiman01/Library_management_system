#ifndef ADDBOOK_H
#define ADDBOOK_H
//#include "shared.h"
#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Addbook;
}

class Addbook : public QDialog
{
    Q_OBJECT

public:
    explicit Addbook(QWidget *parent = nullptr);
    ~Addbook();
protected:
 void resizeEvent(QResizeEvent* evt) override;
signals:
  void sendRef();
private slots:
 void on_pushButton_clicked();

 void on_pushButton_2_clicked();

private:
    Ui::Addbook *ui;
};

#endif // ADDBOOK_H
