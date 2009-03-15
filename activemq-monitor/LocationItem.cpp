/*
 * LocationItem.cpp
 *
 *  Created on: Mar 14, 2009
 *      Author: Ian Zepp
 */

#include "LocationItem.h"

LocationItem::LocationItem(QObject *parent) :
	QObject(parent), messages(0), bytes(0), connected(false)
{
}

LocationItem::~LocationItem()
{
}

QString LocationItem::getId(IdType type)
{
	switch (type)
	{
	case Full:
	case Subscription:
		return QString(getHostnameUri() + getSubscription());
	case Hostname:
		return QString(getHostnameUri());
	default:
		throw QString("Invalid IdType specified: " + QString::number(type));
	}
}

QString LocationItem::getHostnameUri()
{
	return QString("tcp://" + hostname + ":" + port);
}

QString LocationItem::getSubscription()
{
	if (isTopic())
		return QString("/topic/" + channel);
	else if (isQueue())
		return QString("/queue/" + channel);
	else
		return QString::null;
}
