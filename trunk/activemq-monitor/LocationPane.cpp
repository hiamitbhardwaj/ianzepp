#include "LocationPane.h"

LocationPane::LocationPane(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	ui.propertiesWidget->setVisible(ui.propertiesVisible->isChecked());

	// Initialize the context menu
	contextMenu = new QMenu(this);
	contextMenu->addAction(ui.actionCreateLocation);

	// Tweak the tree
	ui.locationTree->setColumnHidden(IdColumn, true);
}

LocationPane::~LocationPane()
{

}

void LocationPane::contextMenuRequested(const QPoint &pos)
{
	qDebug() << "LocationPane::contextMenuRequested(const QPoint &pos)";

	//LocationItem *item = getLocationItem(ui.locationTree->currentItem());
	actionTriggered(contextMenu->exec(ui.locationTree->mapToGlobal(pos)));
}

void LocationPane::createLocation(LocationItem *item)
{
	QTreeWidgetItem *treeItem = getTreeItem(item);

	if (treeItem)
	{
		QString messageTitle = "Error creating new location";
		QString messageText = "Remote location already exists: " + item->getRemoteUri();
		QMessageBox::warning(this, messageTitle, messageText);
		return;
	}

	// Create the new tree item
	treeItem = new QTreeWidgetItem(ui.locationTree);
	treeItem->setData(DescriptionColumn, Qt::DisplayRole, item->display);
	treeItem->setData(DescriptionColumn, Qt::ToolTipRole, item->getToolTip());
	treeItem->setData(IdColumn, Qt::DisplayRole, item->getRemoteUri());
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
	if (action == ui.actionCreateLocation)
		handleCreateLocation();
}

void LocationPane::handleCreateLocation()
{
	LocationCreateDialog *dialog = new LocationCreateDialog(this);
	dialog->exec();
}
