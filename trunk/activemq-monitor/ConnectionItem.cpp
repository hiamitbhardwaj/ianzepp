/*
 * ConnectionItem.cpp
 *
 *  Created on: Mar 19, 2009
 *      Author: izepp
 */

#include "ConnectionItem.h"

ConnectionItem::ConnectionItem(QTreeWidgetItem *parent) :
	QObject(parent->treeWidget()), QTreeWidgetItem(parent)
{
	// Initialize buffers
	buffer = new QByteArray();

	// Initialize socket
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadable()));

	// Initialize timers
	controlTimer = new QTimer(this);
	controlTimer->setInterval(0);
	QObject::connect(controlTimer, SIGNAL(timeout()), this, SLOT(socketReadIntoBuffer()));

	// Initialize state
	setState(ConnectionItem::Disconnected);

	// Initialize icon
	setIcon(0, QIcon(":/resources/icons/bookmark.gif"));
	treeWidget()->expandItem(parent);
}

ConnectionItem::~ConnectionItem()
{
	delete buffer;
}

void ConnectionItem::setState(ConnectionItem::State state)
{
	previousState = currentState;
	currentState = state;
	emit stateChanged(previousState, currentState);
}

void ConnectionItem::setConnected(bool connected)
{
	if (connected == isConnected())
		return;

	if (connected)
	{
		setState(ConnectionItem::Connecting);
		socket->connectToHost(getRemoteHost(), getRemotePort().toUInt());
	}
	else
	{
		setState(ConnectionItem::Disconnecting);
		socket->disconnectFromHost();
	}
}

void ConnectionItem::setSubscribed(QString destination, bool subscribed)
{
	if (subscribed == isSubscribed(destination))
		return;
	if (false == isListening())
		return;

	ConnectionItem::Frame frame;
	frame.setCommand(subscribed ? "SUBSCRIBE" : "UNSUBSCRIBE");
	frame.setHeader("destination", destination);
	sendMessage(frame);

	subscriptions.insert(destination, subscribed);
	emit subscriptionChanged(destination, subscribed);
}

void ConnectionItem::sendMessage(QString destination, QByteArray payload)
{
	ConnectionItem::Frame frame;
	frame.setCommand("MESSAGE");
	frame.setHeader("destination", destination);
	frame.setPayload(payload);
	sendMessage(frame);
}

void ConnectionItem::sendMessage(ConnectionItem::Frame frame)
{
	setState(ConnectionItem::Sending);

	socket->write(frame.toByteArray());
	emit
	messageSent(frame);

	setState(ConnectionItem::Sent);
	setState(ConnectionItem::Listening);
}

void ConnectionItem::socketConnected()
{
	setState(ConnectionItem::Connected);
	setState(ConnectionItem::Authorizing);

	ConnectionItem::Frame frame;
	frame.setCommand("CONNECT");
	sendMessage(frame);
}

void ConnectionItem::socketDisconnected()
{
	setState(ConnectionItem::Disconnected);
	buffer->clear();
	controlTimer->stop();
	subscriptions.clear();
}

void ConnectionItem::socketReadable()
{
	buffer->append(socket->readAll());
	controlTimer->start();
}

void ConnectionItem::socketProcessBuffer()
{
}

