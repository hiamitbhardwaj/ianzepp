#ifndef AMQMONITOR_H
#define AMQMONITOR_H

#include <QtGui/QMainWindow>
#include "ui_AMQMonitor.h"

class AMQMonitor : public QMainWindow
{
    Q_OBJECT

public:
    AMQMonitor(QWidget *parent = 0);
    ~AMQMonitor();

private:
    Ui::AMQMonitorClass ui;
};

#endif // AMQMONITOR_H
