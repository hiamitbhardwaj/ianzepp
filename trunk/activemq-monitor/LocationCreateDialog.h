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

	enum AcceptSignal
	{
		Create, Update
	};

signals:
	void createLocation(LocationItem *item);
	void updateLocation(LocationItem *item);

public slots:
	virtual void accept();
	void populate(LocationItem *item);
	void validateLocation();
	void setLocationEnabled(bool enabled);
	void setChannelEnabled(bool enabled);
	void setChannelVisible(bool visible);
	void setMessageVisible(bool visible);

	inline AcceptSignal getAcceptSignal() const
	{
		return acceptSignal;
	}
	inline void setAcceptSignal(AcceptSignal acceptSignal)
	{
		this->acceptSignal = acceptSignal;
	}

private:
	Ui::LocationCreateDialogClass ui;
	AcceptSignal acceptSignal;
};

#endif // LOCATIONCREATEDIALOG_H
