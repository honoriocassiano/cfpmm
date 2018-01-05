/*
 * Instance.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Instance.h"

namespace cfpmm {

Instance::Instance(const std::vector<Item>& _items,
		const std::vector<int>& _capacities) :
		nItems(_items.size()), nKnapsacks(_capacities.size()), items(_items), capacities(
				_capacities) {

}

Instance::~Instance() {

}

} /* namespace cfpmm */
