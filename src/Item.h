/*
 * Item.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef ITEM_H_
#define ITEM_H_

namespace cfpmm {

class Item {
public:
	Item(int weight, int profit) :
		_weight(weight), _profit(profit) {
	}

	virtual ~Item() {}

	int weight() const { return _weight; }
	int profit() const { return _profit; }

private:
	int _weight;
	int _profit;
};

} /* namespace cfpmm */

#endif /* ITEM_H_ */
