#include "LocationPane.h"

LocationPane::LocationPane(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	ui.propertiesWidget->setVisible(ui.propertiesVisible->isChecked());

	// Initialize the context menu
	contextMenu = new QMenu(this);
	contextMenu->addAction(ui.actionCreateLocation);
	contextMenu->addAction(ui.actionCreateChannel);
	contextMenu->addAction(ui.actionEdit);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionHostnameAuto);
	contextMenu->addAction(ui.actionConnect);
	contextMenu->addAction(ui.actionDisconnect);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionChannelAuto);
	contextMenu->addAction(ui.actionSubscribe);
	contextMenu->addAction(ui.actionUnsubscribe);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionDelete);

	// Tweak the tree
	ui.locationTree->setColumnHidden(IdColumn, true);
}

LocationPane::~LocationPane()
{

}

void LocationPane::contextMenuRequested(const QPoint &pos)
{
	qDebug() << "LocationPane::contextMenuRequested(const QPoint &pos)";

	LocationItem *item = getSelectedLocationItem();
	bool isRemoteHost = item && item->isRemoteHost();
	bool isSubscription = item && item->isSubscription();

	ui.actionCreateLocation->setEnabled(item == 0);
	ui.actionCreateChannel->setEnabled(isRemoteHost);
	ui.actionEdit->setEnabled(isRemoteHost || isSubscription);
	ui.actionDelete->setEnabled(isRemoteHost || isSubscription);
	ui.actionConnect->setVisible(isRemoteHost);
	ui.actionConnect->setEnabled(isRemoteHost && false == item->connected);
	ui.actionDisconnect->setVisible(isRemoteHost);
	ui.actionDisconnect->setEnabled(isRemoteHost && item->connected);
	ui.actionHostnameAuto->setVisible(isRemoteHost);
	ui.actionHostnameAuto->setVisible(isRemoteHost);
	ui.actionHostnameAuto->setChecked(isRemoteHost && item->hostnameAuto);
	ui.actionSubscribe->setVisible(isSubscription);
	ui.actionSubscribe->setEnabled(isSubscription && false == item->connected);
	ui.actionUnsubscribe->setVisible(isSubscription);
	ui.actionUnsubscribe->setEnabled(isSubscription && item->connected);
	ui.actionChannelAuto->setVisible(isSubscription);
	ui.actionChannelAuto->setChecked(isSubscription && item->channelAuto);
	actionTriggered(contextMenu->exec(ui.locationTree->mapToGlobal(pos)));
}

void LocationPane::createLocation(LocationItem *item)
{
	QTreeWidgetItem *treeItem = getTreeItem(item);
	QString locationId = item->getId();

	if (treeItem)
	{
		QString messageTitle = "Error creating new location";
		QString messageText = "Remote location already exists: " + locationId;
		QMessageBox::warning(this, messageTitle, messageText);
		return;
	}

	// Create the new tree item
	if (item->isRemoteHost())
	{
		treeItem = new QTreeWidgetItem(ui.locationTree);
		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getHostnameUri());
		treeItem->setData(DescriptionColumn, Qt::ToolTipRole, item->display);
	}
	else if (item->isSubscription())
	{
		treeItem = new QTreeWidgetItem(getTreeItem(item->getId(LocationItem::Hostname)));
		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getSubscription());
	}

	treeItem->setData(IdColumn, Qt::DisplayRole, locationId);

	// Register
	registerLocationItem(locationId, item);
}

void LocationPane::updateLocation(LocationItem *item)
{
	LocationItem *originalItem = getLocationItem(item->getId());

	// Update the display (using the original item id)
	QTreeWidgetItem *treeItem = getTreeItem(originalItem->getId());

	if (item->isRemoteHost())
	{
		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getHostnameUri());
		treeItem->setData(DescriptionColumn, Qt::ToolTipRole, item->display);
	}
	else if (item->isSubscription())
	{
		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getSubscription());
	}

	// Change the item id (if needed)
	if (originalItem->getId() != item->getId())
	{
		unregisterLocationItem(originalItem->getId());
		treeItem->setData(IdColumn, Qt::DisplayRole, item->getId());
		registerLocationItem(item->getId(), originalItem);
	}

	// Finally, update the original item with new values
	originalItem->bytes = item->bytes;
	originalItem->channel = item->channel;
	originalItem->channelAuto = item->channelAuto;
	originalItem->channelType = item->channelType;
	originalItem->display = item->display;
	originalItem->hostname = item->hostname;
	originalItem->hostnameAuto = item->hostnameAuto;
	originalItem->messages = item->messages;
	originalItem->port = item->port;
}

void LocationPane::updateProperties(QTreeWidgetItem *treeItem)
{
	qDebug() << "LocationPane::updateProperties(QTreeWidgetItem *treeItem)";
	ui.propertiesWidget->updateProperties(getSelectedLocationItem());
}

void LocationPane::insertItemClicked()
{
	qDebug() << "LocationPane::insertItemClicked()";

}

void LocationPane::removeItemClicked()
{
	qDebug() << "LocationPane::removeItemClicked()";

}

void LocationPane::actionHovered(QAction *action)
{

}

void LocationPane::setPropertiesVisible(bool visible)
{
	ui.propertiesVisible->setChecked(visible);
	ui.propertiesWidget->setVisible(visible);
}

void LocationPane::actionTriggered(QAction *action)
{
	qDebug() << "LocationPane::actionTriggered(QAction *action)";

	if (action == 0)
		return;
	if (action == ui.actionCreateLocation)
		handleCreateLocation();
	else if (action == ui.actionCreateChannel)
		handleCreateChannel();
	else if (action == ui.actionEdit)
		handleEdit();
	else if (action == ui.actionDelete)
		handleDelete();
	else if (action == ui.actionConnect)
		handleConnect();
	else if (action == ui.actionDisconnect)
		handleDisconnect();
	else if (action == ui.actionSubscribe)
		handleSubscribe();
	else if (action == ui.actionUnsubscribe)
		handleUnsubscribe();
}

void LocationPane::handleCreateLocation()
{
	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->setChannelVisible(false);
	dialog->setMessageVisible(false);
	dialog->exec();
}

void LocationPane::handleCreateChannel()
{
	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->populate(getSelectedLocationItem());
	dialog->setLocationEnabled(false);
	dialog->setChannelEnabled(true);
	dialog->setChannelVisible(true);
	dialog->setMessageVisible(false);
	dialog->exec();
}

void LocationPane::handleEdit()
{
	LocationItem *item = getSelectedLocationItem();
	bool isRemoteHost = item && item->isRemoteHost();
	bool isSubscription = item && item->isSubscription();

	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->populate(getSelectedLocationItem());
	dialog->setLocationEnabled(isRemoteHost);
	dialog->setChannelEnabled(false == isRemoteHost && isSubscription);
	dialog->setChannelVisible(false == isRemoteHost && isSubscription);
	dialog->setMessageVisible(false);
	dialog->setAcceptSignal(LocationCreateDialog::Update);
	dialog->exec();
}

void LocationPane::handleDelete()
{
}

void LocationPane::handleConnect()
{
}

void LocationPane::handleDisconnect()
{
}

void LocationPane::handleSubscribe()
{
}

void LocationPane::handleUnsubscribe()
{
}

void LocationPane::handleAutomaticallyConnect(bool checked)
{
}

void LocationPane::handleAutomaticallySubscribe(bool checked)
{
}

