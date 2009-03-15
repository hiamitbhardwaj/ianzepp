#ifndef LOCATIONPROPERTIES_H
#define LOCATIONPROPERTIES_H

#include <QtCore/QString>
#include <QtGui/QWidget>
#include "ui_LocationProperties.h"
#include "LocationItem.h"

class LocationProperties: public QWidget
{
Q_OBJECT

public:
	LocationProperties(QWidget *parent = 0);
	~LocationProperties();

public slots:
	void updateProperties(LocationItem *item, bool editable = false);

private:
	Ui::LocationPropertiesClass ui;
};

#endif // LOCATIONPROPERTIES_H
