/*
 * InstanceGenerator.cpp
 *
 *  Created on: 20 de out de 2016
 *      Author: aluno
 */

#include "InstanceGenerator.h"

#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

namespace cfpmm {

constexpr auto UNIFORM_MIN = 10;
constexpr auto UNIFORM_MAX = 1000;

InstanceGenerator::InstanceGenerator() {

}

InstanceGenerator::~InstanceGenerator() {

}

void InstanceGenerator::generate(std::size_t nItems, std::size_t nKnacksacks,
		int correlated, bool similar) {

	using namespace std;

	// Create random number generator generator
	default_random_engine generator(
			chrono::system_clock::now().time_since_epoch().count());

	// Create distribution
	uniform_int_distribution<int> distribution(UNIFORM_MIN, UNIFORM_MAX);

	vector<int> weights(nItems);
	vector<int> prices(nItems);
	vector<int> capacities(nKnacksacks);

	// TODO Check this implementation
	if (correlated == 0) {
		for (int i = 0; i < nItems; i++) {

			// Knacksack Problems - page 185
			weights.push_back(distribution(generator));
			prices.push_back(distribution(generator));
		}
	} else if (correlated == 1) {
		for (int i = 0; i < nItems; i++) {

			// Knacksack Problems - page 186
			weights.push_back(distribution(generator));
			prices.push_back(distribution(generator) + 100);
		}
	}

	double weightSum = 0.0;

	for (int i = 0; i < nItems; ++i) {
		weightSum += weights[i];
	}

	if (similar) {

	} else {

	}
}

} /* namespace cfpmm */
