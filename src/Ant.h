/*
 * Ant.h
 *
 *  Created on: 23 de out de 2016
 *      Author: cassiano
 */

#ifndef ANT_H_
#define ANT_H_

#include "Instance.h"
#include "Solution.h"

namespace cfpmm {

/**
 * Class that represent an ant of a colony
 */
class Ant {
public:

	/**
	 * Initializer for an ant
	 * @param instance instance of the problem
	 */
	Ant(Instance* instance, std::vector<std::vector<double> >& pheromoneList);
	virtual ~Ant();

	/**
	 * Getter for the solution
	 */
	const Solution& getSolution() const {
		return solution;
	}

private:

	/**
	 * Generate a initial solution
	 */
	void generateInitialSolution();

	std::vector<std::vector<double> >& pheromoneList;

private:

	Solution solution; /**< Solution carried by ant */
};

} /* namespace cfpmm */

#endif /* ANT_H_ */
