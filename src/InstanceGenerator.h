/*
 * InstanceGenerator.h
 *
 *  Created on: 20 de out de 2016
 *      Author: aluno
 */

#ifndef INSTANCEGENERATOR_H_
#define INSTANCEGENERATOR_H_

#include <cstddef>

namespace cfpmm {

class InstanceGenerator {
public:
	InstanceGenerator();
	virtual ~InstanceGenerator();

	static void generate(std::size_t nItems, std::size_t nKnacksacks, int correlated, bool similar);
};

} /* namespace cfpmm */

#endif /* INSTANCEGENERATOR_H_ */
