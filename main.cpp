#include "solitaire.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Solitaire w;
    w.show();
    return a.exec();
}
