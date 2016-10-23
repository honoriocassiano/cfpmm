/*
 * InstanceGenerator.h
 *
 *  Created on: 20 de out de 2016
 *      Author: aluno
 */

#ifndef INSTANCEGENERATOR_H_
#define INSTANCEGENERATOR_H_

#include <cstddef>
#include <vector>
#include <string>

namespace cfpmm {

/**
 * Enum that indicate correlation type between items profits and weights.
 */
enum class correlation {
	NONE, /**< Profits and weights will be generate randomly */
	WEAK, /**< Weight will be generated randomly and profit will be generated randomly between a threshold around generated weight */
	STRONG /**< Weight will be generated randomly and profit will be proportional to generated weight */
};

/**
 * Class that generate and save instances of multiple knacksacks problem
 */
class InstanceGenerator {
public:
	InstanceGenerator();
	virtual ~InstanceGenerator();

	/**
	 * Generate an instance of a problem.
	 * @param nItems number of items
	 * @param nKnacksacks number of knacksacks
	 * @param correlated type of correlation between profits and weights of the items
	 * @param similar flag that indicate if knacksacks capacities must be similar or not
	 * @param save flag that indicate if the generated instance must be save in a file
	 */
	static void generate(std::size_t nItems, std::size_t nKnacksacks,
			correlation correlated, bool similar, bool save = true);

	/**
	 * Save an instance in a file.
	 * @param filename name of file that the instance will be saved
	 * @param nItems number of items
	 * @param nKnacksacks number of knacksacks
	 * @param weights list of items weights
	 * @param profits list of items profits
	 * @param capacities list of knacksacks capacities
	 *
	 * @return true if file was saved and false if an error occurred
	 */
	static bool saveToFile(const std::string& filename, std::size_t nItems,
			std::size_t nKnacksacks, const std::vector<int>& weigths,
			const std::vector<int>& profits, const std::vector<int>& capacities);
};

} /* namespace cfpmm */

#endif /* INSTANCEGENERATOR_H_ */
