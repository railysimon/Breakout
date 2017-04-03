#include "arkanoid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arkanoid window;
    window.show();

    return a.exec();
}
