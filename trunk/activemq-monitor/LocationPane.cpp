#include "LocationPane.h"

LocationPane::LocationPane(QWidget *parent) :
	QWidget(parent), rootItem(0), contextDialog(0), contextMenu(0)
{
	ui.setupUi(this);
	ui.propertiesWidget->setVisible(ui.propertiesVisible->isChecked());

	initializeContextDialog();
	initializeContextMenu();

	// Initialize the root location item
	rootItem = new LocationItem();
	rootItem->setData(LocationItem::DescriptionColumn, Qt::DisplayRole, "Remote Host Connections");
	rootItem->setData(LocationItem::DescriptionColumn, Qt::ToolTipRole, "Right-click to manage connections");
	rootItem->setData(LocationItem::IdColumn, Qt::DisplayRole, "<root>");
	ui.locationTree->addTopLevelItem(rootItem);

	// Tweak the tree
	ui.locationTree->setColumnHidden(LocationItem::IdColumn, true);
}

LocationPane::~LocationPane()
{
}

void LocationPane::contextMenuRequested(const QPoint &pos)
{
	qDebug() << "LocationPane::contextMenuRequested(const QPoint &pos)";

	QMenu *menu = 0;
	LocationItem *item = getSelectedItem();

	if (item && item->isSubscription())
		menu = getSubscriptionMenu();
	else if (item && item->isRemoteHost())
		menu = getRemoteHostMenu();
	else
		menu = getRootMenu();

	// Show the menu and handle the returned action
	action(menu->exec(ui.locationTree->mapToGlobal(pos)));
}

void LocationPane::addingRemoteHost(LocationItem *item)
{

}

void LocationPane::addingSubscription(LocationItem *item)
{

}

void LocationPane::setPropertiesVisible(bool visible)
{
	ui.propertiesVisible->setChecked(visible);
	ui.propertiesWidget->setVisible(visible);
}

void LocationPane::connectionCreated(RemoteBroker *broker)
{

}

void LocationPane::connectionEstablished(RemoteBroker *broker)
{

}

void LocationPane::connectionError(RemoteBroker *broker, RemoteBroker::SocketError &socketError)
{

}

void LocationPane::connectionClosed(RemoteBroker *broker)
{

}

void LocationPane::frameReceived(RemoteBroker *broker, RemoteFrame *frame)
{

}

void LocationPane::frameSent(RemoteBroker *broker, RemoteFrame *frame)
{

}

void LocationPane::initializeContextMenu()
{
	contextMenu = new QMenu(this);

	contextMenu->addAction(ui.actionAddRemoteHost);
	contextMenu->addAction(ui.actionAddSubscription);
	contextMenu->addAction(ui.actionEdit);
	contextMenu->addAction(ui.actionDelete);

	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionAutoConnection);
	contextMenu->addAction(ui.actionConnect);
	contextMenu->addAction(ui.actionDisconnect);

	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionAutoSubscription);
	contextMenu->addAction(ui.actionSubscribe);
	contextMenu->addAction(ui.actionUnsubscribe);
}

void LocationPane::initializeContextDialog()
{
	contextDialog = new LocationContextDialog(this);

	// Connect to dialog's signals
	connect(contextDialog, SIGNAL(createLocation(LocationItem *)), this, SLOT(createLocation(LocationItem *)));
	connect(contextDialog, SIGNAL(updateLocation(LocationItem *)), this, SLOT(updateLocation(LocationItem *)));
}

QMenu *LocationPane::getRootMenu()
{
	// QMessageBox::information(this, "Debug", "LocationPane::getRootMenu()");

	ui.actionAddRemoteHost->setEnabled(true);
	ui.actionAddSubscription->setEnabled(false);
	ui.actionEdit->setEnabled(false);
	ui.actionDelete->setEnabled(false);

	// Enabled? : Remote Host Menu
	ui.actionAutoConnection->setEnabled(false);
	ui.actionConnect->setEnabled(false);
	ui.actionDisconnect->setEnabled(false);

	// Enabled? : Subscription Menu
	ui.actionAutoSubscription->setEnabled(false);
	ui.actionSubscribe->setEnabled(false);
	ui.actionUnsubscribe->setEnabled(false);

	// Done.
	return contextMenu;
}

