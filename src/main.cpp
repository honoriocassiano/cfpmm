//============================================================================
// Name        : CFPMM.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "InstanceUtils.h"
#include "Instance.h"
#include "Solution.h"
#include "Ant.h"

#include <iostream>

int main(void) {

	using namespace cfpmm;

//	InstanceUtils::generate(10, 5, correlation::WEAK, true);

	std::vector<int> capacities { 10, 21, 52, 33 };

	std::vector<Item> items { Item(5, 4), Item(10, 64), Item(3, 9), Item(19, 5),
			Item(11, 8), Item(8, 18), Item(7, 4), Item(7, 5) };

	Instance* instance = new Instance(items.size(), capacities.size(), items,
			capacities);

//	 Solution* solution = new Solution(instance);
//
//	 std::vector<int> _s { -1, -1, -1, 1, -1, -1, -1, -1 };
//
//	 auto& s = solution->getSolution();
//
//	 s = _s;


	Ant* ant = new Ant(instance);

	auto solution = ant->getSolution();

	std::cout << (InstanceUtils::isValidSolution(solution) ? "true" : "false") << "\n";
	std::cout << solution << std::endl;


	return 0;
}
