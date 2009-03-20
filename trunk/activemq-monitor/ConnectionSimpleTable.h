/*
 * ConnectionSimpleTable.h
 *
 *  Created on: Mar 20, 2009
 *      Author: izepp
 */

#ifndef CONNECTIONSIMPLETABLE_H_
#define CONNECTIONSIMPLETABLE_H_

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include "ConnectionItem.h"

class ConnectionSimpleTable: public QTableWidget
{
Q_OBJECT

public:
	enum Columns
	{
		Subscription, Active, MessagesIn, MessagesOut, BytesIn, BytesOut, LastActivity
	};

public:
	ConnectionSimpleTable(QWidget *parent, ConnectionItem *item);
	virtual ~ConnectionSimpleTable();

	ConnectionItem *getConnectionItem() const
	{
		return connectionItem;
	}

	QTableWidgetItem *getItem(QString subscription) const
	{
		QList<QTableWidgetItem *> items = findItems(subscription, Qt::MatchFixedString);
		return items.isEmpty() ? 0 : items.first();
	}

public slots:
	void stateChanged(ConnectionItem::State previous, ConnectionItem::State current);
	void messageReceived(ConnectionItem::Frame frame);
	void messageSent(ConnectionItem::Frame frame);
	void subscriptionChanged(QString destination, bool subscribed);

protected:
	void incrementItemAt(int row, int column, int incrementBy = 1);
	uint insertSubscription(QString subscription);

private:
	ConnectionItem *connectionItem;
};

#endif /* CONNECTIONSIMPLETABLE_H_ */
