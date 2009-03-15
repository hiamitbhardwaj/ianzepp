#include "LocationCreateDialog.h"

LocationCreateDialog::LocationCreateDialog(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);

	// Connect to parent's slots
	connect(this, SIGNAL(createLocation(LocationItem *)), parent, SLOT(createLocation(LocationItem *)));
}

LocationCreateDialog::~LocationCreateDialog()
{

}

void LocationCreateDialog::accept()
{
	LocationItem *item = new LocationItem(this->parentWidget());
	item->protocol = ui.protocol->currentText();
	item->hostname = ui.hostname->text();
	item->port = atoi(ui.port->text().toAscii().constData());
	item->automatic = ui.automatic->isChecked();

	// Send out
	emit createLocation(item);

	// Accept the dialog
	QDialog::accept();
}
