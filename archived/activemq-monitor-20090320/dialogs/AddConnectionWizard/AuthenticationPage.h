/*
 * AuthenticationPage.h
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#ifndef ADDCONNECTIONWIZARD_AUTHENTICATIONPAGE_H_
#define ADDCONNECTIONWIZARD_AUTHENTICATIONPAGE_H_

#include "../AddConnectionWizard.h"

class AddConnectionWizard::AuthenticationPage: public QWizardPage
{
Q_OBJECT

public:
	AuthenticationPage(QWidget *parent = 0);
	virtual ~AuthenticationPage();
};

#endif /* ADDCONNECTIONWIZARD_AUTHENTICATIONPAGE_H_ */
