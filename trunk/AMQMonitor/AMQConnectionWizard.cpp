/*
 * AMQConnectionWizard.cpp
 *
 *  Created on: Mar 23, 2009
 *      Author: Ian Zepp
 */

#include "AMQConnectionWizard.h"
#include "AMQConnectionWizardNetworkPage.h"

AMQConnectionWizard::AMQConnectionWizard(QWidget *parent) :
	QWizard(parent)
{
	addPage(new AMQConnectionWizardNetworkPage(this));
	addPage(createAuthorizationPage());
	setWindowTitle(trUtf8("Create a New Connection"));
}

QWizardPage *AMQConnectionWizard::createNetworkPage()
{
	return NULL;
}

QWizardPage *AMQConnectionWizard::createAuthorizationPage()
{
	QWizardPage *page = new QWizardPage(this);
	page->setTitle(trUtf8("Authorization Settings"));
	return page;
}

