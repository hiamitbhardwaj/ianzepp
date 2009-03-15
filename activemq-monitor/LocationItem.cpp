/*
 * LocationItem.cpp
 *
 *  Created on: Mar 14, 2009
 *      Author: Ian Zepp
 */

#include "LocationItem.h"

LocationItem::LocationItem(QObject *parent) :
	QObject(parent)
{
	// TODO Auto-generated constructor stub

}

LocationItem::~LocationItem()
{
	// TODO Auto-generated destructor stub
}

QString LocationItem::getRemoteUri(bool complete)
{
	QString remoteUri;
	remoteUri += protocol;
	remoteUri += "://";
	remoteUri += hostname;
	remoteUri += ":";
	remoteUri += port;

	if (complete)
		return remoteUri += getSubscription();
	else
		return remoteUri;
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

QString LocationItem::getDisplayText()
{
	if (isSubscription())
		return getSubscription();
	else if (isRemoteHost())
		return getRemoteUri(false);
	else
		return QString("<unknown>");
}
