#include "AMQMonitor.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AMQMonitor w;
    w.show();
    return a.exec();
}
