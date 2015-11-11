#include "ventilate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ventilate w;
    w.show();

    return a.exec();
}
