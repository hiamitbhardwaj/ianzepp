/*
 * OptionsPage.h
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#ifndef ADDCONNECTIONWIZARD_OPTIONSPAGE_H_
#define ADDCONNECTIONWIZARD_OPTIONSPAGE_H_

#include "../AddConnectionWizard.h"

class AddConnectionWizard::OptionsPage: public QWizardPage
{
Q_OBJECT

public:
	OptionsPage(QWidget *parent = 0);
	virtual ~OptionsPage();
};

#endif /* ADDCONNECTIONWIZARD_OPTIONSPAGE_H_ */
