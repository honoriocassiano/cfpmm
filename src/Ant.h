/*
 * Ant.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef ANT_H_
#define ANT_H_

#include "Instance.h"
#include "Solution.h"

namespace cfpmm {

class Ant {
public:
	Ant(Instance* instance);
	virtual ~Ant();

	void generateInitialSolution();

private:

	Solution solution;
};

} /* namespace cfpmm */

#endif /* ANT_H_ */
