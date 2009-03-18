/*
 * RemoteBroker.cpp
 *
 *  Created on: Mar 17, 2009
 *      Author: Ian Zepp
 */

#include "RemoteBroker.h"

RemoteBroker::RemoteBroker(QObject *parent) :
	QTcpSocket(parent)
{
	QObject::connect(this, SIGNAL(connected()), this, SLOT(socketCreated()));
	QObject::connect(this, SIGNAL(disconnected()), this, SLOT(socketClosed()));
	QObject::connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
	QObject::connect(this, SIGNAL(readyRead()), this, SLOT(socketReadable()));

	// Setup the read buffer
	readBuffer = new QByteArray();

	// Setup the read buffer timer
	readTimer = new QTimer(this);
	readTimer->setInterval(0); // fire when event queue is idle
	QObject::connect(readTimer, SIGNAL(timeout()), this, SLOT(processSocketBuffer()));
}

RemoteBroker::~RemoteBroker()
{
	if (isConnectionEstablished())
		sendFrame(newDisconnectFrame());
	if (isConnectionCreated())
		QTcpSocket::disconnectFromHost();

	delete readBuffer;
}

quint64 RemoteBroker::sendFrame(RemoteFrame frame)
{
	emit frameSent(this, frame);
	return QTcpSocket::write(frame.toFrame());
}

void RemoteBroker::setSubscribed(const QString &subscription, bool wantsSubscription)
{
	if (isConnectionEstablished() == false)
		return;

	bool alreadySubscribed = isSubscribed(subscription);

	if (wantsSubscription && !alreadySubscribed)
		sendFrame(newSubscriptionFrame(subscription));
	else if (!wantsSubscription && alreadySubscribed)
		sendFrame(newUnsubscriptionFrame(subscription));
}

void RemoteBroker::socketCreated ()
{
	emit connectionCreated (this);
}

void RemoteBroker::socketClosed ()
{
	emit connectionClosed (this);
	readTimer->stop ();
	readBuffer->clear ();
}

void RemoteBroker::socketError (QAbstractSocket::SocketError &socketError)
{
	emit connectionError (this, socketError);
	readTimer->stop ();
	readBuffer->clear ();
}

void RemoteBroker::socketReadable ()
{
	readTimer->start ();
	readBuffer->append (QTcpSocket::readAll ());
}

void RemoteBroker::processSocketBuffer ()
{
	if (!readBuffer->contains ('\0')) {
		return readTimer->stop ();
	}

	// Find the message endpoint
	int breakpoint = readBuffer->indexOf ('\0');

	// Parse the incoming frame
	emit frameReceived (this, RemoteFrame (readBuffer->left (breakpoint)));

	// Clean up the read buffer: The stomp server sends back \0\n instead of just \0
	readBuffer->remove (0, breakpoint + 2);
}
