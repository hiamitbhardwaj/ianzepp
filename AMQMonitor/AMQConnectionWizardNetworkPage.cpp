#include "AMQConnectionWizardNetworkPage.h"

AMQConnectionWizardNetworkPage::AMQConnectionWizardNetworkPage(QWidget *parent) :
	QWizardPage(parent)
{
	ui.setupUi(this);

	// Register option fields
	registerField("name*", ui.name);
	registerField("remoteHost*", ui.remoteHost);
	registerField("remotePort", ui.remotePort);
	registerField("automatic", ui.automatic);

	// Connect signals for overriden isComplete method.
	QObject::connect(ui.name, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
	QObject::connect(ui.remoteHost, SIGNAL(currentIndexChanged(int)), this, SIGNAL(completeChanged()));
	QObject::connect(ui.remoteHost, SIGNAL(editTextChanged(QString)), this, SIGNAL(completeChanged()));

	// Set title and subtitle
	setTitle(trUtf8("Network Connection Settings"));
	setSubTitle(trUtf8("The next few pages will help you to set up a remote connection"
		" to an ActiveMQ messaging server."));
}

AMQConnectionWizardNetworkPage::~AMQConnectionWizardNetworkPage()
{

}

bool AMQConnectionWizardNetworkPage::isComplete() const
{
	if (ui.name->text().isEmpty())
		return false;
	else if (ui.remoteHost->currentText().isEmpty())
		return false;
	else
		return true;
}
