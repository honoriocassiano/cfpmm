/*
 * Solution.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Solution.h"

#include <cassert>
#include <iomanip>

namespace cfpmm {

Solution::Solution(Instance* _instance) :
		instance(_instance) {
	assert(_instance != nullptr);

	remainingCapacity = instance->getCapacities();
	solution = std::vector<int>(this->instance->getCapacities().size(), -1);
}

Solution::~Solution() {

}

bool Solution::isSelected(int item) const {
	return solution[item] == -1;
}

bool Solution::isSelected(int item, int knapsack) const {
	return solution[item] == knapsack;
}

bool Solution::canUpdate(int item, int knapsack) const {
	return (remainingCapacity[knapsack] - instance->getItems()[item].weight() >= 0)
			&& (solution[knapsack] == -1);
}

bool Solution::update(int item, int knapsack) {
	if (canUpdate(item, knapsack)) {
		solution[item] = knapsack;
		remainingCapacity[knapsack] -= instance->getItems()[item].weight();

		return true;
	} else {
		return false;
	}
}

double Solution::getValue() const {

	int sum = 0;

	for (int i = 0; i < instance->getNumItems(); ++i) {
		if (solution[i] != -1) {
			sum += instance->getItems()[i].profit();
		}
	}

	return sum;
}

std::ostream& operator<<(std::ostream& os, const Solution& solution) {
	for (auto& i : solution.solution) {
		os << std::setw(3) << i << " ";
	}

	return os;
}

void Solution::clear() {

	remainingCapacity = instance->getCapacities();

	for (int i = 0; i < instance->getCapacities().size(); ++i) {
		solution[i] = -1;
	}
}

} /* namespace cfpmm */
