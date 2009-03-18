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
#include <QtCore/QUuid>
#include <QtGui/QTreeWidget>
#include "RemoteBroker.h"

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
	LocationItem(LocationItem *parent, int type = Type);
	virtual ~LocationItem();

	QString getDisplayText() const;

public:
	inline bool isAutoConnection() const
	{
		return autoConnection;
	}

	inline bool isAutoSubscription() const
	{
		return autoSubscription;
	}

	inline bool isHttp() const
	{
		return remotePort == QString::number(Http);
	}

	inline bool isHttps() const
	{
		return remotePort == QString::number(Https);
	}

	inline bool isOpenWire() const
	{
		return remotePort == QString::number(OpenWire);
	}

	inline bool isQueue() const
	{
		return QRegExp("^/queue/").indexIn(getSubscription());
	}

	inline bool isRemoteHost() const
	{
		return !isSubscription() && !remoteHost.isEmpty() && !remotePort.isEmpty();
	}

	inline bool isStomp() const
	{
		return remotePort == QString::number(Stomp);
	}

	inline bool isSubscription() const
	{
		return !subscription.isEmpty();
	}

	inline bool isTopic() const
	{
		return QRegExp("^/topic/").indexIn(getSubscription());
	}

	inline void incrementMessages(quint32 num = 1)
	{
		messages += num;
	}

	inline void incrementBytes(quint32 num = 1)
	{
		bytes += num;
	}

	inline quint32 getBytes() const
	{
		return bytes;
	}

	inline QString getId() const
	{
		return text(IdColumn);
	}

	inline quint32 getMessages() const
	{
		return messages;
	}

	inline QString getParentId() const
	{
		return getParentItem()->text(IdColumn);
	}

	inline LocationItem *getParentItem() const
	{
		return (LocationItem *) parent();
	}

	inline RemoteBroker *getRemoteBroker () const
	{
		return remoteBroker;
	}

	inline QString getRemoteHost() const
	{
		return remoteHost;
	}

	inline QString getRemotePort() const
	{
		return remotePort;
	}

	inline QString getSubscription() const
	{
		return subscription;
	}

	inline void setAutoConnection(bool autoConnection)
	{
		this->autoConnection = autoConnection;
	}

	inline void setAutoSubscription(bool autoSubscription)
	{
		this->autoSubscription = autoSubscription;
	}

	inline void setBytes(quint32 bytes)
	{
		this->bytes = bytes;
	}

	inline void setMessages(quint32 messages)
	{
		this->messages = messages;
	}

	inline void setRemoteBroker (RemoteBroker *remoteBroker)
	{
		this->remoteBroker = remoteBroker;
	}

	inline void setRemoteHost(QString remoteHost)
	{
		this->remoteHost = remoteHost;
	}

	inline void setRemotePort(QString remotePort)
	{
		this->remotePort = remotePort;
	}

	inline void setSubscription(QString subscription)
	{
		this->subscription = subscription;
	}

private:
	// Internal data
	QString remoteHost;
	QString remotePort;
	QString subscription;
	quint32 messages;
	quint32 bytes;
	bool autoConnection;
	bool autoSubscription;
	RemoteBroker *remoteBroker;
};

#endif /* LOCATIONITEM_H_ */
