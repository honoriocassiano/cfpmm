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

namespace cfpmm {

Ant::Ant(Instance* _instance) :
		solution(_instance) {

	generateInitialSolution();
}

Ant::~Ant() {

}

void Ant::generateInitialSolution() {
	auto items = solution.instance->items;
	auto capacities = solution.instance->capacities;

	// TODO Implement this function
#warning "Implement this function"

}

} /* namespace cfpmm */
