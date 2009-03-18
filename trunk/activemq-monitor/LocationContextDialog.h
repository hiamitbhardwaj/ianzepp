#ifndef LocationContextDialog_H
#define LocationContextDialog_H

#include <QtCore/QString>
#include <QtGui/QDialog>
#include "ui_LocationContextDialog.h"
#include "LocationItem.h"

class LocationContextDialog: public QDialog
{
Q_OBJECT

public:
	enum PortIndexes
	{
		EditIndex, StompIndex, OpenWireIndex, HttpIndex, HttpsIndex
	};

	enum ChannelTypeIndexes
	{
		TopicIndex, QueueIndex
	};

	enum ManagementRoles
	{
		Undefined, AddRemoteHost, AddSubscription, Edit
	};

public:
	LocationContextDialog(QWidget *parent = 0);
	~LocationContextDialog();

	// Modified return value for the exec method.
	LocationItem *exec();

public:
	inline void setRootItem(LocationItem *item)
	{
		rootItem = item;
	}

	inline void setRemoteHostItem(LocationItem *item)
	{
		remoteHostItem = item;
	}

	inline void setSubscriptionItem(LocationItem *item)
	{
		subscriptionItem = item;
	}

	inline void setManagementRole(ManagementRoles role) {
		managementRole = role;
	}

public slots:
	void updateAcceptable();

signals:
	void addingRemoteHost(LocationItem *item);
	void addingSubscription(LocationItem *item);

private:
	void setRemoteHostGroupEnabled(bool enabled);
	void setSubscriptionGroupEnabled(bool enabled);
	QString getRemotePort() const;
	QString getSubscription() const;

private:
	Ui::LocationContextDialogClass ui;
	LocationItem *rootItem;
	LocationItem *remoteHostItem;
	LocationItem *subscriptionItem;
	int managementRole;
};

#endif // LocationContextDialog_H
