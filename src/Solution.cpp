/*
 * Solution.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Solution.h"

#include <cassert>

namespace cfpmm {

Solution::Solution(Instance* _instance) : instance(_instance) {
	assert(_instance != nullptr);
}

Solution::~Solution() {

}

bool Solution::isSelected(int item) const {
	return solution[item] == -1;
}

bool Solution::isSelected(int item, int knapsack) const {
	return solution[item] == knapsack;
}

std::ostream& operator<<(std::ostream& os, const Solution& solution) {
	for(auto& i : solution.solution) {
		os << i << " ";
	}

	return os;
}

void Solution::clear() {
}

} /* namespace cfpmm */
