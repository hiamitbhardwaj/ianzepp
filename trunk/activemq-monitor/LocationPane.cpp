#include "LocationPane.h"

LocationPane::LocationPane(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	ui.propertiesWidget->setVisible(ui.propertiesVisible->isChecked());

	// Initialize the context menu
	contextMenu = new QMenu(this);
	contextMenu->addAction(ui.actionAddRemoteHost);
	contextMenu->addAction(ui.actionAddSubscription);
	contextMenu->addAction(ui.actionEdit);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionAutoConnection);
	contextMenu->addAction(ui.actionConnect);
	contextMenu->addAction(ui.actionDisconnect);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionAutoSubscription);
	contextMenu->addAction(ui.actionSubscribe);
	contextMenu->addAction(ui.actionUnsubscribe);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionDelete);

	// Initialize the root location item
	rootItem = new LocationItem(ui.locationTree);
	rootItem->setData(LocationItem::DescriptionColumn, Qt::DisplayRole, "Remote Host Connections");
	rootItem->setData(LocationItem::DescriptionColumn, Qt::ToolTipRole, "Right-click to create, edit, or delete connections");
	rootItem->setData(LocationItem::IdColumn, Qt::DisplayRole, "<root>");

	// Tweak the tree
	ui.locationTree->setColumnHidden(LocationItem::IdColumn, true);
}

LocationPane::~LocationPane()
{

}

void LocationPane::contextMenuRequested(const QPoint &pos)
{
	qDebug() << "LocationPane::contextMenuRequested(const QPoint &pos)";

	LocationItem *item = getSelectedItem();
	bool isRemoteHost = item && item->isRemoteHost();
	bool isSubscription = item && item->isSubscription();
	bool isConnected = item && item->getConnected();

	ui.actionAddRemoteHost->setEnabled(item == 0 || item == getRootItem());
	ui.actionAddSubscription->setEnabled(isRemoteHost);
	ui.actionEdit->setEnabled(isRemoteHost || isSubscription);
	ui.actionDelete->setEnabled(isRemoteHost || isSubscription);
	ui.actionConnect->setVisible(isRemoteHost);
	ui.actionConnect->setEnabled(isRemoteHost && !isConnected);
	ui.actionDisconnect->setVisible(isRemoteHost);
	ui.actionDisconnect->setEnabled(isRemoteHost && isConnected);
	ui.actionAutoConnection->setVisible(isRemoteHost);
	ui.actionAutoConnection->setVisible(isRemoteHost);
	ui.actionAutoConnection->setChecked(isRemoteHost && item->getAutoConnection());
	ui.actionSubscribe->setVisible(isSubscription);
	ui.actionSubscribe->setEnabled(isSubscription && !isConnected);
	ui.actionUnsubscribe->setVisible(isSubscription);
	ui.actionUnsubscribe->setEnabled(isSubscription && isConnected);
	ui.actionAutoSubscription->setVisible(isSubscription);
	ui.actionAutoSubscription->setChecked(isSubscription && item->getAutoSubscription());

	// Show the menu and handle the returned action
	action(contextMenu->exec(ui.locationTree->mapToGlobal(pos)));
}

//void LocationPane::createLocation(LocationItem *item)
//{
//	QTreeWidgetItem *treeItem = getTreeItem(item);
//	QString locationId = item->getId();
//
//	if (treeItem)
//	{
//		QString messageTitle = "Error creating new location";
//		QString messageText = "Remote location already exists: " + locationId;
//		QMessageBox::warning(this, messageTitle, messageText);
//		return;
//	}
//
//	// Create the new tree item
//	if (item->isRemoteHost())
//	{
//		treeItem = new QTreeWidgetItem(ui.locationTree);
//
//		//		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getDisplayText());
//	}
//	//	else if (item->isSubscription())
//	//	{
//	//		treeItem = new QTreeWidgetItem(getTreeItem(item->getId(LocationItem::Hostname)));
//	//		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getSubscription());
//	//	}
//
////	treeItem->setData(IdColumn, Qt::DisplayRole, locationId);
//
//	// Register
//	registerLocationItem(locationId, item);
//}
//
//void LocationPane::updateLocation(LocationItem *item)
//{
////	LocationItem *originalItem = getLocationItem(item->getId());
////
////	// Update the display (using the original item id)
////	QTreeWidgetItem *treeItem = getTreeItem(originalItem->getId());
////
////	if (item->isRemoteHost())
////	{
////		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getHostnameUri());
////		treeItem->setData(DescriptionColumn, Qt::ToolTipRole, item->display);
////	}
////	else if (item->isSubscription())
////	{
////		treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->getSubscription());
////	}
////
////	// Change the item id (if needed)
////	if (originalItem->getId() != item->getId())
////	{
////		unregisterLocationItem(originalItem->getId());
////		treeItem->setData(IdColumn, Qt::DisplayRole, item->getId());
////		registerLocationItem(item->getId(), originalItem);
////	}
////
////	// Finally, update the original item with new values
////	originalItem->bytes = item->bytes;
////	originalItem->channel = item->channel;
////	originalItem->channelAuto = item->channelAuto;
////	originalItem->channelType = item->channelType;
////	originalItem->display = item->display;
////	originalItem->hostname = item->hostname;
////	originalItem->hostnameAuto = item->hostnameAuto;
////	originalItem->messages = item->messages;
////	originalItem->port = item->port;
//}

//void LocationPane::updateProperties(QTreeWidgetItem *treeItem)
//{
//	qDebug() << "LocationPane::updateProperties(QTreeWidgetItem *treeItem)";
//	ui.propertiesWidget->updateProperties(getSelectedLocationItem());
//}

void LocationPane::insertItemClicked()
{
	qDebug() << "LocationPane::insertItemClicked()";

}

void LocationPane::removeItemClicked()
{
	qDebug() << "LocationPane::removeItemClicked()";

}

void LocationPane::setPropertiesVisible(bool visible)
{
	ui.propertiesVisible->setChecked(visible);
	ui.propertiesWidget->setVisible(visible);
}

void LocationPane::action(QAction *action)
{
	qDebug() << "LocationPane::action(QAction *action)";

	if (action == 0)
		return;
	if (action == ui.actionAddRemoteHost)
		actionAddRemoteHost();
	else if (action == ui.actionAddSubscription)
		actionAddSubscription();
	else if (action == ui.actionEdit)
		actionEdit();
	else if (action == ui.actionDelete)
		actionDelete();
	else if (action == ui.actionConnect)
		actionConnect();
	else if (action == ui.actionDisconnect)
		actionDisconnect();
	else if (action == ui.actionSubscribe)
		actionSubscribe();
	else if (action == ui.actionUnsubscribe)
		actionUnsubscribe();
}

void LocationPane::actionAddRemoteHost()
{
	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->setParentItem(getRootItem());
	dialog->exec();
}

void LocationPane::actionAddSubscription()
 {
	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->setParentItem(getSelectedItem());
	dialog->exec();
}

void LocationPane::actionEdit()
{
	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->setParentItem(getSelectedItem());
	dialog->exec();
}

void LocationPane::actionDelete()
{
}

void LocationPane::actionConnect()
{
}

void LocationPane::actionDisconnect()
{
}

void LocationPane::actionSubscribe()
{
}

void LocationPane::actionUnsubscribe()
{
}

void LocationPane::actionAutoConnection(bool checked)
{
}

void LocationPane::actionAutoSubscription(bool checked)
{
}

