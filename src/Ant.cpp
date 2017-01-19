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

double Ant::calculateProbability(int item, int knapsack) {
	double ph = this->pheromoneList.at(knapsack).at(item);

	double hI = 1.0 * this->instance->getItems()[item].profit()
			/ this->solution.getRemainingCapacity().at(knapsack);

	return pow(ph, alpha) * pow(hI, beta);
}

void Ant::findSolution() {

	solution.clear();

	using rid = std::uniform_real_distribution<double>;

	// Create random number generator generator
	std::default_random_engine generator(
			std::chrono::system_clock::now().time_since_epoch().count());

	rid distribution(0, 1);

	bool loop = true;

	while (loop) {
		double prob = distribution(generator);

		double probabilities[instance->getNumKnapsacks()][instance->getNumItems()] {
				0 };

		double probabilitiesSum = 0;

		bool hasAvaliableItem = true;

		for (int k = 0; k < instance->getNumKnapsacks(); ++k) {
			for (int i = 0; i < instance->getNumItems(); ++i) {

				if (solution.canUpdate(i, k)) {
					probabilities[k][i] = calculateProbability(i, k);

				} else {
					probabilities[k][i] = 0.0;

					hasAvaliableItem = false;
				}

				probabilitiesSum += probabilities[k][i];
			}
		}

		if (!hasAvaliableItem) {
			loop = false;
		}

		// Normalize probabilities
		for (int k = 0; k < instance->getNumKnapsacks(); ++k) {
			for (int i = 0; i < instance->getNumItems(); ++i) {
				probabilities[k][i] /= probabilitiesSum;
			}
		}

		double sum = 0.0;

		bool itemChoosed = false;

		int k = 0, i = 0;

		while (k < instance->getNumKnapsacks() && !itemChoosed) {
			while (i < instance->getNumItems() && !itemChoosed) {

				if (prob < sum + probabilities[k][i]) {
					this->solution.update(i, k);

					itemChoosed = true;
				}
				sum += probabilities[k][i];
				++i;
			}
			++k;
		}
	}
}

void Ant::generateInitialSolution() {
	auto& items = solution.instance->items;
	auto& capacities = solution.instance->capacities;

	std::vector<int> solution(items.size(), -1);
	std::vector<int> remainingCapacities(capacities);

	for (int i = 0; i < items.size(); ++i) {

		for (int k = 0; k < capacities.size(); ++k) {

			Log(
					"i: %d, k: %d, remainingCapacities[k]: %d, items[i].weight(): %d",
					i, k, remainingCapacities[k], items[i].weight());

			if (remainingCapacities[k] >= items[i].weight()) {
				solution[i] = k;
				remainingCapacities[k] -= items[i].weight();

				std::cout << std::endl;

				break;
			}
		}
	}

	this->solution.solution = std::move(solution);

	Log("Solução da formiga");
	std::cout << this->solution << std::endl << std::endl;
}

} /* namespace cfpmm */

