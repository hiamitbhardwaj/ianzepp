/*
 * AddConnectionWizard.cpp
 *
 *  Created on: Mar 20, 2009
 *      Author: Ian Zepp
 */

#include "AddConnectionWizard.h"
#include "AddConnectionWizard/AuthenticationPage.h"
#include "AddConnectionWizard/NetworkPage.h"
#include "AddConnectionWizard/OptionsPage.h"

AddConnectionWizard::AddConnectionWizard(QWidget *parent) :
	QWizard(parent)
{
	addPage(new AddConnectionWizard::NetworkPage);
	addPage(new AddConnectionWizard::AuthenticationPage);
	addPage(new AddConnectionWizard::OptionsPage);
	setWindowTitle("Add Connection Wizard");
}

AddConnectionWizard::~AddConnectionWizard()
{
	// TODO Auto-generated destructor stub
}

void AddConnectionWizard::accept()
{

}
