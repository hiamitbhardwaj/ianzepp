/*
 * SubscriptionItem.h
 *
 *  Created on: Mar 19, 2009
 *      Author: izepp
 */

#ifndef SUBSCRIPTIONITEM_H_
#define SUBSCRIPTIONITEM_H_

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUuid>
#include <QtGui/QTreeWidgetItem>
#include "ConnectionItem.h"

class SubscriptionItem: public QObject, public QTreeWidgetItem
{
Q_OBJECT

public:
	SubscriptionItem(ConnectionItem *parent, QString destination);
	virtual ~SubscriptionItem();

	ConnectionItem *getConnectionItem()
	{
		return (ConnectionItem *) ((QObject *) this)->parent();
	}

	QString getDestination() const
	{
		return destination;
	}

	QString getId() const
	{
		return id;
	}

	bool isConnected()
	{
		return getConnectionItem()->isConnected();
	}

	bool isListening()
	{
		return getConnectionItem()->isListening();
	}

	bool isSubscribed()
	{
		return getConnectionItem()->isSubscribed(getDestination());
	}

	bool isAutomatic()
	{
		return automatic;
	}

	void setAutomatic(bool automatic)
	{
		this->automatic = automatic;
	}

	void setSubscribed(bool subscribed)
	{
		getConnectionItem()->setSubscribed(getDestination(), subscribed);

	}

signals:
	void stateChanged(ConnectionItem::State previous, ConnectionItem::State current);

protected slots:
	void connectionStateChanged(ConnectionItem::State previous, ConnectionItem::State current);
	void messageReceived(ConnectionItem::Frame frame);
	void messageSent(ConnectionItem::Frame frame);
	void subscriptionChanged(QString destination, bool subscribed);
	void updateDisplayData();

private:
	QString id;
	QString destination;
	bool automatic;
};

#endif /* SUBSCRIPTIONITEM_H_ */
