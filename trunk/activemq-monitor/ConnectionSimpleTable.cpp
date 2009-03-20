/*
 * ConnectionSimpleTable.cpp
 *
 *  Created on: Mar 20, 2009
 *      Author: izepp
 */

#include "ConnectionSimpleTable.h"

ConnectionSimpleTable::ConnectionSimpleTable(QWidget *parent, ConnectionItem *item) :
	QTableWidget(parent)
{
	// Connect to connectionItem
	QObject::connect(item, SIGNAL(messageReceived(ConnectionItem::Frame)), this, SLOT(messageReceived(ConnectionItem::Frame)));
	QObject::connect(item, SIGNAL(messageSent(ConnectionItem::Frame)), this, SLOT(messageSent(ConnectionItem::Frame)));
	QObject::connect(item, SIGNAL(stateChanged(ConnectionItem::State, ConnectionItem::State)), this, SLOT(stateChanged(ConnectionItem::State, ConnectionItem::State)));
	QObject::connect(item, SIGNAL(subscriptionChanged(QString, bool)), this, SLOT(subscriptionChanged(QString, bool)));

	// Update UI with columns
	setColumnCount(7);
	setHorizontalHeaderItem(Subscription, new QTableWidgetItem("Subscription"));
	setHorizontalHeaderItem(Active, new QTableWidgetItem("Subscription"));
	setHorizontalHeaderItem(MessagesIn, new QTableWidgetItem("Messages In"));
	setHorizontalHeaderItem(MessagesOut, new QTableWidgetItem("Messages Out"));
	setHorizontalHeaderItem(BytesIn, new QTableWidgetItem("Bytes In"));
	setHorizontalHeaderItem(BytesOut, new QTableWidgetItem("Bytes Out"));
	setHorizontalHeaderItem(LastActivity, new QTableWidgetItem("Last Activity"));
	verticalHeader()->hide();
}

ConnectionSimpleTable::~ConnectionSimpleTable()
{
}

void ConnectionSimpleTable::incrementItemAt(int row, int column, int incrementBy)
{
	QTableWidgetItem *item = this->item(row, column);
	quint32 currentValue = item->text().toUInt();
	item->setText(QString::number(currentValue + incrementBy));
}

uint ConnectionSimpleTable::insertSubscription(QString subscription)
{
	int insertedRow = rowCount();
	insertRow(insertedRow);
	setItem(insertedRow, Subscription, new QTableWidgetItem(subscription));
	setItem(insertedRow, Active, new QTableWidgetItem("-"));
	setItem(insertedRow, MessagesIn, new QTableWidgetItem("0"));
	setItem(insertedRow, MessagesOut, new QTableWidgetItem("0"));
	setItem(insertedRow, BytesIn, new QTableWidgetItem("0"));
	setItem(insertedRow, BytesOut, new QTableWidgetItem("0"));
	setItem(insertedRow, LastActivity, new QTableWidgetItem("-"));
	return insertedRow;
}

void ConnectionSimpleTable::messageReceived(ConnectionItem::Frame frame)
{
	QTableWidgetItem *item = getItem(frame.getDestination());
	uint relevantRow;

	if (item == 0)
		relevantRow = insertSubscription(frame.getDestination());
	else
		relevantRow = item->row();

	// Bump all of the data fields
	incrementItemAt(relevantRow, MessagesIn);
	incrementItemAt(relevantRow, BytesIn, frame.getSize());
}

void ConnectionSimpleTable::messageSent(ConnectionItem::Frame frame)
{
	QTableWidgetItem *item = getItem(frame.getDestination());
	uint relevantRow;

	if (item == 0)
		relevantRow = insertSubscription(frame.getDestination());
	else
		relevantRow = item->row();

	// Bump all of the data fields
	incrementItemAt(relevantRow, MessagesOut);
	incrementItemAt(relevantRow, BytesOut, frame.getSize());
}

void ConnectionSimpleTable::stateChanged(ConnectionItem::State, ConnectionItem::State)
{
}

void ConnectionSimpleTable::subscriptionChanged(QString destination, bool subscribed)
{
	QTableWidgetItem *item = getItem(destination);
	uint relevantRow;

	if (item == 0 && subscribed)
		relevantRow = insertSubscription(destination);
	else if (item)
		relevantRow = item->row();
	else
		return;

	itemAt(relevantRow, Active)->setText(subscribed ? "Yes" : "No");
}
