/*
 * LocationActionSubscribe.cpp
 *
 *  Created on: Mar 18, 2009
 *      Author: Ian Zepp
 */

#include "LocationActionSubscribe.h"
#include "LocationItem.h"

LocationActionSubscribe::LocationActionSubscribe(LocationPane *locationPane)
{
	Q_CHECK_PTR(locationPane);
	Q_CHECK_PTR(locationPane->getSelectedItem());
	Q_CHECK_PTR(locationPane->getSelectedItem()->getRemoteBroker());

	qDebug() << "LocationActionSubscribe::LocationActionSubscribe(LocationPane *locationPane)";
	qDebug() << "\t With Location Pane:" << locationPane;
	qDebug() << "\t With Subscription:" << locationPane->getSelectedItem()->getSubscription();

	LocationItem *selectedItem = locationPane->getSelectedItem();
	RemoteBroker *remoteBroker = selectedItem->getRemoteBroker();
	remoteBroker->setSubscribed(selectedItem->getSubscription(), true);
}

LocationActionSubscribe::~LocationActionSubscribe()
{
	// TODO Auto-generated destructor stub
}
