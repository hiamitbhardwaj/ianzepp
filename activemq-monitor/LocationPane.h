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
	void addingRemoteHost(LocationItem *item);
	void addingSubscription(LocationItem *item);
	void setPropertiesVisible(bool visible);

	// Remote broker management
	void connectionCreated(RemoteBroker *broker);
	void connectionEstablished(RemoteBroker *broker);
	void connectionClosed(RemoteBroker *broker);
	void connectionError(RemoteBroker *broker, RemoteBroker::SocketError &socketError);
	void frameReceived(RemoteBroker *broker, RemoteFrame *frame);
	void frameSent(RemoteBroker *broker, RemoteFrame *frame);

public:
	inline QTreeWidget *getTreeWidget() const
	{
		return ui.locationTree;
	}

private:
	inline LocationContextDialog *getContextDialog() const
	{
		return contextDialog;
	}

	inline QTreeWidgetItem *getSelectedTreeItem() const
	{
		QList<QTreeWidgetItem *> itemList = ui.locationTree->selectedItems();
		return itemList.isEmpty() ? 0 : itemList.first();
	}

	inline LocationItem *getSelectedItem() const
	{
		return (LocationItem *) getSelectedTreeItem();
	}

	inline LocationItem *getRootItem() const
	{
		return rootItem;
	}

	inline RemoteBroker *getBroker(const QString &itemId) const
	{
		return brokerMap.value(itemId);
	}

	inline void insertBroker(const QString &itemId, RemoteBroker *broker)
	{
		brokerMap.insert(itemId, broker);
	}

	inline void removeBroker(const QString &itemId)
	{
		brokerMap.remove(itemId);
	}

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
	void actionAddRemoteHost();
	void actionAddSubscription();
	void actionEdit();
	void actionDelete();
	void actionConnect();
	void actionDisconnect();
	void actionSubscribe();
	void actionUnsubscribe();
	void actionAutoConnection(bool checked);
	void actionAutoSubscription(bool checked);

private:
	Ui::LocationPaneClass ui;
	LocationItem *rootItem;
	LocationContextDialog *contextDialog;
	QMenu *contextMenu;
	QHash<QString, RemoteBroker *> brokerMap;
};

#endif // LOCATIONPANE_H
