#include "AMQMonitor.h"
#include "AMQConnection.h"
#include "AMQConnectionWizard.h"
#include "AMQFrameProducer.h"
#include "AMQSubscription.h"
#include "AMQSubscriptionModel.h"

AMQMonitor::AMQMonitor(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);

	// Initialize the settings
	QCoreApplication::setOrganizationName("Zepp Software");
	QCoreApplication::setOrganizationDomain("ianzepp.com");
	QCoreApplication::setApplicationName("AMQMonitor");

	// Initialize the action signals

	// Initialize connections from settings
	QStringListIterator it(getConnectionIds());

	while (it.hasNext())
	{
		initializeConnection(it.next());
	}

}

AMQMonitor::~AMQMonitor()
{

}

void AMQMonitor::triggeredNewConnection()
{
	qDebug() << "void AMQMonitor::triggeredNewConnection()";
	(new AMQConnectionWizard(this))->show();
}

void AMQMonitor::triggeredNewSubscription()
{
	qDebug() << "void AMQMonitor::triggeredNewSubscription()";
}

void AMQMonitor::initializeConnection(QString connectionId)
{
	AMQConnection *connection = new AMQConnection(this, connectionId);
	connection->loadSettings();

	// Initialize signals & slots
	QObject::connect(connection, SIGNAL(stateChanged(AMQConnection::ConnectionState)), this,
			SLOT(stateChanged(AMQConnection::ConnectionState)));
	QObject::connect(connection, SIGNAL(receivedFrame(AMQConnectionFrame)), this, SLOT(receivedFrame(AMQConnectionFrame)));
	QObject::connect(connection, SIGNAL(sentFrame(AMQConnectionFrame)), this, SLOT(sentFrame(AMQConnectionFrame)));

	// Create the tree item
	QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget);
	item->setText(0, connection->getName());
	item->setText(1, connection->getId());

	// Add to the mapping
	setConnection(connectionId, connection);
}

void AMQMonitor::stateChanged(AMQConnection::ConnectionState)
{

}

void AMQMonitor::receivedFrame(AMQConnectionFrame)
{

}

void AMQMonitor::sentFrame(AMQConnectionFrame)
{

}

