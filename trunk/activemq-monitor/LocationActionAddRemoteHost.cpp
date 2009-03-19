/*
 * LocationActionAddRemoteHost.cpp
 *
 *  Created on: Mar 18, 2009
 *      Author: Ian Zepp
 */

#include "LocationActionAddRemoteHost.h"
#include "LocationContextDialog.h"
#include "LocationItem.h"
#include "RemoteBroker.h"
#include "RemoteFrame.h"

LocationActionAddRemoteHost::LocationActionAddRemoteHost(LocationPane *locationPane)
{
	qDebug() << "LocationActionAddRemoteHost::LocationActionAddRemoteHost(LocationPane *locationPane)";
	qDebug() << "\t Using Pane:" << locationPane;

	Q_CHECK_PTR(locationPane);

	LocationContextDialog *contextDialog = locationPane->getContextDialog();
	LocationItem *rootItem = locationPane->getRootItem();
	LocationItem *selectedItem = 0;
	LocationItem *subscriptionItem = 0;
	LocationItem *returnedItem = 0;

	Q_CHECK_PTR(rootItem);

	contextDialog->setRootItem(rootItem);
	contextDialog->setRemoteHostItem(selectedItem);
	contextDialog->setSubscriptionItem(subscriptionItem);
	contextDialog->setManagementRole(LocationContextDialog::AddRemoteHost);

	// Add the remote host
	returnedItem = contextDialog->exec();

	// If there was no response object, the item doesn't need to be created
	if (returnedItem == 0)
		return;

	qDebug() << "\t Created new item:";
	qDebug() << "\t\t Item Id:" << returnedItem->getId();
	qDebug() << "\t\t Remote Host:" << returnedItem->getRemoteHost();
	qDebug() << "\t\t Remote Port:" << returnedItem->getRemotePort();
	qDebug() << "\t\t Auto Connection:" << returnedItem->isAutoConnection();

	// Does this name already exist in the tree?
	// TODO

	// Create a new network connection
	RemoteBroker *remoteBroker = new RemoteBroker(locationPane);
	remoteBroker->setRemoteHost(returnedItem->getRemoteHost());
	remoteBroker->setRemotePort(returnedItem->getRemotePort());
	remoteBroker->setItemId(returnedItem->getId());

	qDebug() << "\t Created associated remote broker";

	// Connect the broker slots
	QObject::connect(remoteBroker, SIGNAL(connectionCreated(RemoteBroker *)),
	locationPane, SLOT(connectionCreated(RemoteBroker *)));

	QObject::connect(remoteBroker, SIGNAL(connectionEstablished(RemoteBroker *)),
	locationPane, SLOT(connectionEstablished(RemoteBroker *)));

	QObject::connect(remoteBroker, SIGNAL(connectionClosed(RemoteBroker *)),
	locationPane, SLOT(connectionClosed(RemoteBroker *)));

	QObject::connect(remoteBroker, SIGNAL(connectionError(RemoteBroker *, RemoteBroker::SocketError &)),
	locationPane, SLOT(connectionError(RemoteBroker *, RemoteBroker::SocketError &)));

	QObject::connect(remoteBroker, SIGNAL(frameReceived(RemoteBroker *, RemoteFrame)),
	locationPane, SLOT(frameReceived(RemoteBroker *, RemoteFrame)));

	QObject::connect(remoteBroker, SIGNAL(frameSent(RemoteBroker *, RemoteFrame)),
	locationPane, SLOT(frameSent(RemoteBroker *, RemoteFrame)));

	// Register
	returnedItem->setRemoteBroker(remoteBroker);
	locationPane->insertBroker(returnedItem->getId(), remoteBroker);

	// Add to tree
	rootItem->addChild(returnedItem);
}

LocationActionAddRemoteHost::~LocationActionAddRemoteHost()
{
	// TODO Auto-generated destructor stub
}
