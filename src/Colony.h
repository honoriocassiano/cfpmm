/*
 * Colony.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef COLONY_H_
#define COLONY_H_

#include "Ant.h"

namespace cfpmm {

class Colony {
public:
	Colony();
	virtual ~Colony();

private:
	std::vector<Ant*> ants;
};

} /* namespace cfpmm */

#endif /* COLONY_H_ */
