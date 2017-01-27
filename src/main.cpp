//============================================================================
// Name        : CFPMM.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iomanip>
#include <iostream>
#include <vector>

#include "Utils.h"

#define DEBUG

#include "Colony.h"
#include "Instance.h"
#include "Item.h"
#include "Solution.h"
#include "Cartesian.h"

int main(void) {

	using namespace cfpmm;



	// Instância do Geovani
	std::vector<int> capacities { 6, 11, 55, 10, 2, 44, 5 };

	std::vector<Item> items { Item(6, 4), Item(6, 20), Item(6, 4), Item(6, 20), Item(6, 4), Item(6, 20), Item(3, 9), Item(12, 15), Item(3, 1) };

	Instance* instance = new Instance(items.size(), capacities.size(), items,
			capacities);

	
	cartesian(instance);
	
/*
//	InstanceUtils::generate(10, 5, correlation::WEAK, true);

//	std::vector<int> capacities { 10, 21, 52, 33 };
//	std::vector<int> capacities { 10, 21, 52, 33, 5 };
//	std::vector<int> capacities { 2, 15, 22, 17, 5 };

	// Instância do Geovani
	std::vector<int> capacities { 6, 11, 4, 13 };

	std::vector<Item> items { Item(5, 4), Item(10, 20), Item(3, 9), Item(12, 15),
				Item(3, 1), Item(5, 1) };
//	std::vector<Item> items { Item(5, 4), Item(10, 64), Item(3, 9), Item(13, 5),
//			Item(11, 8), Item(8, 18), Item(7, 4), Item(7, 5) };

	Instance* instance = new Instance(items.size(), capacities.size(), items,
			capacities);

	Colony* colony = new Colony(instance, 1, 0.9, 1, 1);

	Solution sol = colony->run();

	std::cout << "Capacidades:" << std::endl;
//	printVector(instance->getCapacities());
	//**********************************************************
	for (auto& v : instance->getCapacities()) {
		std::cout << std::setw(3) << v << " ";
	}
	std::cout << std::endl;
	//**********************************************************

	std::cout << std::endl;

	std::cout << "Pesos:" << std::endl;
	for (auto& i : instance->getItems()) {
		std::cout << std::setw(3) << i.weight() << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Item/mochila:" << std::endl;
	std::cout << sol << std::endl << std::endl;

	std::vector<int> ocupado(instance->getCapacities().size(), 0);

	const auto& temp = sol.getSolutionVector();

	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i] != -1) {
			ocupado[temp[i]] +=
					const_cast<const Instance*>(instance)->getItems()[i].weight();
		}
	}

	std::cout << "Capacidade/Uso:" << std::endl;
//	printVector(ocupado);
	//**********************************************************
	for (auto& v : ocupado) {
		std::cout << std::setw(3) << v << " ";
	}
	std::cout << std::endl;
	//**********************************************************

	std::cout << std::endl;
*/
	return 0;
}
