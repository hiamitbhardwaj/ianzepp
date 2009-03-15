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

	enum PortIndexes
	{
		EditIndex, StompIndex, OpenWireIndex, HttpIndex, HttpsIndex
	};

	enum ChannelTypeIndexes
	{
		TopicIndex, QueueIndex
	};

public:
	inline void setParentItem(LocationItem *item)
	{
		parentItem = item;
	}

	virtual int exec();

public slots:
	virtual void accept();
	void validateLocation();
	void setLocationEnabled(bool enabled);
	void setChannelEnabled(bool enabled);
	void setChannelVisible(bool visible);
	void setMessageVisible(bool visible);

private:
	Ui::LocationCreateDialogClass ui;
	LocationItem *parentItem;
};

#endif // LOCATIONCREATEDIALOG_H
