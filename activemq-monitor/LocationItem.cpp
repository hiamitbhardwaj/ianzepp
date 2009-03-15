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
}

LocationItem::LocationItem(QTreeWidget *parent, int type) :
	QTreeWidgetItem(parent, type)
{
}

LocationItem::LocationItem(QTreeWidgetItem *parent, int type) :
	QTreeWidgetItem(parent, type)
{
}

LocationItem::~LocationItem()
{
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
	else if (isTopic())
		return QString("/topic/" + subscription);
	else if (isQueue())
		return QString("/queue/" + subscription);
	else
		return QString::null;
}
