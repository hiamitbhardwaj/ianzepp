/*
 * RemoteBroker.cpp
 *
 *  Created on: Mar 17, 2009
 *      Author: Ian Zepp
 */

#include "RemoteBroker.h"

RemoteBroker::RemoteBroker(QObject *parent) :
	QTcpSocket(parent), authenticated(false)
{
	qDebug() << "RemoteBroker::RemoteBroker(QObject *parent)";

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
	qDebug() << "RemoteBroker::~RemoteBroker()";
	qDebug() << "\t Connection Created:" << isConnectionCreated();
	qDebug() << "\t Connection Established:" << isConnectionEstablished();

	if (isConnectionEstablished())
		sendFrame(newDisconnectFrame());
	if (isConnectionCreated())
		QTcpSocket::disconnectFromHost();

	delete readBuffer;
}

quint64 RemoteBroker::sendFrame(RemoteFrame frame)
{
	qDebug() << "quint64 RemoteBroker::sendFrame(RemoteFrame frame)";
	qDebug() << "\t Connection Created:" << isConnectionCreated();
	qDebug() << "\t Connection Established:" << isConnectionEstablished();
	qDebug() << "\t Remote Host: " << remoteHost;
	qDebug() << "\t Remote Port: " << remotePort;
	qDebug() << "\t Frame Command & Contents:" << frame.toFrame();

	quint64 bytesWritten = 0;

	if (isConnectionCreated())
	{
		emit frameSent(this, frame);
		bytesWritten = QTcpSocket::write(frame.toFrame());
	}

	qDebug() << "\t Bytes Written: " << bytesWritten;
	return bytesWritten;
}

void RemoteBroker::setSubscribed(const QString &subscription, bool wantsSubscription)
{
	qDebug() << "void RemoteBroker::setSubscribed(const QString &subscription, bool wantsSubscription)";
	qDebug() << "\t Connection Created:" << isConnectionCreated();
	qDebug() << "\t Connection Established:" << isConnectionEstablished();
	qDebug() << "\t Remote Host:" << remoteHost;
	qDebug() << "\t Remote Port:" << remotePort;
	qDebug() << "\t Subscription:" << subscription;
	qDebug() << "\t Wants:" << wantsSubscription;

	if (false == isConnectionEstablished())
		qDebug() << "\t Cannot send subscription frame if not authenticated";
	else if (wantsSubscription)
		sendFrame(newSubscriptionFrame(subscription));
	else
		sendFrame(newUnsubscriptionFrame(subscription));
}

void RemoteBroker::socketCreated()
{
	qDebug() << "void RemoteBroker::socketCreated()";
	qDebug() << "\t Remote Host:" << remoteHost;
	qDebug() << "\t Remote Port:" << remotePort;

	emit
	connectionCreated(this);

	sendFrame(newConnectFrame());
}

void RemoteBroker::socketClosed()
{
	qDebug() << "void RemoteBroker::socketClosed()";
	qDebug() << "\t Remote Host:" << remoteHost;
	qDebug() << "\t Remote Port:" << remotePort;

	emit
	connectionClosed(this);
	readTimer->stop();
	readBuffer->clear();
	authenticated = false;
}

void RemoteBroker::socketError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "void RemoteBroker::socketError(QAbstractSocket::SocketError socketError)";

	emit
	connectionError(this, socketError);
	readTimer->stop();
	readBuffer->clear();
	authenticated = false;
}

void RemoteBroker::socketReadable()
{
	qDebug() << "void RemoteBroker::socketReadable()";
	qDebug() << "\t Remote Host:" << remoteHost;
	qDebug() << "\t Remote Port:" << remotePort;

	readTimer->start();
	readBuffer->append(QTcpSocket::readAll());
}

void RemoteBroker::processSocketBuffer()
{
	qDebug() << "void RemoteBroker::processSocketBuffer()";
	qDebug() << "\t Remote Host:" << remoteHost;
	qDebug() << "\t Remote Port:" << remotePort;

	if (!readBuffer->contains('\0'))
	{
		qDebug() << "\t Missing NULL terminator, returning.";
		return readTimer->stop();
	}

	// Find the message endpoint
	int breakpoint = readBuffer->indexOf('\0');

	qDebug() << "\t Found terminator at offset:" << breakpoint;

	// Extract the frame
	RemoteFrame frame(readBuffer->left(breakpoint));

	qDebug() << "\t Frame Command & Contents: " << frame.toFrame();

	// Parse the incoming frame
	if (frame.getCommand() == "CONNECTED")
	{
		authenticated = true;
		emit connectionEstablished(this);
	}

	// Always send out the frame
	emit frameReceived(this, frame);

	// Clean up the read buffer: The stomp server sends back \0\n instead of just \0
	readBuffer->remove(0, breakpoint + 2);
}
