#include "LocationContextDialog.h"

LocationContextDialog::LocationContextDialog(QWidget *parent) :
	QDialog(parent), rootItem(0), remoteHostItem(0), subscriptionItem(0), managementRole(Undefined)
{
	ui.setupUi(this);
}

LocationContextDialog::~LocationContextDialog()
{
}

LocationItem *LocationContextDialog::exec()
{
	if (remoteHostItem)
	{
		// Inject values
		ui.remoteHost->setText(remoteHostItem->getRemoteHost());
		ui.autoConnection->setChecked(remoteHostItem->isAutoConnection());

		if (remoteHostItem->isStomp())
		{
			ui.remotePort->setCurrentIndex(StompIndex);
		}
		else if (remoteHostItem->isOpenWire())
		{
			ui.remotePort->setCurrentIndex(OpenWireIndex);
		}
		else if (remoteHostItem->isHttp())
		{
			ui.remotePort->setCurrentIndex(HttpIndex);
		}
		else if (remoteHostItem->isHttps())
		{
			ui.remotePort->setCurrentIndex(HttpsIndex);
		}
		else
		{
			ui.remotePort->setEditText(remoteHostItem->getRemotePort());
		}
	}

	if (subscriptionItem)
	{
		// Inject values
		if (subscriptionItem->isTopic())
		{
			ui.subscriptionType->setCurrentIndex(TopicIndex);
		}
		else if (subscriptionItem->isQueue())
		{
			ui.subscriptionType->setCurrentIndex(QueueIndex);
		}

		ui.subscription->setText(subscriptionItem->getSubscription());
		ui.autoSubscription->setCheckable(subscriptionItem->isAutoSubscription());
	}

	// Set enabled groups
	setRemoteHostGroupEnabled(remoteHostItem == 0);
	setSubscriptionGroupEnabled(remoteHostItem != 0);

	// Can the dialog be accepted?
	updateAcceptable();

	// Set focus
	if (managementRole == AddRemoteHost)
		ui.remoteHost->setFocus();
	else if (managementRole == AddSubscription)
		ui.subscription->setFocus();

	// Call the superclass exec method
	if (QDialog::exec() != QDialog::Accepted)
		return 0;

	// Create a new location item
	LocationItem *item = new LocationItem();
	item->setRemoteHost(ui.remoteHost->text());
	item->setRemotePort(getRemotePort());
	item->setAutoConnection(ui.autoConnection->isChecked());
	item->setSubscription(getSubscription());
	item->setAutoSubscription(ui.autoSubscription->isChecked());

	// Update the visible data
	item->setText(LocationItem::DescriptionColumn, item->getDisplayText());

	// Cleanup
	ui.autoConnection->setChecked(false);
	ui.remoteHost->setText(QString::null);
	ui.remotePort->setEditText(QString::null);
	ui.remotePort->setCurrentIndex(0);
	ui.autoSubscription->setChecked(false);
	ui.subscriptionType->setCurrentIndex(TopicIndex);
	ui.subscription->setText(QString::null);

	// Done.
	return item;
}

void LocationContextDialog::updateAcceptable()
{
	bool enabled = true;

	if (managementRole == AddRemoteHost && ui.remoteHost->text().isEmpty())
	{
		enabled = false;
	}
	else if (managementRole == AddSubscription && ui.subscription->text().isEmpty())
	{
		enabled = false;
	}

	ui.create->setEnabled(enabled);
}

void LocationContextDialog::setRemoteHostGroupEnabled(bool enabled)
{
	ui.remoteHost->setEnabled(enabled);
	ui.remotePort->setEnabled(enabled);
	ui.autoConnection->setEnabled(enabled);
}

void LocationContextDialog::setSubscriptionGroupEnabled(bool enabled)
{
	ui.subscription->setEnabled(enabled);
	ui.subscriptionType->setEnabled(enabled);
	ui.autoSubscription->setEnabled(enabled);
}

QString LocationContextDialog::getRemotePort() const
{
	QString remotePort = ui.remotePort->currentText();

	if (remotePort == "<stomp>" || remotePort.isEmpty())
	{
		return QString::number(LocationItem::Stomp);
	}
	else if (remotePort == "<openwire>")
	{
		return QString::number(LocationItem::OpenWire);
	}
	else if (remotePort == "<http>")
	{
		return QString::number(LocationItem::Http);
	}
	else if (remotePort == "<https>")
	{
		return QString::number(LocationItem::Https);
	}
	else
	{
		return remotePort;
	}
}

QString LocationContextDialog::getSubscription() const
{
	QString subscription = ui.subscription->text();
	QString type = ui.subscriptionType->currentText();

	if (subscription.isEmpty())
		return QString::null;
	else
		return QString("/" + type + "/" + subscription);
}
