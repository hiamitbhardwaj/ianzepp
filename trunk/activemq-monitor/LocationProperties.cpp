#include "LocationProperties.h"

LocationProperties::LocationProperties(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);

#ifdef QT_NO_DEBUG
	ui.idLabel->setVisible(false);
	ui.id->setvisible(false);
#endif
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

#ifdef QT_DEBUG
	ui.id->setText(item->getRemoteUri());
	ui.id->setToolTip(item->getRemoteUri());
#endif

	ui.remoteHost->setItemData(0, item->getRemoteUri(false));
	ui.remoteHost->setEditable(editable);
	ui.channel->setItemData(0, item->channel);
	ui.channel->setEditable(editable);
	ui.messages->setText(QString::number(item->messages));
	ui.bytes->setText(QString::number(item->messages));

	if (item->isTopic())
		ui.channelType->setCurrentIndex(TopicColumn);
	else if (item->isQueue())
		ui.channelType->setCurrentIndex(QueueColumn);

	ui.channelType->setEnabled(false);
}
