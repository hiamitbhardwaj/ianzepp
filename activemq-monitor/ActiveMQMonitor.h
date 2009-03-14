#ifndef ACTIVEMQMONITOR_H
#define ACTIVEMQMONITOR_H

#include <QtGui/QMainWindow>
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
