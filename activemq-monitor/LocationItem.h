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

public:
	QString id;
	QString name;
	QString remoteHost;
	QString channelType;
	QString channel;
	quint32 messages;
	quint32 bytes;
	bool connected;
	bool autoConnect;
};

#endif /* LOCATIONITEM_H_ */
