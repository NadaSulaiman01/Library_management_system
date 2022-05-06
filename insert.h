#ifndef INSERT_H
#define INSERT_H

#include <QDialog>


namespace Ui {
class Insert;
}

class Insert : public QDialog
{
    Q_OBJECT

public:

    explicit Insert(QWidget *parent = nullptr);
    ~Insert();
protected:
 void resizeEvent(QResizeEvent* evt) override;

private slots:
  void recieveData2(QStringList);

    void on_pushButton_insert_clicked();

    void on_pushButton_cancel_clicked();

    void on_comboBox_memberid_currentTextChanged(const QString &arg1);

private:
    Ui::Insert *ui;
};

#endif // INSERT_H
