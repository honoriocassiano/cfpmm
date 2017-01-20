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
	Ant(Instance* instance, std::vector<std::vector<double> >& pheromoneList, double alpha, double beta);
	virtual ~Ant();

	/**
	 * Getter for the solution
	 */
	const Solution& getSolution() const {
		return solution;
	}

	double getValue() const {
		return solution.getValue();
	}

	void findSolution();

private:

	bool loop();

	/**
	 * Generate a initial solution
	 */
	void generateInitialSolution();

	double calculateProbability(int item, int knapsack);

	std::vector<std::vector<double> >& pheromoneList;

private:

	double alpha;
	double beta;

	Solution solution; /**< Solution carried by ant */
	const Instance* instance;
};

} /* namespace cfpmm */

#endif /* ANT_H_ */
