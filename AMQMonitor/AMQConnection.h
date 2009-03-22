/*
 * AMQConnection.h
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#ifndef AMQCONNECTION_H_
#define AMQCONNECTION_H_

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QRegExp>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>

// Required for slots
#include "AMQConnectionFrame.h"

// Forward declarations
class AMQSubscription;

class AMQConnection: public QObject
{
Q_OBJECT

public:
	enum ConnectionState
	{
		Connecting,
		Connected,
		Authenticating,
		Authenticated,
		Listening,
		ReceivingFrame,
		ReceivedFrame,
		SendingFrame,
		SentFrame,
		Disconnecting,
		Disconnected
	};

public:
	AMQConnection(QObject *parent);
	virtual ~AMQConnection();

	AMQSubscription *createSubscription(QString destination);
	AMQSubscription *createSubscription(QString destination, QString selector);
	AMQSubscription *findSubscriptionById(QString id);
	AMQSubscription *findSubscription(QString destination);
	AMQSubscription *findSubscription(QString destination, QString selector);

Q_SIGNALS:
	void stateChanged(AMQConnection::ConnectionState);
	void receivedFrame(AMQConnectionFrame);
	void sentFrame(AMQConnectionFrame);

public Q_SLOTS:
	void connectToHost();
	void sendFrame(AMQConnectionFrame);
	void receiveFrame(AMQConnectionFrame);

private Q_SLOTS:
	void socketConnected();
	void socketDisconnected();
	void socketError(QTcpSocket::SocketError);
	void socketProcessBuffer();

	void receiveQueueTimeout();
	void sendQueueTimeout();
	void sendQueueFrame(AMQConnectionFrame);

private:
	QList<AMQSubscription *> subscriptions;
	QList<AMQConnectionFrame> receiveQueue;
	QList<AMQConnectionFrame> sendQueue;
	QTimer *receiveTimer;
	QTimer *sendTimer;
	QString remoteHost;
	QString remotePort;
	QTcpSocket *socket;
	QByteArray buffer;
	qint32 frameSize;
};

#endif /* AMQCONNECTION_H_ */
