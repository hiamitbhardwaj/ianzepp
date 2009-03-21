/*
 * AMQSubscription.cpp
 *
 *  Created on: Mar 21, 2009
 *      Author: Ian Zepp
 */

#include "AMQSubscription.h"

AMQSubscription::AMQSubscription(AMQConnection *parent) :
	QObject(parent), automatic(false), subscribed(false), acknowledged(false)
{
	// Initialize the parent connection
	this->connection = parent;

	QObject::connect(parent, SIGNAL(stateChanged(AMQConnection::ConnectionState)), this,
			SLOT(stateChanged(AMQConnection::ConnectionState)));
	QObject::connect(parent, SIGNAL(receivedFrame(AMQConnectionFrame)), this, SLOT(receivedFrame(AMQConnectionFrame)));
	QObject::connect(parent, SIGNAL(sentFrame(AMQConnectionFrame)), this, SLOT(sentFrame(AMQConnectionFrame)));
}

AMQSubscription::~AMQSubscription()
{
}

void AMQSubscription::setSubscribed(bool subscribed)
{
	qDebug() << "void AMQSubscription::setSubscribed(bool)";
	qDebug() << "\t Id:" << getId();
	qDebug() << "\t Destination:" << getDestination();
	qDebug() << "\t Selector:" << getSelector();
	qDebug() << "\t Acknowledged:" << getAcknowledged();
	qDebug() << "\t Subscribed:" << subscribed;

	if (this->subscribed == subscribed)
		return;

	AMQConnectionFrame frame(getConnection());

	if (subscribed)
		frame.setCommandType(AMQConnectionFrame::Subscribe);
	else
		frame.setCommandType(AMQConnectionFrame::Unsubscribe);

	if (false == getId().isEmpty())
		frame.setId(getId());
	if (false == getSelector().isEmpty())
		frame.setSelector(getSelector());

	frame.setDestination(getDestination());
	frame.setReceiptRequired(true);

	// Save the receipt token
	setSubscriptionReceipt(frame.getReceipt());

	// Send it.
	frame.send();
}

void AMQSubscription::send(QString message)
{
	AMQConnectionFrame frame(getConnection());
	frame.setCommandType(AMQConnectionFrame::Send);
	frame.setDestination(getDestination());
	frame.setPayload(message.toUtf8());
	frame.send();
}

void AMQSubscription::stateChanged(AMQConnection::ConnectionState state)
{
	if (state == AMQConnection::Authenticated && getAutomatic())
		setSubscribed(true);
}

void AMQSubscription::receivedFrame(AMQConnectionFrame frame)
{
	// TODO message processing
	switch (frame.getCommandType())
	{
	case AMQConnectionFrame::Receipt:
		receivedReceiptFrame(frame);
		break;

	case AMQConnectionFrame::Message:
		receivedMessageFrame(frame);
		break;

	default:
		break;
	}
}

void AMQSubscription::sentFrame(AMQConnectionFrame frame)
{
	if (frame.getCommandType() == AMQConnectionFrame::Disconnect)
		subscribed = false;
	if (frame.getCommandType() != AMQConnectionFrame::Unsubscribe)
		return;
	if (frame.getDestination() != getDestination())
		return;
	if (frame.getSelector() != getSelector())
		return;

	// Mark as unsubscribed
	subscribed = false;
}

void AMQSubscription::receivedReceiptFrame(AMQConnectionFrame frame)
{
	if (frame.getReceipt() != getSubscriptionReceipt())
		return;

	qDebug() << "void AMQSubscription::receivedReceiptFrame(AMQConnectionFrame)";
	qDebug() << "\t Receipt:" << frame.getReceipt();
	qDebug() << "\t Expected Receipt:" << getSubscriptionReceipt();
	qDebug() << "\t Subscribed To:" << getDestination();

	// Only mark subscribed once the subscription receipt comes back
	subscribed = true;

	// Send a message
	send("Hello World!");
}

void AMQSubscription::receivedMessageFrame(AMQConnectionFrame frame)
{
	if (frame.getDestination() != getDestination())
		return;

	qDebug() << "void AMQSubscription::receivedMessageFrame(AMQConnectionFrame)";
	qDebug() << "\t Subscribed To:" << frame.getDestination();
	qDebug() << "\t Message Id:" << frame.getMessageId();

}

