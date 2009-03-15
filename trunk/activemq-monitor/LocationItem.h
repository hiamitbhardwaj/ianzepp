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
	static const quint16 StompPort = 61613;
	static const quint16 OpenWirePort = 61616;
	static const quint16 HttpPort = 80;
	static const quint16 HttpsPort = 443;

	enum IdType
	{
		Full, Hostname, Subscription
	};

public:
	LocationItem(QObject *parent = 0);
	virtual ~LocationItem();

	QString getId(IdType = Full);
	QString getHostnameUri();
	QString getSubscription();

	inline bool isAutomaticConnection()
	{
		return hostnameAuto;
	}
	inline bool isAutomaticSubscription()
	{
		return hostnameAuto;
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
		return port == QString::number(StompPort);
	}
	inline bool isOpenWire()
	{
		return port == QString::number(OpenWirePort);
	}
	inline bool isHttp()
	{
		return port == QString::number(HttpPort);
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
	QString hostname;
	bool hostnameAuto;
	QString port;
	QString channel;
	QString channelType;
	bool channelAuto;
	quint32 messages;
	quint32 bytes;
	bool connected;
};

#endif /* LOCATIONITEM_H_ */
