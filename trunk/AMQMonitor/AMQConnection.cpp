/*
 * AMQConnection.cpp
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#include "AMQConnection.h"
#include "AMQSubscription.h"

AMQConnection::AMQConnection(QObject *parent) :
	QObject(parent), frameSize(0)
{
	// Initialize socket
	socket = new QTcpSocket(this);

	QObject::connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
	QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(socketProcessBuffer()));

	// Initialize loopback
	QObject::connect(this, SIGNAL(receivedFrame(AMQConnectionFrame)), this, SLOT(receiveFrame(AMQConnectionFrame)));

	// Startup offline
	emit stateChanged(Disconnected);
}

AMQConnection::~AMQConnection()
{
	if (socket->isOpen())
		socket->disconnectFromHost();
	emit stateChanged(Disconnected);
}

AMQSubscription *AMQConnection::createSubscription(QString destination)
{
	return createSubscription(destination, QString::null);
}

AMQSubscription *AMQConnection::createSubscription(QString destination, QString selector)
{
	AMQSubscription *subscription = new AMQSubscription(this);
	subscription->setDestination(destination);
	subscription->setSelector(selector);
	return subscription;
}

AMQSubscription *AMQConnection::findSubscriptionById(QString id)
{
	QListIterator<AMQSubscription *> iterator(subscriptions);

	while (iterator.hasNext())
	{
		AMQSubscription *item = iterator.next();

		if (item->getId() != id)
			continue;
		return item;
	}

	return NULL;
}

AMQSubscription *AMQConnection::findSubscription(QString destination)
{
	return findSubscription(destination, QString::null);
}

AMQSubscription *AMQConnection::findSubscription(QString destination, QString selector)
{
	QListIterator<AMQSubscription *> iterator(subscriptions);

	while (iterator.hasNext())
	{
		AMQSubscription *item = iterator.next();

		if (item->getDestination() != destination)
			continue;
		if (item->getSelector() != selector)
			continue;
		return item;
	}

	return NULL;
}

void AMQConnection::socketConnected()
{
	qDebug() << "void AMQConnection::socketConnected()";

	emit
	stateChanged(Connected);
	emit
	stateChanged(Authenticating);

	// Send the authorization frame
	AMQConnectionFrame frame(this);
	frame.setCommandType(AMQConnectionFrame::Connect);
	frame.setUser(QString::null);
	frame.setPassword(QString::null);
	sendFrame(frame);
}

void AMQConnection::socketDisconnected()
{
	emit stateChanged(Disconnected);
}

void AMQConnection::socketError(QTcpSocket::SocketError)
{
}

void AMQConnection::socketProcessBuffer()
{
	// Pull in available data
	buffer += socket->readAll();

	// Setup the content length regex
	QRegExp matcher("content-length:\\s*(\\d+)\n");

	// Loop through the frames
	do
	{
		// Have we already checked for the required minimum frame length?
		if (frameSize && buffer.size() < frameSize)
			return;

		// Is there at least one null byte?
		if (false == buffer.contains('\0'))
			return;

		// Are at least all of the headers present?
		if (false == buffer.contains("\n\n"))
			return;

		// Determine the frame size
		if (matcher.indexIn(QString(buffer)) == -1)
			frameSize = buffer.indexOf('\0') + 1;
		else
			frameSize = buffer.indexOf("\n\n") + 2 + matcher.cap(1).toInt() + 1;

		// Do we have that much data available?
		if (frameSize > buffer.size())
			return;

		// Update the state
		emit
		stateChanged(ReceivingFrame);

		// Initialize the frame
		AMQConnectionFrame frame(this, buffer.left(frameSize));

		// Trim the buffer data
		buffer.remove(0, frameSize);

		// Reset the frame size
		frameSize = 0;

		// Send out the message
		emit
		receivedFrame(frame);

		// Update the state
		emit stateChanged(ReceivedFrame);

		// Done with this frame
	} while (true);
}

void AMQConnection::connectToHost()
{
	emit stateChanged(Connecting);
	socket->connectToHost("localhost", 61613);
}

void AMQConnection::sendFrame(AMQConnectionFrame frame)
{
	qDebug() << "void AMQConnection::sendFrame(AMQConnectionFrame)";

	sendFrameData(frame.toFrame());
	emit sentFrame(frame);

}

void AMQConnection::sendFrameData(QByteArray frameData)
{
	qDebug() << "void AMQConnection::sendFrameData(QByteArray)";
	qDebug() << "\t Frame Data:\n" << frameData;

	emit
	stateChanged(SendingFrame);
	socket->write(frameData);
	emit stateChanged(SentFrame);
}

void AMQConnection::receiveFrame(AMQConnectionFrame frame)
{
	qDebug() << "void AMQConnection::receiveFrame(AMQConnectionFrame)";
	qDebug() << "\t Frame Data:\n" << frame.toFrame();
}

