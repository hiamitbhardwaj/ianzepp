/*
 * NetworkPage.h
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#ifndef ADDCONNECTIONWIZARD_NETWORKPAGE_H_
#define ADDCONNECTIONWIZARD_NETWORKPAGE_H_

#include "../AddConnectionWizard.h"

class AddConnectionWizard::NetworkPage : public QWizardPage
{
	Q_OBJECT

public:
	NetworkPage(QWidget *parent = 0);
	virtual ~NetworkPage();
};

#endif /* ADDCONNECTIONWIZARD_NETWORKPAGE_H_ */
