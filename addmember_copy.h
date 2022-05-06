#ifndef ADDMEMBER_COPY_H
#define ADDMEMBER_COPY_H

#include <QDialog>

namespace Ui {
class addmember_copy;
}

class addmember_copy : public QDialog
{
    Q_OBJECT

public:
    explicit addmember_copy(QWidget *parent = nullptr);
    ~addmember_copy();
protected:
 void resizeEvent(QResizeEvent* evt) override;


private:
    Ui::addmember_copy *ui;
};

#endif // ADDMEMBER_COPY_H
