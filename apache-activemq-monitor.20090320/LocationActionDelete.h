/*
 * LocationActionDelete.h
 *
 *  Created on: Mar 18, 2009
 *      Author: Ian Zepp
 */

#ifndef LOCATIONACTIONDELETE_H_
#define LOCATIONACTIONDELETE_H_

#include <QtGui/QMessageBox>
#include "LocationPane.h"

class LocationActionDelete
{
public:
	LocationActionDelete(LocationPane *locationPane);
	virtual ~LocationActionDelete();
};

#endif /* LOCATIONACTIONDELETE_H_ */
