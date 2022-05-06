#include "library.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Library w;
    w.show();
    return a.exec();
}
