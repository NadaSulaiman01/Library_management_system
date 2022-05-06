#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Returnbook;
}

class Returnbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit Returnbook(QWidget *parent = nullptr);
    ~Returnbook();
signals:
    void sendCombo();


private slots:

     void recieveCombo();

    void on_pushButton_returnToHome_clicked();

    void on_comboBox_sort_currentTextChanged(const QString &arg1);

    void on_pushButton_returnbook_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_refresh_clicked();

private:
    Ui::Returnbook *ui;
};

#endif // RETURNBOOK_H
