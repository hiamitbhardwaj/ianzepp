#include "LocationCreateDialog.h"

LocationCreateDialog::LocationCreateDialog(QWidget *parent) :
	QDialog(parent), acceptSignal(LocationCreateDialog::Create)
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

void LocationCreateDialog::accept()
{
	LocationItem *item = new LocationItem(this->parentWidget());

	// Basic remote items
	item->display = ui.display->text();
	item->hostname = ui.hostname->text();
	item->hostnameAuto = ui.hostnameAuto->isChecked();

	// Port management
	QString port = ui.port->currentText();

	if (port == "<stomp>" || port.isEmpty())
		item->port = QString::number(LocationItem::StompPort);
	else if (port == "<openwire>")
		item->port = QString::number(LocationItem::OpenWirePort);
	else if (port == "<http>")
		item->port = QString::number(LocationItem::HttpPort);
	else if (port == "<https>")
		item->port = QString::number(LocationItem::HttpsPort);
	else
		item->port = port;

	// Channel management
	item->channelType = ui.channelType->currentText();
	item->channel = ui.channel->text();
	item->channelAuto = ui.channelAuto->isChecked();

	// Send out
	if (getAcceptSignal() == Create)
		emit createLocation(item);
	else if (getAcceptSignal() == Update)
		emit updateLocation(item);

	// Accept the dialog
	QDialog::accept();
}

void LocationCreateDialog::populate(LocationItem *item)
{
	if (item == 0)
		return;

	ui.display->setText(item->display);
	ui.hostname->setText(item->hostname);
	ui.hostnameAuto->setChecked(item->hostnameAuto);

	if (item->isStomp())
		ui.port->setCurrentIndex(StompIndex);
	else if (item->isOpenWire())
		ui.port->setCurrentIndex(OpenWireIndex);
	else if (item->isHttp())
		ui.port->setCurrentIndex(HttpIndex);
	else
		ui.port->setEditText(item->port);

	if (item->isTopic())
		ui.channelType->setCurrentIndex(TopicIndex);
	else if (item->isQueue())
		ui.channelType->setCurrentIndex(QueueIndex);

	ui.channel->setText(item->channel);
	ui.channelAuto->setCheckable(item->channelAuto);
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
