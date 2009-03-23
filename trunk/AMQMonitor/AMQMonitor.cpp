#include "AMQMonitor.h"
#include "AMQConnection.h"
#include "AMQSubscription.h"
#include "AMQSubscriptionModel.h"
#include "AMQFrameProducer.h"

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

	// Producer
	AMQFrameProducer *producer = new AMQFrameProducer(connection);
	producer->setDestination("/topic/test.1");
	producer->setPayload("Welcome to my world.");

	// Connect
	connection->connectToHost();
}

AMQMonitor::~AMQMonitor()
{

}
