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

	frame.setId(getId());
	frame.setDestination(getDestination());
	frame.setSelector(getSelector());
	frame.setReceiptRequired(true);

	// Save the receipt token
	setSubscriptionReceipt(frame.getReceipt());

	// Send it.
	frame.send();
}

void AMQSubscription::stateChanged(AMQConnection::ConnectionState)
{

}

void AMQSubscription::receivedFrame(AMQConnectionFrame frame)
{
	if (frame.getDestination() != getDestination())
		return;
	if (frame.getSelector() != getSelector())
		return;

	qDebug() << "void AMQSubscription::setSubscribed(bool)";
	qDebug() << "\t Id:" << frame.getId();
	qDebug() << "\t Destination:" << frame.getDestination();
	qDebug() << "\t Selector:" << frame.getSelector();
	qDebug() << "\t Acknowledged:" << frame.getAcknowledged();

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

	// Acknowledge the message?
	if (getAcknowledged())
		frame.acknowledge();
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
	qDebug() << "void AMQSubscription::receivedReceiptFrame(AMQConnectionFrame)";
	qDebug() << "\t Receipt:" << frame.getReceipt();
	qDebug() << "\t Expected Receipt:" << getSubscriptionReceipt();

	// Only mark subscribed once the subscription receipt comes back
	if (frame.getReceipt() == getSubscriptionReceipt())
		subscribed = true;
}

void AMQSubscription::receivedMessageFrame(AMQConnectionFrame)
{
}

