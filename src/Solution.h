/*
 * Solution.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "Instance.h"

namespace cfpmm {

class Ant;

class Solution {
public:
	Solution(Instance* instance);
	virtual ~Solution();

	void clear();

private:
	Instance* instance;

	friend class Ant;
};

} /* namespace cfpmm */

#endif /* SOLUTION_H_ */
