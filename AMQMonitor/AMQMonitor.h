#ifndef AMQMONITOR_H
#define AMQMONITOR_H

#include <QtCore/QCoreApplication>
#include <QtCore/QHash>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QMainWindow>

#include "AMQConnection.h"
#include "AMQConnectionFrame.h"
#include "AMQSubscription.h"

// UI classes
#include "ui_AMQMonitor.h"

class AMQMonitor: public QMainWindow
{
Q_OBJECT

public:
	AMQMonitor(QWidget *parent = 0);
	~AMQMonitor();

public Q_SLOTS:
	void triggeredNewConnection();
	void triggeredNewSubscription();

private Q_SLOTS:
	void stateChanged(AMQConnection::ConnectionState);
	void receivedFrame(AMQConnectionFrame);
	void sentFrame(AMQConnectionFrame);

private:
	void initializeConnection(QString connectionId);

private:
	AMQConnection *getConnection(QString connectionId) const
	{
		if (connections.contains(connectionId))
			return connections.value(connectionId);
		else
			return NULL;
	}

	void setConnection(QString connectionId, AMQConnection *connection)
	{
		connections.insert(connectionId, connection);
	}

	QStringList getConnectionIds() const
	{
		QSettings settings;
		settings.beginGroup("connections");
		return settings.childGroups();
	}

	AMQSubscription *getSubscription(QString subscriptionId) const
	{
		if (subscriptions.contains(subscriptionId))
			return subscriptions.value(subscriptionId);
		else
			return NULL;
	}

	void setSubscription(QString subscriptionId, AMQSubscription *subscription)
	{
		subscriptions.insert(subscriptionId, subscription);
	}

	QStringList getSubscriptionIds(QString connectionId) const
	{
		QSettings settings;
		settings.beginGroup("connections/" + connectionId + "/subscriptions");
		return settings.childKeys();
	}

private:
	Ui::AMQMonitorClass ui;
	QHash<QString, AMQConnection *> connections;
	QHash<QString, AMQSubscription *> subscriptions;
};

#endif // AMQMONITOR_H
