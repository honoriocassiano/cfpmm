/*
 * Ant.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Ant.h"

#include <chrono>
#include <random>
#include <algorithm>
#include <memory>

namespace cfpmm {

Ant::Ant(Instance* _instance, std::vector<std::vector<double> >& _pheromoneList) :
		solution(_instance), pheromoneList(_pheromoneList) {

	generateInitialSolution();
}

Ant::~Ant() {

}

void Ant::generateInitialSolution() {
	auto& items = solution.instance->items;
	auto& capacities = solution.instance->capacities;

	std::vector<int> solution(items.size(), -1);
	std::vector<int> remainingCapacities(capacities);

	for (int i = 0; i < items.size(); ++i) {

		for (int k = 0; k < capacities.size(); ++k) {

			if (remainingCapacities[k] >= items[i].weight()) {
				solution[i] = k;
				remainingCapacities[k] -= items[i].weight();

				break;
			}
		}
	}

	this->solution.solution = std::move(solution);
}

} /* namespace cfpmm */
