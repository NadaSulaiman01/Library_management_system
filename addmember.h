#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QDialog>

namespace Ui {
class Addmember;
}

class Addmember : public QDialog
{
    Q_OBJECT

public:
    explicit Addmember(QWidget *parent = nullptr);
    ~Addmember();
protected:
 void resizeEvent(QResizeEvent* evt) override;

private:
    Ui::Addmember *ui;
};

#endif // ADDMEMBER_H
