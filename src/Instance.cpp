/*
 * Instance.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Instance.h"

namespace cfpmm {

Instance::Instance(std::size_t _nItems, std::size_t _nKnacksacks,
		const std::vector<int>& _weigths, const std::vector<int>& _profits,
		const std::vector<int>& _capacities) :
		nItems(_nItems), nKnacksacks(_nKnacksacks), weigths(_weigths), profits(
				_profits), capacities(_capacities) {

}

Instance::~Instance() {

}

} /* namespace cfpmm */
