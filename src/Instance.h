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

#include "Item.h"

namespace cfpmm {

class Solution;
class Ant;
class Colony;

class Instance {
public:
	/**
	 * @param nItems Number of items
	 * @param nKnapsacks Number of knapsacks
	 * @param items List of items
	 * @param capacities List of knapsacks
	 */
	Instance(std::size_t nItems, std::size_t nKnapsacks,
			const std::vector<Item>& items, const std::vector<int>& capacities);

	virtual ~Instance();

	/**
	 * @return List of items.
	 */
	const std::vector<Item>& getItems() const {
		return items;
	}

	/**
	 * @return List of capacities.
	 */
	const std::vector<int>& getCapacities() const {
		return capacities;
	}

	/**
	 * @return Number of items.
	 */
	std::size_t getNumItems() const {
		return nItems;
	}

	/**
	 * @return Number of knapsacks.
	 */
	std::size_t getNumKnapsacks() const {
		return nKnapsacks;
	}

private:

	/**
	 * Number of items.
	 */
	std::size_t nItems;

	/**
	 * Number of knapsacks.
	 */
	std::size_t nKnapsacks;

	/**
	 * List of items.
	 */
	std::vector<Item> items;

	/**
	 * List of capaticies.
	 */
	std::vector<int> capacities;

	friend class Solution;
	friend class Ant;
	friend class Colony;
};

} /* namespace cfpmm */

#endif /* INSTANCE_H_ */
