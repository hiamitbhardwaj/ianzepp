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

class LocationItem: public QObject
{
public:
	LocationItem(QObject *parent = 0);
	virtual ~LocationItem();

	QString getRemoteUri(bool complete = true);
	QString getSubscription();
	QString getToolTip ();

	inline bool isAutomatic()
	{
		return automatic;
	}
	inline bool isConnected()
	{
		return connected;
	}

	inline bool isRemoteHost()
	{
		return getSubscription().isEmpty();
	}
	inline bool isSubscription()
	{
		return false == getSubscription().isEmpty();
	}

	inline bool isStomp()
	{
		return protocol.toLower() == "stomp";
	}
	inline bool isOpenWire()
	{
		return protocol.toLower() == "openwire";
	}
	inline bool isHttp()
	{
		return protocol.toLower() == "http";
	}

	inline bool isTopic()
	{
		return channelType.toLower() == "topic" && false == channel.isEmpty();
	}
	inline bool isQueue()
	{
		return channelType.toLower() == "queue" && false == channel.isEmpty();
	}

	inline void incrementMessages(quint32 num = 1)
	{
		messages += num;
	}
	inline void incrementBytes(quint32 num = 1)
	{
		bytes += num;
	}

public:
	QString display;
	QString protocol;
	QString hostname;
	QString port;
	QString channelType;
	QString channel;
	quint32 messages;
	quint32 bytes;
	bool connected;
	bool automatic;
};

#endif /* LOCATIONITEM_H_ */
