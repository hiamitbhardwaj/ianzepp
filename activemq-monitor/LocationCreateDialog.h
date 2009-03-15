#ifndef LOCATIONCREATEDIALOG_H
#define LOCATIONCREATEDIALOG_H

#include <QtCore/QString>
#include <QtGui/QDialog>
#include "ui_LocationCreateDialog.h"
#include "LocationItem.h"

class LocationCreateDialog: public QDialog
{
Q_OBJECT

public:
	LocationCreateDialog(QWidget *parent = 0);
	~LocationCreateDialog();

signals:
	void createLocation(LocationItem *item);

public slots:
	virtual void accept();
	void validateLocation();

private:
	Ui::LocationCreateDialogClass ui;
};

#endif // LOCATIONCREATEDIALOG_H
