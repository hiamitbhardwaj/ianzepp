#include "LocationCreateDialog.h"

LocationCreateDialog::LocationCreateDialog(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
	ui.display->setFocus();

	// Connect to parent's slots
	connect(this, SIGNAL(createLocation(LocationItem *)), parent, SLOT(createLocation(LocationItem *)));
}

LocationCreateDialog::~LocationCreateDialog()
{
}

void LocationCreateDialog::accept()
{
	LocationItem *item = new LocationItem(this->parentWidget());
	item->display = ui.display->text();
	item->protocol = ui.protocol->currentText();
	item->hostname = ui.hostname->text();
	item->port = ui.port->text();
	item->automatic = ui.automatic->isChecked();

	// Send out
	emit
	createLocation(item);

	// Accept the dialog
	QDialog::accept();
}

void LocationCreateDialog::validateLocation()
{
	bool disabled = ui.display->text().isEmpty() || ui.hostname->text().isEmpty();
	ui.create->setEnabled(false == disabled);
}
