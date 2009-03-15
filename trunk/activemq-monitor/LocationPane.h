#ifndef LOCATIONPANE_H
#define LOCATIONPANE_H

#include <QtGui/QWidget>
#include "ui_LocationPane.h"

class LocationPane : public QWidget
{
    Q_OBJECT

public:
    LocationPane(QWidget *parent = 0);
    ~LocationPane();

private:
    Ui::LocationPaneClass ui;
};

#endif // LOCATIONPANE_H
