/*
 * AMQSubscription.h
 *
 *  Created on: Mar 21, 2009
 *      Author: Ian Zepp
 */

#ifndef AMQSUBSCRIPTION_H_
#define AMQSUBSCRIPTION_H_

#include <QtCore/QObject>

class AMQSubscription: public QObject
{
Q_OBJECT

public:
	AMQSubscription(QObject *parent);
	virtual ~AMQSubscription();

private:
	QString id;
	QString destination;
	QString selector;
	bool automatic;
};

#endif /* AMQSUBSCRIPTION_H_ */
