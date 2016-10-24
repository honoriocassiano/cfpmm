/*
 * Instance.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Instance.h"

namespace cfpmm {

Instance::Instance(std::size_t _nItems, std::size_t _nKnapsacks,
		const std::vector<Item>& _items,
		const std::vector<int>& _capacities) :
		nItems(_nItems), nKnapsacks(_nKnapsacks), items(_items), capacities(_capacities) {

}

Instance::~Instance() {

}

} /* namespace cfpmm */
