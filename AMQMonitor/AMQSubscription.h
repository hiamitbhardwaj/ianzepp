/*
 * AMQSubscription.h
 *
 *  Created on: Mar 21, 2009
 *      Author: Ian Zepp
 */

#ifndef AMQSUBSCRIPTION_H_
#define AMQSUBSCRIPTION_H_

#include <QtCore/QObject>

// Required for slots
#include "AMQConnectionFrame.h"
#include "AMQConnection.h"

class AMQSubscription: public QObject
{
Q_OBJECT

public:
	AMQSubscription(AMQConnection *parent);
	virtual ~AMQSubscription();

	void setSubscribed(bool subscribed);
	void send(QString message);

public:
	bool getAutomatic() const
	{
		return automatic;
	}

	void setAutomatic(bool automatic)
	{
		this->automatic = automatic;
	}

	AMQConnection *getConnection() const
	{
		return connection;
	}

	QString getDestination() const
	{
		return destination;
	}

	void setDestination(QString destination)
	{
		this->destination = destination;
	}

	QString getId() const
	{
		return id;
	}

	void setId(QString id)
	{
		this->id = id;
	}

	bool getAcknowledged() const
	{
		return acknowledged;
	}

	void setAcknowledged(bool acknowledged)
	{
		this->acknowledged = acknowledged;
	}

	QString getSelector() const
	{
		return selector;
	}

	void setSelector(QString selector)
	{
		this->selector = selector;
	}

	bool getSubscribed() const
	{
		return subscribed;
	}

	QString getSubscriptionReceipt() const
	{
		return subscriptionReceipt;
	}

	void setSubscriptionReceipt(QString subscriptionReceipt)
	{
		this->subscriptionReceipt = subscriptionReceipt;
	}

private Q_SLOTS:
	void stateChanged(AMQConnection::ConnectionState);
	void receivedFrame(AMQConnectionFrame);
	void receivedReceiptFrame(AMQConnectionFrame);
	void receivedMessageFrame(AMQConnectionFrame);
	void sentFrame(AMQConnectionFrame);

private:
	AMQConnection *connection;
	QString id;
	QString destination;
	QString selector;
	QString subscriptionReceipt;
	bool automatic;
	bool subscribed;
	bool acknowledged;
};

#endif /* AMQSUBSCRIPTION_H_ */
