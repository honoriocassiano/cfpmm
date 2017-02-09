//============================================================================
// Name        : CFPMM.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <thread>

#include "Debug.h"
#include "Colony.h"
#include "Instance.h"
#include "InstanceUtils.h"
#include "Item.h"
#include "Solution.h"
#include "Exact.h"

using namespace std;

int main(void) {

	using namespace cfpmm;

//	InstanceUtils::generate(10 , 5, correlation::WEAK, true);

// Instância do Geovani
// std::vector<int> capacities { 6, 11, 55, 10, 2, 44, 5 };

// std::vector<Item> items { Item(6, 4), Item(6, 20), Item(6, 4), Item(6, 20), Item(6, 4), Item(6, 20), Item(3, 9), Item(12, 15), Item(3, 1) };

// Instância gerada
//	std::vector<int> capacities { 1499, 78, 336 };
//	std::vector<Item> items { Item(487, 456), Item(269, 209), Item(542, 638),
//			Item(169, 70), Item(543, 518), Item(859, 956), Item(916, 889), Item(878, 828), Item(116, 105), Item(102, 159) };

//	std::vector<int> capacities { 1499, 78, 336, 492, 35 };
//
//	std::vector<Item> items { Item(487, 456), Item(269, 209), Item(542, 638),
//			Item(169, 70), Item(543, 518), Item(859, 956), Item(916, 889), Item(
//					878, 828), Item(116, 105), Item(102, 159) };

	std::vector<int> capacities { 1499, 78, 336, 492, 35 };

	std::vector<Item> items { Item(487, 456), Item(269, 209), Item(542, 638), Item(542, 638), 
			Item(169, 70), Item(543, 518), Item(859, 956), Item(859, 956), Item(859, 956), Item(
					878, 828) };

	Instance* instance = new Instance(items.size(), capacities.size(), items,
			capacities);

	const size_t _threads = 4;
	
	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
	unsigned concurentThreadsUsed = _threads > concurentThreadsSupported ? 
			concurentThreadsSupported : _threads;

	std::cout << "Processadores disponíveis: " << concurentThreadsSupported << std::endl;
	std::cout << "Threads instanciadas: " << _threads << std::endl;

	auto exact = Exact(instance);

	const clock_t begin_time_exact = clock();

	auto solution = exact.solve(_threads);

	std::cout << "Tempo de execução (Seg): "
			<< (float(clock() - begin_time_exact) / CLOCKS_PER_SEC) / concurentThreadsUsed << std::endl;

	std::cout << "\n\tResultado exato: \n" << solution << "\t = "
			<< solution.getValue() << "\n";

//	//	auto solution = exact.solve();
//
//	// Exact result
//	//	std::cout << "\n\tResultado exato: \n" << solution << "\t = "
//	//			<< solution.getValue() << "\n";
//
//	//	 std::cout << "Tempo de execução (Seg): " << float( clock () - begin_time_exact ) /  CLOCKS_PER_SEC << std::endl;
//
//	Colony* colony = new Colony(instance, 10, 0.9, 1, 1);
//
//	//	 const clock_t begin_time_colony = clock();
//
//	auto sol = colony->run();
//
//	std::cout << "\n\tResultado da colonia de antas:\n" << std::get<0>(sol)
//			<< "\t = " << std::get<0>(sol).getValue() << std::endl;
//	std::cout << "\n\tNúmero de iterações:\n" << std::get<1>(sol) << std::endl;
//
//	//	 std::cout << "Tempo de execução (Seg): " << float( clock () - begin_time_colony ) /  CLOCKS_PER_SEC << std::endl;

	return 0;
}
