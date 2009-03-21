/*
 * SubscriptionItem.cpp
 *
 *  Created on: Mar 19, 2009
 *      Author: izepp
 */

#include "SubscriptionItem.h"

SubscriptionItem::SubscriptionItem(ConnectionItem *parent, QString destination) :
	QObject(parent), QTreeWidgetItem(parent), automatic(false)
{
	// Save destination
	this->destination = destination;

	// Initialize ID
	this->id = QUuid::createUuid().toString();

	// Connect to parent
	QObject::connect(parent, SIGNAL(messageReceived(ConnectionItem::Frame)), this, SLOT(messageReceived(ConnectionItem::Frame)));
	QObject::connect(parent, SIGNAL(messageSent(ConnectionItem::Frame)), this, SLOT(messageSent(ConnectionItem::Frame)));
	QObject::connect(parent, SIGNAL(stateChanged(ConnectionItem::State, ConnectionItem::State)), this,
			SLOT(connectionStateChanged(ConnectionItem::State, ConnectionItem::State)));
	QObject::connect(parent, SIGNAL(stateChanged(ConnectionItem::State, ConnectionItem::State)), this,
			SIGNAL(stateChanged(ConnectionItem::State, ConnectionItem::State)));
	QObject::connect(parent, SIGNAL(subscriptionChanged(QString, bool)), this, SLOT(subscriptionChanged(QString, bool)));

	// Final UI setup
	updateDisplayData();

	setData(0, Qt::DisplayRole, destination);
	setIcon(0, QIcon(":/resources/icons/entry_org.gif"));
	setExpanded(true);
}

SubscriptionItem::~SubscriptionItem()
{
}

void SubscriptionItem::connectionStateChanged(ConnectionItem::State, ConnectionItem::State)
{
}

void SubscriptionItem::messageReceived(ConnectionItem::Frame)
{

}

void SubscriptionItem::messageSent(ConnectionItem::Frame)
{

}

void SubscriptionItem::subscriptionChanged(QString destination, bool)
{
	if (getDestination() == destination)
		updateDisplayData();
}

void SubscriptionItem::updateDisplayData()
{
	// Set the tooltip
	if (isSubscribed())
		setData(0, Qt::ToolTipRole, "Subscribed and listening for messages...");
	else if (isListening())
		setData(0, Qt::ToolTipRole, "Not subscribed (connection is up, though)");
	else if (isConnected())
		setData(0, Qt::ToolTipRole, "Not subscribed (connection is up, but not yet authorized)");
	else
		setData(0, Qt::ToolTipRole, "Not subscribed (connection is down");
}
