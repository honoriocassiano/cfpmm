/*
 * Instance.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <cstddef>
#include <vector>

namespace cfpmm {

class Solution;
class Ant;

class Instance {
public:
	Instance(std::size_t nItems, std::size_t nKnacksacks,
			const std::vector<int>& weigths, const std::vector<int>& profits,
			const std::vector<int>& capacities);

	virtual ~Instance();

private:
	std::size_t nItems;
	std::size_t nKnacksacks;
	std::vector<int> weigths;
	std::vector<int> profits;
	std::vector<int> capacities;

	friend class Solution;
	friend class Ant;
};

} /* namespace cfpmm */

#endif /* INSTANCE_H_ */
