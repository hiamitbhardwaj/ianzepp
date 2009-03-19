#include "LocationPane.h"
#include "LocationActionAddRemoteHost.h"
#include "LocationActionAddSubscription.h"
#include "LocationActionDelete.h"

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
#ifdef QT_NO_DEBUG
	ui.locationTree->setColumnHidden(LocationItem::IdColumn, true);
#endif
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

void LocationPane::setPropertiesVisible(bool visible)
{
	qDebug() << "LocationPane::setPropertiesVisible(bool visible)";
	ui.propertiesVisible->setChecked(visible);
	ui.propertiesWidget->setVisible(visible);
}

void LocationPane::initializeContextMenu()
{
	qDebug() << "LocationPane::initializeContextMenu()";

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
	qDebug() << "LocationPane::initializeContextDialog()";

	contextDialog = new LocationContextDialog(this);

	// Connect to dialog's signals
	QObject::connect(contextDialog, SIGNAL(createLocation(LocationItem *)), this, SLOT(createLocation(LocationItem *)));
	QObject::connect(contextDialog, SIGNAL(updateLocation(LocationItem *)), this, SLOT(updateLocation(LocationItem *)));
}

QMenu *LocationPane::getRootMenu()
{
	qDebug() << "LocationPane::getRootMenu()";

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
	qDebug() << "LocationPane::getRemoteHostMenu()";

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
	qDebug() << "LocationPane::getSubscriptionMenu()";

	// Current selection
	LocationItem *item = getSelectedItem();
	RemoteBroker *broker = getBroker(item->getParentId());

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
	ui.actionSubscribe->setEnabled(true);
	ui.actionUnsubscribe->setEnabled(true);

	// Done.
	return contextMenu;
}

QMenu *LocationPane::getMessageMenu()
{
	qDebug() << "LocationPane::getMessageMenu()";

	return contextMenu;
}

void LocationPane::action(QAction *action)
{
	qDebug() << "LocationPane::action(QAction *action)";

	if (action == 0)
		return;

	if (action == ui.actionAddRemoteHost)
	{
		LocationActionAddRemoteHost(this);
	}
	else if (action == ui.actionAddSubscription)
	{
		LocationActionAddSubscription(this);
	}
	else if (action == ui.actionDelete)
	{
		LocationActionDelete(this);
	}
	else if (action == ui.actionConnect)
	{
		LocationItem *item = getSelectedItem();
		Q_CHECK_PTR(item);
		Q_CHECK_PTR(item->getRemoteBroker());

		item->setConnectionMode(LocationItem::Attempting);
		item->getRemoteBroker()->connectToHost();

		qDebug() << "\t Attempting connection...";
	}
	else if (action == ui.actionDisconnect)
	{
		LocationItem *item = getSelectedItem();
		Q_CHECK_PTR(item);
		Q_CHECK_PTR(item->getRemoteBroker());

		item->setConnectionMode(LocationItem::Closed);
		item->getRemoteBroker()->disconnectFromHost();
		item->getRemoteBroker()->close();

		qDebug() << "\t Disconnecting...";
	}
	else if (action == ui.actionSubscribe)
	{
	}
	else if (action == ui.actionUnsubscribe)
	{
	}
}

void LocationPane::connectionCreated(RemoteBroker *remoteBroker)
{
	qDebug() << "LocationPane::connectionCreated(RemoteBroker *broker)";
	qDebug() << "\t With Broker:" << remoteBroker;
	qDebug() << "\t Associated Item Id:" << remoteBroker->getItemId();

	Q_CHECK_PTR(remoteBroker);
	Q_CHECK_PTR(getItemById(remoteBroker->getItemId()));

	getItemById(remoteBroker->getItemId())->setConnectionMode(LocationItem::Created);
}

void LocationPane::connectionEstablished(RemoteBroker *remoteBroker)
{
	Q_CHECK_PTR(remoteBroker);
	Q_CHECK_PTR(getItemById(remoteBroker->getItemId()));

	qDebug() << "LocationPane::connectionEstablished(RemoteBroker *remoteBroker)";
	qDebug() << "\t With Broker:" << remoteBroker;
	qDebug() << "\t Associated Item Id:" << remoteBroker->getItemId();

	LocationItem *childItem = 0;
	LocationItem *selectedItem = getItemById(remoteBroker->getItemId());
	selectedItem->setConnectionMode(LocationItem::Established);

	// Find all of the auto-subscribe items
	for (int index = 0; index < selectedItem->childCount(); ++index)
	{
		childItem = (LocationItem *) selectedItem->child(index);

		Q_CHECK_PTR(childItem);

		qDebug() << "\t Child Item:";
		qDebug() << "\t\t Item Id:" << childItem->getId();
		qDebug() << "\t\t Is Subscription:" << childItem->isSubscription();
		qDebug() << "\t\t Is Auto Subscription:" << childItem->isAutoSubscription();
		qDebug() << "\t\t Subscription:" << childItem->getSubscription();

		if (false == childItem->isSubscription() || false == childItem->isAutoSubscription())
			qDebug() << "\t\t Skipping subscription attempt.";
		else
			remoteBroker->setSubscribed(childItem->getSubscription(), true);
	}
}

void LocationPane::connectionClosed(RemoteBroker *remoteBroker)
{
	qDebug() << "LocationPane::connectionClosed(RemoteBroker *remoteBroker)";
	qDebug() << "\t With Broker:" << remoteBroker;
	qDebug() << "\t Associated Item Id: " << remoteBroker->getItemId();

	Q_CHECK_PTR(remoteBroker);
	Q_CHECK_PTR(getItemById(remoteBroker->getItemId()));

	getItemById(remoteBroker->getItemId())->setConnectionMode(LocationItem::Closed);
}

void LocationPane::connectionError(RemoteBroker *remoteBroker, RemoteBroker::SocketError &socketError)
{
	qDebug() << "LocationPane::connectionError(RemoteBroker *remoteBroker, RemoteBroker::SocketError &socketError)";

	Q_CHECK_PTR(remoteBroker);
	Q_CHECK_PTR(getItemById(remoteBroker->getItemId()));

	getItemById(remoteBroker->getItemId())->setConnectionMode(LocationItem::Error);
}

void LocationPane::frameReceived(RemoteBroker *broker, RemoteFrame frame)
{
	qDebug() << "LocationPane::frameReceived(RemoteBroker *remoteBroker, RemoteFrame frame)";
}

void LocationPane::frameSent(RemoteBroker *broker, RemoteFrame frame)
{
	qDebug() << "LocationPane::frameSent(RemoteBroker *remoteBroker, RemoteFrame frame)";

}
