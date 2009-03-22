#include "AMQMonitor.h"
#include "AMQConnection.h"
#include "AMQSubscription.h"
#include "AMQSubscriptionModel.h"

AMQMonitor::AMQMonitor(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);

	AMQConnection *connection = new AMQConnection(this);
	AMQSubscription *subscription;

	// Create a few listeners
	subscription = connection->createSubscription("/topic/test.1");
	subscription->setAutomatic(true);
	subscription->setAcknowledged(true);
	subscription->setGeneratedId();

	// Add model
	ui.subscriptionView->setModel(new AMQSubscriptionModel(subscription));

	// Connect
	connection->connectToHost();
}

AMQMonitor::~AMQMonitor()
{

}
