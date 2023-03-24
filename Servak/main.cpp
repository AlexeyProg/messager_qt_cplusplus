#include <QCoreApplication>
#include "servak.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Servak k;
    return a.exec();
}
