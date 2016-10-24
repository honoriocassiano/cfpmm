/*
 * InstanceGenerator.h
 *
 *  Created on: 20 de out de 2016
 *      Author: aluno
 */

#ifndef INSTANCEUTILS_H_
#define INSTANCEUTILS_H_

#include <cstddef>
#include <vector>
#include <string>

#include "Instance.h"
#include "Solution.h"
#include "Item.h"

namespace cfpmm {

/**
 * Enumeration that indicate correlation type between items profits and weights.
 */
enum class correlation {
	NONE, /**< Profits and weights will be generate randomly */
	WEAK, /**< Weight will be generated randomly and profit will be generated randomly between a threshold around generated weight */
	STRONG /**< Weight will be generated randomly and profit will be proportional to generated weight */
};

/**
 * Class that generate and save instances of multiple knapsacks problem
 */
class InstanceUtils {
public:
	virtual ~InstanceUtils();

	/**
	 * Generate an instance of a problem.
	 * @param nItems number of items
	 * @param nKnapsacks number of knapsacks
	 * @param correlated type of correlation between profits and weights of the items
	 * @param similar flag that indicate if knapsacks capacities must be similar or not
	 * @param save flag that indicate if the generated instance must be save in a file
	 *
	 * @return New instance of problem
	 */
	static Instance* generate(std::size_t nItems, std::size_t nKnapsacks,
			correlation correlated, bool similar, bool save = true);

	/**
	 * Save an instance in a file.
	 * @param filename name of file that the instance will be saved
	 * @param nItems number of items
	 * @param nKnapsacks number of knapsacks
	 * @param capacities list of knapsacks capacities
	 * @param items list of items
	 *
	 * @return true if file was saved and false if an error occurred
	 */
	static bool saveToFile(const std::string& filename, std::size_t nItems,
			std::size_t nKnapsacks, const std::vector<int>& capacities,
			const std::vector<Item>& items);

	/**
	 * Reads a instance from a file
	 * @param filename name of file
	 *
	 * return The instance of problem or null if an error occurred
	 */
	static Instance* readFromFile(const std::string& filename);

	/**
	 * Check if a solution is valid
	 *
	 * @param solution Solution to be checked
	 *
	 * @return true if is valid or false if not
	 */
	static bool isValidSolution(const Solution& solution);
};

} /* namespace cfpmm */

#endif /* INSTANCEUTILS_H_ */
