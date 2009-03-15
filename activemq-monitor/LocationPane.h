#ifndef LOCATIONPANE_H
#define LOCATIONPANE_H

#include <QtCore/QDebug>
#include <QtCore/QHash>
#include <QtCore/QRegExp>
#include <QtGui/QApplication>
#include <QtGui/QMenu>
#include <QtGui/QMessageBox>
#include <QtGui/QWidget>

#include "ui_LocationPane.h"
#include "LocationItem.h"
#include "LocationCreateDialog.h"

class LocationPane: public QWidget
{
Q_OBJECT

public:
	LocationPane(QWidget *parent = 0);
	~LocationPane();

	enum Columns
	{
		DescriptionColumn, IdColumn
	};

public slots:
	void createLocation(LocationItem *item);
	void updateLocation(LocationItem *item);
	void updateProperties(QTreeWidgetItem *treeItem);

	void contextMenuRequested(const QPoint &pos);
	void insertItemClicked();
	void removeItemClicked();
	void setPropertiesVisible(bool visible);

private slots:
	void actionHovered(QAction *action);
	void actionTriggered(QAction *action);

private:
	inline void registerLocationItem(const QString &locationId, LocationItem *item)
	{
		locationHash.insert(locationId, item);
	}
	inline void unregisterLocationItem(const QString &locationId)
	{
		locationHash.remove(locationId);
	}
	inline LocationItem *getLocationItem(const QString &locationId) const
	{
		return locationHash.value(locationId);
	}
	inline LocationItem *getLocationItem(QTreeWidgetItem *treeItem) const
	{
		return treeItem ? getLocationItem(treeItem->text(IdColumn)) : 0;
	}

	inline QList<QTreeWidgetItem *> getTreeItemList(const QString &locationId) const
	{
		return ui.locationTree->findItems(locationId, Qt::MatchExactly, IdColumn);
	}
	inline QTreeWidgetItem *getTreeItem(const QString &locationId) const
	{
		QList<QTreeWidgetItem *> itemList = getTreeItemList(locationId);
		return itemList.isEmpty() ? 0 : itemList.first();
	}
	inline QTreeWidgetItem *getTreeItem(LocationItem *item) const
	{
		return item ? getTreeItem(item->getId()) : 0;
	}
	inline QTreeWidgetItem *getSelectedTreeItem() const
	{
		QList<QTreeWidgetItem *> itemList = ui.locationTree->selectedItems();
		return itemList.isEmpty() ? 0 : itemList.first();
	}
	inline LocationItem *getSelectedLocationItem() const
	{
		return getLocationItem(getSelectedTreeItem());
	}

	void handleCreateLocation();
	void handleCreateChannel();
	void handleEdit();
	void handleDelete();
	void handleConnect();
	void handleDisconnect();
	void handleSubscribe();
	void handleUnsubscribe();
	void handleAutomaticallyConnect(bool checked);
	void handleAutomaticallySubscribe(bool checked);

private:
	Ui::LocationPaneClass ui;
	QMenu *contextMenu;
	QHash<QString, LocationItem *> locationHash;
};

#endif // LOCATIONPANE_H
