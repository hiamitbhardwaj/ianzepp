#include "AMQMonitor.h"
#include "AMQConnection.h"
#include "AMQSubscription.h"

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

	// Connect
	connection->connectToHost();
}

AMQMonitor::~AMQMonitor()
{

}
