#ifndef TESTPAGE_H
#define TESTPAGE_H

#include <QtGui/QWidget>
#include "ui_TestPage.h"

class TestPage : public QWidget
{
    Q_OBJECT

public:
    TestPage(QWidget *parent = 0);
    ~TestPage();

private:
    Ui::TestPageClass ui;
};

#endif // TESTPAGE_H
