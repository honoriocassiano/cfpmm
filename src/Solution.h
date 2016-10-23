/*
 * Solution.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "Instance.h"
#include <vector>
#include <ostream>

namespace cfpmm {

class Ant;

class Solution {
public:
	Solution(Instance* instance);
	virtual ~Solution();

	void clear();

	const std::vector<int>& getSolution() const {
		return solution;
	}

	// TODO Remove this function
	std::vector<int>& getSolution() {
		return solution;
	}

	const Instance* getInstance() const {
		return instance;
	}

	friend std::ostream& operator<<(std::ostream& os, const Solution& solution);

private:
	Instance* instance;

	std::vector<int> solution;

	friend class Ant;
};

} /* namespace cfpmm */

#endif /* SOLUTION_H_ */
