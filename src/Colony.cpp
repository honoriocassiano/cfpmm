/*
 * Colony.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Colony.h"

#include <cassert>
#include <iostream>

namespace cfpmm {

Colony::Colony(Instance* _instance, std::size_t _nAnts, float _evaporationRatio, double _alpha, double _beta) :
		instance(_instance), nAnts(_nAnts), ants(_nAnts, nullptr), evaporationRatio(
				_evaporationRatio), alpha(_alpha), beta(_beta) {

	if (evaporationRatio >= 1 || evaporationRatio <= 0) {
		std::cerr
				<< "Evaporation ratio must be greater then 0 and less then 1\n";
		exit(-1);
	}

	assert(instance != nullptr);

	initialize();
}

Colony::~Colony() {

	for (auto& ant : ants) {
		delete ant;
	}
}

void Colony::initialize() {

	// TODO Must be a parameter?
	constexpr double initialPheromoneValue = 1;

	pheromoneList = std::vector<std::vector<double> >(instance->nKnapsacks,
			std::vector<double>(instance->nItems, initialPheromoneValue));

	for (int i = 0; i < nAnts; ++i) {
		ants[i] = new Ant(instance, pheromoneList, alpha, beta);
	}
}

void Colony::evaporate() {
	for (auto& l : pheromoneList) {
		for (auto& f : l) {
			f *= evaporationRatio;
		}
	}
}

void Colony::run() {
	// TODO Implement this method
}

void Colony::iterateOverAnts() {
	for (int a = 0; a < nAnts; ++a) {
		ants[a]->findSolution();
	}

	evaporate();
	reinforce();
}

void Colony::reinforce() {
	Ant* bestAnt = ants[0];

	for (int i = 1; i < ants.size(); ++i) {
		auto& ant = ants[i];

		if (ant->getValue() > bestAnt->getValue()) {
			bestAnt = ant;
		}
	}

	for (int i = 0; i < instance->nKnapsacks; ++i) {
		for (int j = 0; j < instance->nItems; ++j) {
			if(bestAnt->getSolution().isSelected(j, i)) {
				pheromoneList[i][j] += (1 - evaporationRatio);
			}
		}
	}
}

} /* namespace cfpmm */
