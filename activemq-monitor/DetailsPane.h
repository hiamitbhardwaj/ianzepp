#ifndef DETAILSPANE_H
#define DETAILSPANE_H

#include <QtGui/QWidget>
#include "ui_DetailsPane.h"

class DetailsPane : public QWidget
{
    Q_OBJECT

public:
    DetailsPane(QWidget *parent = 0);
    ~DetailsPane();

private:
    Ui::DetailsPaneClass ui;
};

#endif // DETAILSPANE_H
