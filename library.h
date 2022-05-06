#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMainWindow>


#include "homepage.h"

#include "addmember_copy.h"

#include "finalmember.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Library; }
QT_END_NAMESPACE

class Library : public QMainWindow
{
    Q_OBJECT

public:
    Library(QWidget *parent = nullptr);
    ~Library();
protected:
 void resizeEvent(QResizeEvent* evt) override;

private slots:
 void on_pushButton_login_clicked();

private:
    Ui::Library *ui;


    Homepage *homepage;


    addmember_copy *addmember_copy;

    Finalmember *finalmember;

};
#endif // LIBRARY_H
