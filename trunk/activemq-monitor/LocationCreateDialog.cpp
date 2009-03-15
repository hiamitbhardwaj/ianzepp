#include "LocationCreateDialog.h"

LocationCreateDialog::LocationCreateDialog(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
	ui.display->setFocus();

	// Connect to parent's slots
	connect(this, SIGNAL(createLocation(LocationItem *)), parent, SLOT(createLocation(LocationItem *)));
	connect(this, SIGNAL(updateLocation(LocationItem *)), parent, SLOT(updateLocation(LocationItem *)));
}

LocationCreateDialog::~LocationCreateDialog()
{
}

int LocationCreateDialog::exec()
{
	bool isRemoteHost = parentItem->isRemoteHost();
	bool isSubscription = parentItem->isSubscription();

	if (isRemoteHost || isSubscription)
	{
		ui.display->setText(parentItem->getDisplayText());
		ui.hostname->setText(parentItem->getRemoteHost());
		ui.hostnameAuto->setChecked(parentItem->getAutoConnection());

		if (parentItem->isStomp())
			ui.port->setCurrentIndex(StompIndex);
		else if (parentItem->isOpenWire())
			ui.port->setCurrentIndex(OpenWireIndex);
		else if (parentItem->isHttp())
			ui.port->setCurrentIndex(HttpIndex);
		else
			ui.port->setEditText(parentItem->getRemotePort());
	}

	if (isSubscription)
	{
		if (parentItem->isTopic())
			ui.channelType->setCurrentIndex(TopicIndex);
		else if (parentItem->isQueue())
			ui.channelType->setCurrentIndex(QueueIndex);

		ui.channel->setText(parentItem->getSubscription());
		ui.channelAuto->setCheckable(parentItem->getAutoSubscription());
	}

	return QDialog::exec();
}
void LocationCreateDialog::accept()
{
	LocationItem *item = new LocationItem(parentItem);

	// Basic remote items
	item->setRemoteHost(ui.hostname->text());
	item->setAutoConnection(ui.hostnameAuto->isChecked());

	// Port management
	QString port = ui.port->currentText();

	if (port == "<stomp>" || port.isEmpty())
		item->setRemotePort(QString::number(LocationItem::Stomp));
	else if (port == "<openwire>")
		item->setRemotePort(QString::number(LocationItem::OpenWire));
	else if (port == "<http>")
		item->setRemotePort(QString::number(LocationItem::Http));
	else if (port == "<https>")
		item->setRemotePort(QString::number(LocationItem::Https));
	else
		item->setRemotePort(port);

	// Channel management
	item->setType(ui.channelType->currentText());
	item->setSubscription(ui.channel->text());
	item->setAutoSubscription(ui.channelAuto->isChecked());

	// Set the visible data
	item->setData(LocationItem::DescriptionColumn, Qt::DisplayRole, item->getDisplayText());
	item->setData(LocationItem::IdColumn, Qt::DisplayRole, item->getId());

	// Accept the dialog
	QDialog::accept();
}

void LocationCreateDialog::validateLocation()
{
	bool disabled = ui.display->text().isEmpty() || ui.hostname->text().isEmpty();
	ui.create->setEnabled(false == disabled);
}

void LocationCreateDialog::setLocationEnabled(bool enabled)
{
	ui.display->setEnabled(enabled);
	ui.hostname->setEnabled(enabled);
	ui.hostnameAuto->setEnabled(enabled);
	ui.port->setEnabled(enabled);
}

void LocationCreateDialog::setChannelEnabled(bool enabled)
{
	ui.channel->setEnabled(enabled);
	ui.channelAuto->setEnabled(enabled);
	ui.channelBreak->setEnabled(enabled);
	ui.channelLabel->setEnabled(enabled);
	ui.channelType->setEnabled(enabled);
	ui.channelTypeLabel->setEnabled(enabled);
}

void LocationCreateDialog::setChannelVisible(bool visible)
{
	ui.channel->setVisible(visible);
	ui.channelAuto->setVisible(visible);
	ui.channelBreak->setVisible(visible);
	ui.channelLabel->setVisible(visible);
	ui.channelType->setVisible(visible);
	ui.channelTypeLabel->setVisible(visible);

	if (false == visible)
		setFixedHeight(200);
}

void LocationCreateDialog::setMessageVisible(bool visible)
{

}
