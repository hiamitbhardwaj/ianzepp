/*
 * LocationActionDelete.cpp
 *
 *  Created on: Mar 18, 2009
 *      Author: Ian Zepp
 */

#include "LocationActionDelete.h"

LocationActionDelete::LocationActionDelete(LocationPane *locationPane)
{
	qDebug() << "LocationActionDelete::LocationActionDelete(LocationPane *locationPane)";
	qDebug() << "\t Using Pane:" << locationPane;

	Q_CHECK_PTR(locationPane);
	Q_CHECK_PTR(locationPane->getSelectedItem());
	Q_CHECK_PTR(locationPane->getSelectedItem()->getRemoteBroker());

	LocationItem *selectedItem = locationPane->getSelectedItem();
	RemoteBroker *selectedBroker = selectedItem->getRemoteBroker();
	QString selectedItemId = selectedItem->getId();
	bool isRemoteHost = selectedItem->isRemoteHost();

	// Questions
	QString head = "Delete?";
	QString body = "Are you sure?";

	if (QMessageBox::question(locationPane, head, body) != QMessageBox::Ok)
		return;

	// Delete the item
	delete selectedItem;

	// Delete the broker, this will auto-disconnect (now that final messages have been sent)
	if (isRemoteHost)
	{
		locationPane->removeBroker(selectedItemId);
		delete selectedBroker;
	}
}

LocationActionDelete::~LocationActionDelete()
{
	// TODO Auto-generated destructor stub
}
