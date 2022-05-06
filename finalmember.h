#ifndef FINALMEMBER_H
#define FINALMEMBER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Finalmember;
}

class Finalmember : public QDialog
{
    Q_OBJECT

public:
    explicit Finalmember(QWidget *parent = nullptr);
    ~Finalmember();
protected:
 void resizeEvent(QResizeEvent* evt) override;


private slots:
 void on_pushButton_cancel_clicked();

 void on_pushButton_save_clicked();

private:
    Ui::Finalmember *ui;
};

#endif // FINALMEMBER_H
