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
	setData(IdColumn, Qt::DisplayRole, QUuid::createUuid().toString());
	setConnectionMode(Closed);

}

LocationItem::LocationItem(LocationItem *parent, int type) :
	QTreeWidgetItem(parent, type)
{
	setData(IdColumn, Qt::DisplayRole, QUuid::createUuid().toString());
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

void LocationItem::setConnectionMode(ConnectionMode mode)
{
	switch (mode)
	{
	case Attempting:
		font(LocationItem::DescriptionColumn).setStyle(QFont::StyleItalic);
		font(LocationItem::DescriptionColumn).setWeight(QFont::Normal);
		setToolTip(LocationItem::DescriptionColumn, "Attempting to open connection to " + getRemoteHost());
		break;

	case Created:
		font(LocationItem::DescriptionColumn).setStyle(QFont::StyleItalic);
		font(LocationItem::DescriptionColumn).setWeight(QFont::Normal);
		setToolTip(LocationItem::DescriptionColumn, "Connection created, requesting authorization...");
		break;

	case Established:
		font(LocationItem::DescriptionColumn).setStyle(QFont::StyleNormal);
		font(LocationItem::DescriptionColumn).setWeight(QFont::Bold);
		setToolTip(LocationItem::DescriptionColumn, "Connection established.");
		break;

	case Closed:
		font(LocationItem::DescriptionColumn).setStyle(QFont::StyleNormal);
		font(LocationItem::DescriptionColumn).setWeight(QFont::Normal);
		setToolTip(LocationItem::DescriptionColumn, "Not currently connected.");
		break;

	case Error:
		font(LocationItem::DescriptionColumn).setStyle(QFont::StyleNormal);
		font(LocationItem::DescriptionColumn).setWeight(QFont::Normal);
		setToolTip(LocationItem::DescriptionColumn, "Not currently connection: socket error!");
		break;
	}
}