QMenu *LocationPane::getRemoteHostMenu()
{
	// QMessageBox::information(this, "Debug", "LocationPane::getRemoteHostMenu()");

	// Current selection
	LocationItem *item = getSelectedItem();
	RemoteBroker *broker = getBroker(item->getId());

	// Predetermine
	bool isConnected = broker->isConnectionEstablished();

	// Enabled? Root level options
	ui.actionAddRemoteHost->setEnabled(false);
	ui.actionAddSubscription->setEnabled(true);
	ui.actionEdit->setEnabled(true);
	ui.actionDelete->setEnabled(true);

	// Enabled? : Remote Host Menu
	ui.actionAutoConnection->setEnabled(true);
	ui.actionAutoConnection->setChecked(item->isAutoConnection());
	ui.actionConnect->setEnabled(!isConnected);
	ui.actionDisconnect->setEnabled(isConnected);

	// Enabled? : Subscription Menu
	ui.actionAutoSubscription->setEnabled(false);
	ui.actionSubscribe->setEnabled(isConnected);
	ui.actionUnsubscribe->setEnabled(false);

	// Done.
	return contextMenu;
}

QMenu *LocationPane::getSubscriptionMenu()
{
	// Current selection
	LocationItem *item = getSelectedItem();
	RemoteBroker *broker = getBroker(item->getParentId());

	// Predetermine
	bool isSubscribed = broker->isSubscribed(item->getSubscription());

	// Enabled? Root level options
	ui.actionAddRemoteHost->setEnabled(false);
	ui.actionAddSubscription->setEnabled(false);
	ui.actionEdit->setEnabled(true);
	ui.actionDelete->setEnabled(true);

	// Enabled? : Remote Host Menu
	ui.actionAutoConnection->setEnabled(false);
	ui.actionAutoConnection->setChecked(item->isAutoConnection());
	ui.actionConnect->setEnabled(false);
	ui.actionDisconnect->setEnabled(false);

	// Enabled? : Subscription Menu
	ui.actionAutoSubscription->setEnabled(true);
	ui.actionAutoSubscription->setChecked(item->isAutoSubscription());
	ui.actionSubscribe->setEnabled(isSubscribed == false);
	ui.actionUnsubscribe->setEnabled(isSubscribed);

	// Done.
	return contextMenu;
}

QMenu *LocationPane::getMessageMenu()
{
	return contextMenu;
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
	getContextDialog()->setRootItem(getRootItem());
	getContextDialog()->setRemoteHostItem(0);
	getContextDialog()->setSubscriptionItem(0);
	getContextDialog()->setManagementRole(LocationContextDialog::AddRemoteHost);

	// Add the remote host
	LocationItem *item = getContextDialog()->exec();

	// If there was no response object, the item doesn't need to be created
	if (item == 0)
		return;

	// Does this name already exist in the tree?
	// TODO

	// Create a new network connection
	RemoteBroker *remoteBroker = new RemoteBroker(this);
	remoteBroker->setRemoteHost(item->getRemoteHost());
	remoteBroker->setRemotePort(item->getRemotePort());

	// Register
	insertBroker(item->getId(), remoteBroker);

	// Save the broker in the item
	item->setRemoteBroker(remoteBroker);

	// Add to tree
	getRootItem()->addChild(item);

	// Expand the node
	ui.locationTree->expandItem(getRootItem());
}

void LocationPane::actionAddSubscription()
{
	getContextDialog()->setRootItem(getRootItem());
	getContextDialog()->setRemoteHostItem(getSelectedItem());
	getContextDialog()->setSubscriptionItem(0);
	getContextDialog()->setManagementRole(LocationContextDialog::AddSubscription);

	// Add the subscription
	LocationItem *item = getContextDialog()->exec();

	// If there was no response object, the item doesn't need to be created
	if (item == 0)
		return;

	// Does this name already exist in the tree?
	// TODO

	// Save the broker in the item
	item->setRemoteBroker(getSelectedItem()->getRemoteBroker());

	// Add to tree
	getSelectedItem()->addChild(item);

	// Expand the node
	ui.locationTree->expandItem(getRootItem());
	ui.locationTree->expandItem(getSelectedItem());
}

void LocationPane::actionEdit()
{
}

void LocationPane::actionDelete()
{
	LocationItem *item = getSelectedItem();
	RemoteBroker *broker = item->getRemoteBroker();
	bool isRemoteHost = item->isRemoteHost();

	// Questions
	QString title = "Delete " + item->getDisplayText() + "?";
	QString message = "Are you sure?";

	if (QMessageBox::question(this, title, message) != QMessageBox::Ok)
		return;

	// If a remote host, remove from the broker list
	if (isRemoteHost)
		removeBroker(item->getId());

	// Delete the item, this will auto-unsubscribe if a subscription
	delete item;

	// Delete the broker, this will auto-disconnect (now that final messages have been sent)
	if (isRemoteHost)
		delete broker;
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

