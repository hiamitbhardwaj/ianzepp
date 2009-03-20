/*
 * LocationActionAddSubscription.cpp
 *
 *  Created on: Mar 18, 2009
 *      Author: Ian Zepp
 */

#include "LocationActionAddSubscription.h"
#include "LocationContextDialog.h"
#include "LocationItem.h"

LocationActionAddSubscription::LocationActionAddSubscription(LocationPane *locationPane)
{
	qDebug() << "LocationActionAddSubscription::LocationActionAddSubscription(LocationPane *locationPane)";
	qDebug() << "\t Using Pane:" << locationPane;

	Q_CHECK_PTR(locationPane);

	LocationContextDialog *contextDialog = locationPane->getContextDialog();
	LocationItem *rootItem = locationPane->getRootItem();
	LocationItem *selectedItem = locationPane->getSelectedItem();
	LocationItem *subscriptionItem = 0;
	LocationItem *returnedItem = 0;

	Q_CHECK_PTR(rootItem);
	Q_CHECK_PTR(selectedItem);

	contextDialog->setRootItem(rootItem);
	contextDialog->setRemoteHostItem(selectedItem);
	contextDialog->setSubscriptionItem(subscriptionItem);
	contextDialog->setManagementRole(LocationContextDialog::AddSubscription);

	// Add the subscription
	returnedItem = contextDialog->exec();

	// If there was no response object, the item doesn't need to be created
	if (returnedItem == 0)
		return;

	// Save the remote broker
	Q_CHECK_PTR(selectedItem->getRemoteBroker());
	returnedItem->setRemoteBroker(selectedItem->getRemoteBroker());
	returnedItem->setIcon(LocationItem::DescriptionColumn, QIcon(":/resources/icons/entry_org.gif"));

	// Does this name already exist in the tree?
	// TODO

	// Add to tree and expand
	selectedItem->addChild(returnedItem);
	selectedItem->treeWidget()->expandItem(rootItem);
	selectedItem->treeWidget()->expandItem(selectedItem);
	// TODO ui.locationTree->expandItem(rootItem);
	// TODO ui.locationTree->expandItem(selectedItem);

	// Is the broker connected?
	if (returnedItem->isConnected() && returnedItem->isAutoSubscription())
		returnedItem->getRemoteBroker()->setSubscribed(returnedItem->getSubscription(), true);
}

LocationActionAddSubscription::~LocationActionAddSubscription()
{
	// TODO Auto-generated destructor stub
}
