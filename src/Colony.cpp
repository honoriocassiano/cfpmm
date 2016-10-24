/*
 * Colony.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Colony.h"

#include <cassert>

namespace cfpmm {

Colony::Colony(Instance* _instance, std::size_t _nAnts) :
		instance(_instance), nAnts(_nAnts), ants(_nAnts, nullptr) {

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
		ants[i] = new Ant(instance, pheromoneList);
	}
}

} /* namespace cfpmm */
