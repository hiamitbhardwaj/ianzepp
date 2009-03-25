/*
 * AMQConnectionWizard.h
 *
 *  Created on: Mar 23, 2009
 *      Author: Ian Zepp
 */

#ifndef AMQCONNECTIONWIZARD_H_
#define AMQCONNECTIONWIZARD_H_

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QWizard>

class AMQConnectionWizard: public QWizard
{
Q_OBJECT

public:
	AMQConnectionWizard(QWidget *parent = 0);
	virtual ~AMQConnectionWizard()
	{
	}

public Q_SLOTS:
	virtual void accept()
	{
		qDebug() << "Accepted";
	}

private:
	QWizardPage *createNetworkPage();
	QWizardPage *createAuthorizationPage();
};

#endif /* AMQCONNECTIONWIZARD_H_ */
