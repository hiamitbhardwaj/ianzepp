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
	if (item->connected)
		ui.status->setText(QObject::trUtf8("Connected"));
	else
		ui.status->setText(QObject::trUtf8("Not currently connected"));

	ui.remoteHost->setItemData(0, item->remoteHost);
	ui.remoteHost->setEditable(editable);
	ui.channel->setItemData(0, item->channel);
	ui.channel->setEditable(editable);
	ui.messages->setText(QString::number(item->messages));
	ui.bytes->setText(QString::number(item->messages));
}
