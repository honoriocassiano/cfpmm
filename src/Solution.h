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

/**
 * Class that represent a solution to an instance
 */
class Solution {
public:

	/**
	 * @param instance Instance of problem
	 */
	Solution(Instance* instance);
	virtual ~Solution();

	void clear();

	bool isSelected(int item) const;
	bool isSelected(int item, int knapsack) const;

	bool canUpdate(int item, int knapsack) const;

	bool update(int item, int knapsack) const;

	/**
	 * Getter for solution vector
	 */
	const std::vector<int>& getSolution() const {
		return solution;
	}

	// TODO Remove this function
	std::vector<int>& getSolution() {
		return solution;
	}

	/**
	 * Getter for instance
	 */
	const Instance* getInstance() const {
		return instance;
	}

	const std::vector<int>& getRemainingCapacity() const {
		return remainingCapacity;
	}

	friend std::ostream& operator<<(std::ostream& os, const Solution& solution);

private:
	Instance* instance;

	std::vector<int> solution;
	std::vector<int> capacities;
	std::vector<int> remainingCapacity;

	friend class Ant;
};

} /* namespace cfpmm */

#endif /* SOLUTION_H_ */
