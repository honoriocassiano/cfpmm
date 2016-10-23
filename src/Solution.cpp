/*
 * Solution.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Solution.h"

#include <cassert>

namespace cfpmm {

Solution::Solution(Instance* _instance) : instance(_instance) {
	assert(_instance != nullptr);
}

Solution::~Solution() {

}

} /* namespace cfpmm */

void cfpmm::Solution::clear() {
}
