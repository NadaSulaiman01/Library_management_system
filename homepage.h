#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include "viewbooklist.h"
#include "viewmemberlist.h"
#include "returnbook.h"


namespace Ui {
class Homepage;
}

class Homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Homepage(QWidget *parent = nullptr);
    ~Homepage();
protected:
 void resizeEvent(QResizeEvent* evt) override;

private slots:


 void on_pushButton_7_clicked();

 void on_pushButton_3_clicked();

 void on_pushButton_8_clicked();

private:
    Ui::Homepage *ui;
    Viewbooklist *viewbooklist;
    Viewmemberlist *viewmemberlist;
    Returnbook *returnbook;


};

#endif // HOMEPAGE_H
