/*
 * Colony.cpp
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#include "Colony.h"

namespace cfpmm {

Colony::Colony() {

}

Colony::~Colony() {

	for(auto& ant : ants) {
		delete ant;
	}
}

} /* namespace cfpmm */
