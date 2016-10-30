/*
 * Colony.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef COLONY_H_
#define COLONY_H_

#include <vector>

#include "Ant.h"
#include "Instance.h"

namespace cfpmm {

class Colony {
public:
	Colony(Instance* instance, std::size_t nAnts, float evaporationRatio);
	virtual ~Colony();

	const std::vector<std::vector<double>>& getPheromoneList() const {
		return pheromoneList;
	}

	const std::vector<Ant*>& getAnts() const {
		return ants;
	}

private:

	void initialize();

	void evaporate();
	void reinforce();

	std::size_t nAnts;

	Instance* instance;

	std::vector<Ant*> ants;

	float evaporationRatio;

	std::vector<std::vector<double>> pheromoneList;
};

} /* namespace cfpmm */

#endif /* COLONY_H_ */
