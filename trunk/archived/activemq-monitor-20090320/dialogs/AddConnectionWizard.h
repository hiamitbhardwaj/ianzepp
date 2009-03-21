/*
 * AddConnectionWizard.h
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#ifndef ADDCONNECTIONWIZARD_H_
#define ADDCONNECTIONWIZARD_H_

#include <QtCore/QObject>
#include <QtGui/QWidget>
#include <QtGui/QWizard>

class AddConnectionWizard: public QWizard
{
Q_OBJECT

public:
	class AuthenticationPage;
	class NetworkPage;
	class OptionsPage;

public:
	AddConnectionWizard(QWidget *parent = 0);
	virtual ~AddConnectionWizard();

public slots:
	void accept();
};


#endif /* ADDCONNECTIONWIZARD_H_ */
