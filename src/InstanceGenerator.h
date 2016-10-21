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

enum class correlation {
	NONE, WEAK, STRONG
};

class InstanceGenerator {
public:
	InstanceGenerator();
	virtual ~InstanceGenerator();

	static void generate(std::size_t nItems, std::size_t nKnacksacks,
			correlation correlated, bool similar);

	static bool saveToFile(const std::string& filename, std::size_t nItems,
			std::size_t nKnacksacks, const std::vector<int>& weigths,
			const std::vector<int>& prices, const std::vector<int>& capacities);
};

} /* namespace cfpmm */

#endif /* INSTANCEGENERATOR_H_ */
