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
#include <QtCore/QObject>
#include <QtCore/QRegExp>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>

#include "AMQConnectionFrame.h"

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

Q_SIGNALS:
	void receivedFrame(AMQConnectionFrame);
	void sentFrame(AMQConnectionFrame);

public Q_SLOTS:
	void connectToHost();
	void sendFrame(AMQConnectionFrame);
	void receiveFrame(AMQConnectionFrame);
	void setSubscribed(QString destination, bool subscribed);
	void setSubscribed(QString destination, QString selector, bool subscribed);

private Q_SLOTS:
	void socketConnected();
	void socketDisconnected();
	void socketError(QTcpSocket::SocketError);
	void socketProcessBuffer();

private:
	QString remoteHost;
	QString remotePort;
	QTcpSocket *socket;
	QByteArray buffer;
	qint32 frameSize;
};

#endif /* AMQCONNECTION_H_ */
