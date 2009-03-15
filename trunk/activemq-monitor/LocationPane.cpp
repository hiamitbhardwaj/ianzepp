#include "LocationPane.h"

LocationPane::LocationPane(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	ui.propertiesWidget->setVisible(ui.propertiesVisible->isChecked());

	// Initialize the context menu
	contextMenu = new QMenu(this);
	contextMenu->addAction(ui.actionConnect);
	contextMenu->addAction(ui.actionDisconnect);
	contextMenu->addAction(ui.actionAutoConnect);
	contextMenu->addSeparator();
	contextMenu->addAction(ui.actionProperties);
}

LocationPane::~LocationPane()
{

}

void LocationPane::contextMenuRequested(const QPoint &pos)
{
	qDebug() << "LocationPane::contextMenuRequested(const QPoint &pos)";

	LocationItem *item = getLocationItem(ui.locationTree->currentItem());

	// Set proper values on action objects prior to menu display
	if (item)
	{
		ui.actionConnect->setEnabled(!item->connected);
		ui.actionDisconnect->setEnabled(item->connected);
		ui.actionAutoConnect->setChecked(item->autoConnect);
	}
	else
	{
		ui.actionConnect->setEnabled(false);
		ui.actionDisconnect->setEnabled(false);
		ui.actionAutoConnect->setEnabled(false);
		ui.actionAutoConnect->setChecked(false);
	}

	actionTriggered(contextMenu->exec(ui.locationTree->mapToGlobal(pos)));
}

void LocationPane::updateProperties(QTreeWidgetItem *treeItem)
{
	qDebug() << "LocationPane::updateProperties(QTreeWidgetItem *treeItem)";

	LocationItem *item = getLocationItem(ui.locationTree->currentItem());
	ui.propertiesWidget->updateProperties(item);
}

void LocationPane::insertItemClicked()
{
	qDebug() << "LocationPane::insertItemClicked()";

}

void LocationPane::removeItemClicked()
{
	qDebug() << "LocationPane::removeItemClicked()";

}

void LocationPane::actionHovered(QAction *action)
{

}

void LocationPane::setPropertiesVisible(bool visible)
{
	ui.propertiesVisible->setChecked(visible);
	ui.propertiesWidget->setVisible(visible);
}

void LocationPane::actionTriggered(QAction *action)
{
	qDebug() << "LocationPane::actionTriggered(QAction *action)";

	if (action == 0)
		return;

	LocationItem *item = getLocationItem(ui.locationTree->currentItem());

	if (item == 0)
		return;

	if (action == ui.actionAutoConnect)
		item->autoConnect = ui.actionAutoConnect->isChecked();
	else if (action == ui.actionConnect)
		emit connectionRequested(item->id);
	else if (action == ui.actionDisconnect)
		emit disconnectionRequested(item->id);
	else if (action == ui.actionProperties)
		setPropertiesVisible(true);
}

