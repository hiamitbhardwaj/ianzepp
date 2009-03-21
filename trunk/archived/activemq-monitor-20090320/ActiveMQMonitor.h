#ifndef ACTIVEMQMONITOR_H
#define ACTIVEMQMONITOR_H

#ifndef QT_DEBUG
#define QT_DEBUG true
#endif

#ifndef QT_FATAL_WARNINGS
#define QT_FATAL_WARNINGS true
#endif

#include <QtGui/QMainWindow>
#include <QtDebug>
#include "ui_ActiveMQMonitor.h"


class ActiveMQMonitor : public QMainWindow
{
    Q_OBJECT

public:
    ActiveMQMonitor(QWidget *parent = 0);
    ~ActiveMQMonitor();

private:
    Ui::ActiveMQMonitorClass ui;
};

#endif // ACTIVEMQMONITOR_H
