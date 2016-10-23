/*
 * Item.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef ITEM_H_
#define ITEM_H_

namespace cfpmm {

/**
 * Class that represent an item
 */
class Item {
public:

	Item(int weight, int profit) :
			_weight(weight), _profit(profit) {
	}

	virtual ~Item() {
	}

	/**
	 * Getter for weight
	 */
	int weight() const {
		return _weight;
	}

	/**
	 * Getter for profit
	 */
	int profit() const {
		return _profit;
	}

private:
	int _weight; /**< Weight of item */
	int _profit; /**< Profit of item */
};

} /* namespace cfpmm */

#endif /* ITEM_H_ */
