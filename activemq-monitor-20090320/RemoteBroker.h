/*
 * RemoteBroker.h
 *
 *  Created on: Mar 17, 2009
 *      Author: Ian Zepp
 */

#ifndef REMOTEBROKER_H_
#define REMOTEBROKER_H_

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
#include "RemoteFrame.h"

class RemoteBroker: public QTcpSocket
{
Q_OBJECT

public:
	RemoteBroker(QObject *parent = 0);
	virtual ~RemoteBroker();

	quint64 sendFrame(RemoteFrame frame);
	void setSubscribed(const QString &subscription, bool wantsSubscription);

public:
	inline void connectToHost()
	{
		QTcpSocket::connectToHost(remoteHost, remotePort.toUInt());
	}

	inline bool isConnectionCreated() const
	{
		return QTcpSocket::isOpen();
	}
	inline bool isConnectionEstablished() const
	{
		return QTcpSocket::isOpen() && authenticated;
	}

	inline QString getItemId() const
	{
		return itemId;
	}

	inline void setItemId(const QString &itemId)
	{
		this->itemId = itemId;
	}

	inline void setRemoteHost(const QString &remoteHost)
	{
		this->remoteHost = remoteHost;
	}

	inline void setRemotePort(const QString &remotePort)
	{
		this->remotePort = remotePort;
	}

private:
	inline RemoteFrame newConnectFrame(const QString &user = QString::null, const QString &pass = QString::null)
	{
		RemoteFrame remoteFrame;
		remoteFrame.setCommand("CONNECT");
		remoteFrame.setHeader("login", user);
		remoteFrame.setHeader("passcode", pass);
		return remoteFrame;
	}

	inline RemoteFrame newDisconnectFrame()
	{
		RemoteFrame remoteFrame;
		remoteFrame.setCommand("DISCONNECT");
		return remoteFrame;
	}

	inline RemoteFrame newSubscriptionFrame(const QString &destination)
	{
		RemoteFrame remoteFrame;
		remoteFrame.setCommand("SUBSCRIBE");
		remoteFrame.setHeader("destination", destination);
		return remoteFrame;
	}

	inline RemoteFrame newUnsubscriptionFrame(const QString &destination)
	{
		RemoteFrame remoteFrame;
		remoteFrame.setCommand("UNSUBSCRIBE");
		remoteFrame.setHeader("destination", destination);
		return remoteFrame;
	}

	inline RemoteFrame newMessageFrame(const QString &destination, const QByteArray &data = QByteArray())
	{
		RemoteFrame remoteFrame;
		remoteFrame.setCommand("MESSAGE");
		remoteFrame.setHeader("destination", destination);
		remoteFrame.setData(QByteArray(data));
		return remoteFrame;
	}

	signals:
	void connectionCreated(RemoteBroker *);
	void connectionEstablished(RemoteBroker *);
	void connectionError(RemoteBroker *, RemoteBroker::SocketError);
	void connectionClosed(RemoteBroker *);
	void frameReceived(RemoteBroker *, RemoteFrame);
	void frameSent(RemoteBroker *, RemoteFrame);

private slots:
	void socketCreated();
	void socketError(QAbstractSocket::SocketError socketError);
	void socketClosed();
	void socketReadable();
	void processSocketBuffer();

private:
	QByteArray *readBuffer;
	QTimer *readTimer;
	QString itemId;
	QString remoteHost;
	QString remotePort;
	bool authenticated;
};

#endif /* REMOTEBROKER_H_ */
