/*
 * Ant.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Ant.h"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#include "Item.h"

#include "Debug.h"

namespace cfpmm {

Ant::Ant(Instance* _instance, std::vector<std::vector<double> >& _pheromoneList,
		double _alpha, double _beta) :
		solution(_instance), pheromoneList(_pheromoneList), instance(_instance), alpha(
				_alpha), beta(_beta) {

	generateInitialSolution();
}

Ant::~Ant() {

}

bool Ant::loop() {

	using rid = std::uniform_real_distribution<double>;

	// Create random number generator generator
	std::default_random_engine generator(
			std::chrono::system_clock::now().time_since_epoch().count());

	rid distribution(0, 1);

	double prob = distribution(generator);

	double probabilities[this->instance->getNumKnapsacks()][this->instance->getNumItems()];
	double sumOfProbabilities = 0;

	bool itemAvailable = false;

	for (int k = 0; k < this->instance->getNumKnapsacks(); ++k) {
		for (int i = 0; i < this->instance->getNumItems(); ++i) {
			if (this->solution.canUpdate(i, k)) {
				probabilities[k][i] = calculateProbability(i, k);
				itemAvailable = true;
			} else {
				probabilities[k][i] = 0.0f;
			}

			sumOfProbabilities += probabilities[k][i];
		}
	}

	if (!itemAvailable) {
		return false;
	}

	for (int k = 0; k < instance->getNumKnapsacks(); ++k) {
		for (int i = 0; i < instance->getNumItems(); ++i) {
			probabilities[k][i] = (1.0 * probabilities[k][i])
					/ sumOfProbabilities;
		}
	}

	float sum = 0.0f;
	for (int k = 0; k < this->instance->getNumKnapsacks(); ++k) {
		for (int i = 0; i < this->instance->getNumItems(); ++i) {
			if (prob < sum + probabilities[k][i]) {
				this->solution.update(i, k);
				return true;
			}
			sum += probabilities[k][i];
		}
	}

	return false;
}

double Ant::calculateProbability(int item, int knapsack) {
	double ph = this->pheromoneList.at(knapsack).at(item);

	double hI = 1.0 * this->instance->getItems()[item].profit()
			/ this->solution.getRemainingCapacity().at(knapsack);

	return pow(ph, alpha) * pow(hI, beta);
}

void Ant::findSolution() {

	solution.clear();

	while (loop())
		;
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

