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
#include "LocationContextDialog.h"
#include "RemoteBroker.h"
#include "RemoteFrame.h"

class LocationPane: public QWidget
{
Q_OBJECT

public:
	LocationPane(QWidget *parent = 0);
	~LocationPane();

public slots:
	// Context menu management
	void contextMenuRequested(const QPoint &pos);
	void setPropertiesVisible(bool visible);

	// Remote broker management
	void connectionCreated(RemoteBroker *broker);
	void connectionEstablished(RemoteBroker *broker);
	void connectionClosed(RemoteBroker *broker);
	void connectionError(RemoteBroker *broker, RemoteBroker::SocketError &socketError);
	void frameReceived(RemoteBroker *broker, RemoteFrame frame);
	void frameSent(RemoteBroker *broker, RemoteFrame frame);

public:
	inline QTreeWidget *getTreeWidget() const
	{
		return ui.locationTree;
	}

	inline LocationContextDialog *getContextDialog() const
	{
		return contextDialog;
	}

	inline LocationItem *getItemById(const QString &itemId) const
	{
		qDebug() << "LocationItem *LocationPane::getItemById(const QString &itemId) const";
		qDebug() << "\t Item Id: " << itemId;
		Qt::MatchFlags flags = Qt::MatchExactly | Qt::MatchRecursive;
		QList<QTreeWidgetItem *> itemList = ui.locationTree->findItems(itemId, flags, LocationItem::IdColumn);
		qDebug() << "\t Result Count: " << itemList.size();
		return itemList.isEmpty() ? 0 : (LocationItem *) itemList.first();
	}

	inline LocationItem *getSelectedItem() const
	{
		qDebug() << "LocationItem *LocationPane::getSelectedItem() const";
		QList<QTreeWidgetItem *> itemList = ui.locationTree->selectedItems();
		qDebug() << "\t Result Count: " << itemList.size();
		return itemList.isEmpty() ? 0 : (LocationItem *) itemList.first();
	}

	inline LocationItem *getRootItem() const
	{
		return rootItem;
	}

	inline RemoteBroker *getBroker(const QString &itemId) const
	{
		qDebug() << "RemoteBroker *LocationPane::getBroker(const QString &itemId) const";
		qDebug() << "\t Item Id:" << itemId;
		return brokerMap.value(itemId);
	}

	inline void insertBroker(const QString &itemId, RemoteBroker *broker)
	{
		Q_CHECK_PTR(broker);
		qDebug() << "void LocationPane::insertBroker(const QString &itemId, RemoteBroker *broker)";
		qDebug() << "\t Item Id:" << itemId;
		brokerMap.insert(itemId, broker);
	}

	inline void removeBroker(const QString &itemId)
	{
		qDebug() << "void LocationPane::removeBroker(const QString &itemId)";
		qDebug() << "\t Item Id:" << itemId;
		brokerMap.remove(itemId);
	}

	signals:
	void debug(const QString &);

private:
	void initializeContextMenu();
	void initializeContextDialog();

	// Menus
	QMenu *getRootMenu();
	QMenu *getRemoteHostMenu();
	QMenu *getSubscriptionMenu();
	QMenu *getMessageMenu();

	// Actions
	void action(QAction *action);

private:
	Ui::LocationPaneClass ui;
	LocationItem *rootItem;
	LocationContextDialog *contextDialog;
	QMenu *contextMenu;
	QHash<QString, RemoteBroker *> brokerMap;
};

#endif // LOCATIONPANE_H
