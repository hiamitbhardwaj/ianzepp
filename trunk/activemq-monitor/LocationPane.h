#ifndef LOCATIONPANE_H
#define LOCATIONPANE_H

#include <QtCore/QDebug>
#include <QtCore/QHash>
#include <QtCore/QRegExp>
#include <QtGui/QApplication>
#include <QtGui/QMenu>
#include <QtGui/QWidget>

#include "ui_LocationPane.h"
#include "LocationItem.h"

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

signals:
	void connectionRequested(const QString &registeredKey);
	void disconnectionRequested(const QString &registeredKey);

public slots:
	void contextMenuRequested(const QPoint &pos);
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

private:
	Ui::LocationPaneClass ui;
	QMenu *contextMenu;
	QHash<QString, LocationItem *> locationHash;
};

#endif // LOCATIONPANE_H
