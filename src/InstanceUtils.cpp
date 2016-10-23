/*
 * InstanceGenerator.cpp
 *
 *  Created on: 20 de out de 2016
 *      Author: aluno
 */

#include "InstanceUtils.h"

#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace cfpmm {

// TODO Check this value
constexpr auto UNIFORM_MIN = 100;
constexpr auto UNIFORM_MAX = 1000;

using namespace std;

InstanceUtils::~InstanceUtils() {

}

void InstanceUtils::generate(std::size_t nItems, std::size_t nKnacksacks,
		correlation correlated, bool similar, bool save) {

#define RAND(MIN, MAX, GEN) (uniform_int_distribution<int>(MIN, MAX)(GEN))

	using c = correlation;
	using uid = uniform_int_distribution<int>;

	// Create random number generator generator
	default_random_engine generator(
			chrono::system_clock::now().time_since_epoch().count());

//	vector<int> weights;
//	vector<int> profits;
	vector<int> capacities;

	vector<Item> items;

	// TODO Check this implementation
	if (correlated == c::NONE) {

		uid distribution(UNIFORM_MIN, UNIFORM_MAX);

		for (int i = 0; i < nItems; i++) {

			// Knacksack Problems - page 185
			int weight = distribution(generator);
			int profit = distribution(generator);

			items.push_back(Item(weight, profit));
		}
	} else if (correlated == c::WEAK) {

		uid distribution(UNIFORM_MIN, UNIFORM_MAX);

		for (int i = 0; i < nItems; i++) {
			// Knacksack Problems - page 185
			int weight = distribution(generator);
			int profit = RAND(weight - 100, weight + 100, generator);

			items.push_back(Item(weight, profit));
		}
	} else if (correlated == c::STRONG) {

		uid distribution(UNIFORM_MIN, UNIFORM_MAX);

		for (int i = 0; i < nItems; i++) {
			// Knacksack Problems - page 186
			int weight = distribution(generator);
			int profit = RAND(weight - 100, weight + 100, generator);
		}
	}

	double weightSum = 0.0;

	for (int i = 0; i < nItems; ++i) {
		weightSum += items[i].weight();
	}

	if (similar) {

		double wj = 0.5 * weightSum;
		int lastCapacity = wj;

		for (int i = 0; i < nKnacksacks - 1; i++) {

			double ck = 0;

			for (int k = 0; k < i; k++) {
				ck += capacities[k];
			}

			uid distribution(UNIFORM_MIN, UNIFORM_MIN + wj - ck);

			int c = distribution(generator);

			capacities.push_back(c);
			lastCapacity -= c;
		}

		capacities.push_back(lastCapacity);

	} else {

		double minBound = 0.4 * weightSum / nKnacksacks;
		double maxBound = 0.6 * weightSum / nKnacksacks;
		double lastCapacity = 0.5 * weightSum;

		uid distribution(minBound, maxBound);

		for (int i = 0; i < nKnacksacks - 1; i++) {
			capacities.push_back(distribution(generator));

			lastCapacity -= capacities[i];
		}

		capacities.push_back(lastCapacity);
	}

	if (save) {
		saveToFile("instance.txt", nItems, nKnacksacks, capacities, items);
	}

#undef RAND
}

bool InstanceUtils::saveToFile(const string& filename, size_t nItems,
		size_t nKnacksacks, const vector<int>& capacities,
		const std::vector<Item>& items) {

	ofstream file(filename.c_str());

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file << nItems << " " << nKnacksacks << "\n";

	for (const auto& i : items) {
		file << i.weight() << " " << i.profit() << "\n";
	}

	for (const auto& c : capacities) {
		file << c << "\n";
	}

	file.close();

	return false;
}

bool InstanceUtils::isValidSolution(const Solution& _solution) {

	auto& capacities = _solution.getInstance()->getCapacities();
	auto& items = _solution.getInstance()->getItems();
	auto& solution = _solution.getSolution();

	int totalWeights[capacities.size()];

	std::fill(totalWeights, totalWeights + capacities.size(), 0);

	for (int i = 0; i < solution.size(); i++) {
		if (solution[i] >= 0) {
			totalWeights[solution[i]] += items[i].weight();
		}
	}

	for(auto& c : totalWeights) {
		std::cout << c << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < capacities.size(); i++) {
		if (totalWeights[i] > capacities[i]) {
			return false;
		}
	}

	return true;
}

Solution* InstanceUtils::generateInitialSolution(const Instance& instance) {

	return nullptr;
}

} /* namespace cfpmm */

