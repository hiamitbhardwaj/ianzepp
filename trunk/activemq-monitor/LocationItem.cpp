/*
 * LocationItem.cpp
 *
 *  Created on: Mar 14, 2009
 *      Author: Ian Zepp
 */

#include "LocationItem.h"

LocationItem::LocationItem() :
	QTreeWidgetItem()
{
	setText(IdColumn, QUuid::createUuid().toString());

}

LocationItem::LocationItem(LocationItem *parent, int type) :
	QTreeWidgetItem(parent, type)
{
	setText(IdColumn, QUuid::createUuid().toString());
}

LocationItem::~LocationItem()
{
	if (remoteBroker && isSubscription())
		remoteBroker->setSubscribed(getSubscription(), false);
}

QString LocationItem::getDisplayText() const
{
	bool isHost = isRemoteHost();

	if (isHost && isHttp())
		return QString("http://" + getRemoteHost());
	else if (isHost && isHttps())
		return QString("https://" + getRemoteHost());
	else if (isHost && isOpenWire())
		return QString("openwire://" + getRemoteHost());
	else if (isHost && isStomp())
		return QString("stomp://" + getRemoteHost());
	else if (isSubscription())
		return QString(subscription);
	else
		return QString::null;
}
