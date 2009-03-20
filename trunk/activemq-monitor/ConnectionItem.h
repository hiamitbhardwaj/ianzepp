/*
 * ConnectionItem.h
 *
 *  Created on: Mar 19, 2009
 *      Author: izepp
 */

#ifndef CONNECTIONITEM_H_
#define CONNECTIONITEM_H_

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QVariant>
#include <QtCore/QUuid>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtNetwork/QTcpSocket>

class ConnectionItem: public QObject, public QTreeWidgetItem
{
Q_OBJECT

public:
	class Frame
	{
	public:
		QString getCommand() const
		{
			return QString(command);
		}

		void setCommand(QString command)
		{
			this->command = command;
		}

		QString getDestination() const
		{
			return getHeader("destination");
		}

		QString getHeader(QString name) const
		{
			if (headers.contains(name))
				return QString(headers.value(name));
			else
				return QString::null;
		}

		void setHeader(QString name, QString value)
		{
			headers.insert(name, value);
		}

		QByteArray getPayload() const
		{
			return payload;
		}

		void setPayload(const QByteArray &payload)
		{
			this->payload = payload;
		}

		QString getSessionId() const
		{
			return getHeader("session-id");
		}

		quint32 getSize() const
		{
			return payload.size();
		}

		QByteArray toByteArray() const
		{
			QHash<QString, QString>::ConstIterator iterator = headers.constBegin();
			QByteArray header;
			header.append(getCommand());
			header.append('\n');

			while (iterator != headers.constEnd())
			{
				header.append(iterator.key());
				header.append(':');
				header.append(' ');
				header.append(iterator.value());
				header.append('\n');
				++iterator;
			}

			header.append('\n');
			header.append(payload);
			header.append('\0');
			header.append('\n');
			return header;
		}

	private:
		QHash<QString, QString> headers;
		QString command;
		QByteArray payload;

	};

public:
	enum State
	{
		Connecting,
		Connected,
		Authorizing,
		Authorized,
		Listening,
		Receiving,
		Received,
		Sending,
		Sent,
		Disconnecting,
		Disconnected
	};

public:
	ConnectionItem(QTreeWidgetItem *parent);
	virtual ~ConnectionItem();

	ConnectionItem::State getState()
	{
		return currentState;
	}

	QString getId() const
	{
		return id;
	}

	bool isConnected()
	{
		return currentState >= Connected && currentState < Disconnecting;
	}

	bool isListening()
	{
		return currentState >= Listening && currentState < Disconnecting;
	}

	bool isSubscribed(QString destination)
	{
		return subscriptions.value(destination);
	}

	QString getRemoteHost() const
	{
		return remoteHost;
	}

	void setRemoteHost(QString remoteHost)
	{
		this->remoteHost = remoteHost;
	}

	QString getRemotePort() const
	{
		return remotePort;
	}

	void setRemotePort(QString remotePort)
	{
		this->remotePort = remotePort;
	}

signals:
	void stateChanged(ConnectionItem::State previous, ConnectionItem::State current);
	void messageReceived(ConnectionItem::Frame frame);
	void messageSent(ConnectionItem::Frame frame);
	void subscriptionChanged(QString destination, bool subscribed);

public slots:
	void setConnected(bool connected);
	void setSubscribed(QString destination, bool subscribed);
	void sendMessage(QString destination, QByteArray payload);
	void sendMessage(ConnectionItem::Frame frame);

protected slots:
	void socketConnected();
	void socketDisconnected();
	void socketReadable();
	void socketProcessBuffer();

protected:
	void setState(ConnectionItem::State state);

private:
	QString id;
	ConnectionItem::State previousState;
	ConnectionItem::State currentState;
	QTcpSocket *socket;
	QByteArray *buffer;
	QTimer *controlTimer;
	QString remoteHost;
	QString remotePort;
	QHash<QString, bool> subscriptions;
};

#endif /* CONNECTIONITEM_H_ */
