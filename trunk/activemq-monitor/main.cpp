#include "ActiveMQMonitor.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ActiveMQMonitor w;
    w.show();
    return a.exec();
}
