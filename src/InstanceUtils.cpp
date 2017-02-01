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
constexpr auto MIN = 10;
constexpr auto MAX = 1000;

using namespace std;

InstanceUtils::~InstanceUtils() {

}

Instance* InstanceUtils::generate(std::size_t nItems, std::size_t nKnapsacks,
		correlation correlated, bool similar, bool save) {

#define RAND(MIN, MAX, GEN) (uniform_int_distribution<int>(MIN, MAX)(GEN))

	using c = correlation;
	using uid = uniform_int_distribution<int>;

	// Create random number generator generator
	default_random_engine generator(
			chrono::system_clock::now().time_since_epoch().count());

	vector<int> capacities;

	vector<Item> items;

	// TODO Check this implementation
	if (correlated == c::NONE) {

//		uid distribution(MIN, MAX);
		uid distribution(1, MAX);

		for (int i = 0; i < nItems; i++) {

			// Knapsack Problems - page 185
			int weight = distribution(generator);
			int profit = distribution(generator);

			items.push_back(Item(weight, profit));
		}
	} else if (correlated == c::WEAK) {

//		uid distribution(MIN, MAX);
		uid distribution(1, MAX);

		for (int i = 0; i < nItems; i++) {
			// Knapsack Problems - page 185
			int weight = distribution(generator);

			int profit = RAND(std::max((weight - 100), MIN), weight + 100, generator);

			items.push_back(Item(weight, profit));
		}
	} else if (correlated == c::STRONG) {

//		uid distribution(MIN, MAX);
		uid distribution(1, MAX);

		for (int i = 0; i < nItems; i++) {
			// Knapsack Problems - page 186
			int weight = distribution(generator);

			int profit = RAND(std::max((weight - 100), MIN), weight + 100, generator);
		}
	}

	double weightSum = 0.0;

	for (int i = 0; i < nItems; ++i) {
		weightSum += items[i].weight();
	}

	if (similar) {

		double wj = 0.5 * weightSum;
		int lastCapacity = wj;

		for (int i = 0; i < nKnapsacks - 1; i++) {

			double ck = 0;

			for (int k = 0; k < i; k++) {
				ck += capacities[k];
			}
			
			
			// TUDO VERIFICAR O C DO "C"ARALHO
			// Acho que 
			uid distribution(MIN, std::max((int)(MIN + wj - ck), MIN));

			int c = distribution(generator);

			if ((MIN + wj - ck) < MIN) {
				// std::cout << "MIN: " << MIN << "\tMIN do carallho: " << MIN + wj - ck << "\tc: " << c << std::endl;
				std::cout << "MIN: " << MIN << "\tMIN do carallho: " << MIN + wj - ck << "\tc: " << c << "\twj: " << wj << "\tck: " << ck << std::endl;
			}
			capacities.push_back(c);
			if ((lastCapacity - c) < MIN)
				std::cout << "Ia dar merda" << std::endl;
			// Aqui estava dando problema na última capacidade. Pois a última capacidade é que é a atribuída ao usuário, quando o c é grande, dá problema.
			lastCapacity = ((lastCapacity - c) < MIN) ? MIN : lastCapacity - c;
		}
		std::cout << "last: " << lastCapacity << std::endl;
		capacities.push_back(lastCapacity);

	} else {

		double minBound = 0.4 * weightSum / nKnapsacks;
		double maxBound = 0.6 * weightSum / nKnapsacks;
		double lastCapacity = 0.5 * weightSum;
		
		uid distribution(minBound, maxBound);

		for (int i = 0; i < nKnapsacks - 1; i++) {
			capacities.push_back(distribution(generator));

			lastCapacity -= capacities[i];
		}

		capacities.push_back(lastCapacity);
	}

	if (save) {
		saveToFile("instance.txt", nItems, nKnapsacks, capacities, items);
	}

#undef RAND

	return new Instance(nItems, nKnapsacks, items, capacities);
}

bool InstanceUtils::saveToFile(const string& filename, size_t nItems,
		size_t nKnapsacks, const vector<int>& capacities,
		const std::vector<Item>& items) {

	ofstream file(filename.c_str());

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file << nItems << " " << nKnapsacks << "\n";

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
	auto& solution = _solution.getSolutionVector();

	int totalWeights[capacities.size()];

	std::fill(totalWeights, totalWeights + capacities.size(), 0);

	for (int i = 0; i < solution.size(); i++) {
		if (solution[i] >= 0) {
			totalWeights[solution[i]] += items[i].weight();
		}
	}

	std::cout << "*********************************************\n";
	for (auto& c : capacities) {
		std::cout << c << " ";
	}
	std::cout << "\n";

	for (auto& c : totalWeights) {
		std::cout << c << " ";
	}
	std::cout << "\n";
	std::cout << "*********************************************\n";

	for (int i = 0; i < capacities.size(); i++) {
		if (totalWeights[i] > capacities[i]) {
			return false;
		}
	}

	return true;
}

Instance* InstanceUtils::readFromFile(const std::string& filename) {

	using namespace std;

	FILE* file = fopen(filename.c_str(), "r");

	if (!file) {
		cerr << "Error opening file!\n";
		return nullptr;
	}

	size_t nItems;
	size_t nKnapsacks;

	std::vector<Item> items;
	std::vector<int> capacities;

	fscanf(file, "%ld %ld", &nItems, &nKnapsacks);
	fgetc(file);

	for (int i = 0; i < nItems; ++i) {
		int weight;
		int profit;

		int read = fscanf(file, "%d %d", &weight, &profit);

		if (read != 2) {
			cerr << "Invalid file\n";
			fclose(file);
			return nullptr;
		}

		items.push_back(Item(weight, profit));

		fgetc(file);
	}

	for (int i = 0; i < nKnapsacks; ++i) {
		int capacity;

		int read = fscanf(file, "%d", &capacity);

		if (read != 1) {
			cerr << "Invalid file\n";
			fclose(file);
			return nullptr;
		}

		capacities.push_back(capacity);

		fgetc(file);
	}

	fclose(file);

	return new Instance(nItems, nKnapsacks, items, capacities);
}

} /* namespace cfpmm */

