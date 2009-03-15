/*
 * LocationItem.h
 *
 *  Created on: Mar 14, 2009
 *      Author: Ian Zepp
 */

#ifndef LOCATIONITEM_H_
#define LOCATIONITEM_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QTreeWidget>

class LocationItem: public QTreeWidgetItem
{
public:
	enum Ports
	{
		Http = 80, Https = 443, Stomp = 61613, OpenWire = 61616
	};

	enum Columns
	{
		DescriptionColumn, IdColumn
	};

public:
	LocationItem();
	LocationItem(QTreeWidget * parent, int type = Type);
	LocationItem(QTreeWidgetItem * parent, int type = Type);
	virtual ~LocationItem();

public:
	bool isHttp() const
	{
		return remotePort == QString::number(Http);
	}
	bool isHttps() const
	{
		return remotePort == QString::number(Https);
	}
	bool isOpenWire() const
	{
		return remotePort == QString::number(OpenWire);
	}
	bool isQueue() const
	{
		return type.toLower() == "queue" && !subscription.isEmpty();
	}
	bool isRemoteHost() const
	{
		return !isSubscription() && !remoteHost.isEmpty() && !remotePort.isEmpty();
	}
	bool isStomp() const
	{
		return remotePort == QString::number(Stomp);
	}
	bool isSubscription() const
	{
		return !subscription.isEmpty() && !type.isEmpty();
	}
	bool isTopic() const
	{
		return type.toLower() == "topic" && !subscription.isEmpty();
	}

	void incrementMessages(quint32 num = 1)
	{
		messages += num;
	}
	void incrementBytes(quint32 num = 1)
	{
		bytes += num;
	}

	bool getAutoConnection() const
	{
		return autoConnection;
	}

	bool getAutoSubscription() const
	{
		return autoSubscription;
	}

	quint32 getBytes() const
	{
		return bytes;
	}

	bool getConnected() const
	{
		return connected;
	}

	QString getDisplayText() const;

	QString getId() const
	{
		return text(IdColumn);
	}

	quint32 getMessages() const
	{
		return messages;
	}

	QString getRemoteHost() const
	{
		return remoteHost;
	}

	QString getRemotePort() const
	{
		return remotePort;
	}

	QString getSubscription() const
	{
		return subscription;
	}

	QString getType() const
	{
		return type;
	}

	void setAutoConnection(bool autoConnection)
	{
		this->autoConnection = autoConnection;
	}

	void setAutoSubscription(bool autoSubscription)
	{
		this->autoSubscription = autoSubscription;
	}

	void setBytes(quint32 bytes)
	{
		this->bytes = bytes;
	}

	void setConnected(bool connected)
	{
		this->connected = connected;
	}

	void setMessages(quint32 messages)
	{
		this->messages = messages;
	}

	void setRemoteHost(QString remoteHost)
	{
		this->remoteHost = remoteHost;
	}

	void setRemotePort(QString remotePort)
	{
		this->remotePort = remotePort;
	}

	void setSubscription(QString subscription)
	{
		this->subscription = subscription;
	}

	void setType(QString type)
	{
		this->type = type;
	}

private:
	// Internal data
	QString remoteHost;
	QString remotePort;
	QString type;
	QString subscription;
	quint32 messages;
	quint32 bytes;
	bool autoConnection;
	bool autoSubscription;
	bool connected;

};

#endif /* LOCATIONITEM_H_ */
