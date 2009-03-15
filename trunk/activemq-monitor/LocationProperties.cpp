#include "LocationProperties.h"

LocationProperties::LocationProperties(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
}

LocationProperties::~LocationProperties()
{

}

void LocationProperties::updateProperties(LocationItem *item, bool editable)
{
}
