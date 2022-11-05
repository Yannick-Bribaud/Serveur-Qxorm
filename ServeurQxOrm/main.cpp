#include "ServerUi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerUi w;
    w.show();
    return a.exec();
}
