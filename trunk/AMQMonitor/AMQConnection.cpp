/*
 * AMQConnection.cpp
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#include "AMQConnection.h"

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
}

AMQConnection::~AMQConnection()
{
	if (socket->isOpen())
		socket->disconnectFromHost();
}

void AMQConnection::socketConnected()
{
	qDebug() << "void AMQConnection::socketConnected()";

	// Send the authorization frame
	AMQConnectionFrame frame(this);
	frame.setCommandType(AMQConnectionFrame::Connect);
	frame.setUser(QString::null);
	frame.setPassword(QString::null);
	sendFrame(frame);
}

void AMQConnection::socketDisconnected()
{
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

		// Initialize the frame
		AMQConnectionFrame frame(this, buffer.left(frameSize));

		// Trim the buffer data
		buffer.remove(0, frameSize);

		// Reset the frame size
		frameSize = 0;

		// Change states & send out the message
		emit receivedFrame(frame);

		// Done with this frame
	} while (true);
}

void AMQConnection::connectToHost()
{
	socket->connectToHost("localhost", 61613);
}

void AMQConnection::sendFrame(AMQConnectionFrame frame)
{
	qDebug() << "void AMQConnection::sendFrame(AMQConnectionFrame)";
	qDebug() << "\t Frame Data:\n" << frame.toFrame();

	socket->write(frame.toFrame());
	emit sentFrame(frame);
}

void AMQConnection::receiveFrame(AMQConnectionFrame frame)
{
	qDebug() << "void AMQConnection::receiveFrame(AMQConnectionFrame)";
	qDebug() << "\t Frame Data:\n" << frame.toFrame();
}

void AMQConnection::setSubscribed(QString destination, bool subscribed)
{
	setSubscribed(destination, QString::null, subscribed);
}

void AMQConnection::setSubscribed(QString destination, QString selector, bool subscribed)
{
	qDebug() << "void AMQConnection::setSubscribed(QString, QString, bool)";
	qDebug() << "\t Destination:" << destination;
	qDebug() << "\t Selector:" << selector;
	qDebug() << "\t Subscribed:" << subscribed;

	AMQConnectionFrame frame(this);

	if (subscribed)
		frame.setCommandType(AMQConnectionFrame::Subscribe);
	else
		frame.setCommandType(AMQConnectionFrame::Unsubscribe);

	frame.setDestination(destination);
	frame.setSelector(selector);
	frame.setReceiptRequired(true);

	sendFrame(frame);
}

