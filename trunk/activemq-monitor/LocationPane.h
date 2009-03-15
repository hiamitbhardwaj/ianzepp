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
	void contextMenuRequested(const QPoint &pos);
	void createLocation(LocationItem *item);
	void insertItemClicked();
	void removeItemClicked();
	void setPropertiesVisible(bool visible);
	void updateProperties(QTreeWidgetItem *treeItem);

private slots:
	void actionHovered(QAction *action);
	void actionTriggered(QAction *action);

private:
	inline LocationItem *registerLocationItem(const QString &locationKey)
	{
		return locationHash.insert(locationKey, new LocationItem(this)).value();
	}
	inline LocationItem *getLocationItem(const QString &locationKey) const
	{
		return locationHash.value(locationKey);
	}
	inline LocationItem *getLocationItem(QTreeWidgetItem *treeItem) const
	{
		return treeItem ? getLocationItem(treeItem->text(IdColumn)) : 0;
	}

	inline QList<QTreeWidgetItem *> getTreeItemList(LocationItem *item) const
	{
		if (item)
			return ui.locationTree->findItems(item->getRemoteUri(), Qt::MatchExactly, IdColumn);
		else
			return QList<QTreeWidgetItem *> ();
	}
	inline QTreeWidgetItem *getTreeItem(LocationItem *item) const
	{
		QList<QTreeWidgetItem *> itemList = getTreeItemList(item);
		return itemList.isEmpty() ? 0 : itemList.first();
	}

	void handleCreateLocation();

private:
	Ui::LocationPaneClass ui;
	QMenu *contextMenu;
	QHash<QString, LocationItem *> locationHash;
};

#endif // LOCATIONPANE_H
