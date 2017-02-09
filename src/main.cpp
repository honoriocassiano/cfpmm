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
#include <string>
#include <fstream>

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

	// ================== GERA AS 10 INSTÂNCIAS =====================
	/*
	 for (int i = 1; i < 11; ++i) {
	 InstanceUtils::generate(i, 10 , i, correlation::WEAK, true);
	 }
	 */
	// ===============================================================
	// ================= RESOLVE PELO MÉTODO EXATO ===================
	/*
	 const size_t _threads = 1;
	 std::vector<int> capacities { 6, 11, 55, 10, 2, 44, 5 };
	 std::vector<Item> items { Item(6, 4), Item(6, 20), Item(6, 4),
	 Item(6, 20), Item(6, 4), Item(6, 20),
	 Item(3, 9), Item(12, 15), Item(3, 1) };

	 auto exact = Exact(instance);

	 const clock_t begin_time_exact = clock();

	 auto solution = exact.solve(_threads);

	 std::cout << "Tempo de execução (Seg): "
	 << (float(clock() - begin_time_exact) / CLOCKS_PER_SEC) / concurentThreadsUsed << std::endl;

	 std::cout << "\n\tResultado exato: \n" << solution << "\t = "
	 << solution.getValue() << "\n";
	 */
	// ===============================================================
	// ================ RESOLVE PELA META-HEURISTICA =================
	/*
	 std::vector<int> capacities { 6, 11, 55, 10, 2, 44, 5 };
	 std::vector<Item> items { Item(6, 4), Item(6, 20), Item(6, 4),
	 Item(6, 20), Item(6, 4), Item(6, 20),
	 Item(3, 9), Item(12, 15), Item(3, 1) };

	 Colony* colony = new Colony(instance, 10, 0.9, 1, 1);
	 const clock_t begin_time_colony = clock();
	 auto sol = colony->run();

	 std::cout << "\n\tResultado da colonia de antas:\n" << std::get<0>(sol)
	 << "\t = " << std::get<0>(sol).getValue() << std::endl;
	 std::cout << "\n\tNúmero de iterações:\n" << std::get<1>(sol) << std::endl;

	 std::cout << "Tempo de execução (Seg): " << float( clock () - begin_time_colony ) /  CLOCKS_PER_SEC << std::endl;
	 */
	// ===============================================================
	// ====================== EXEMPLO DE TESTE =======================
	/*
	 std::vector<int> capacities { 1499, 78, 336, 492, 35 };

	 std::vector<Item> items { Item(487, 456), Item(269, 209), Item(542, 638),
	 Item(169, 70), Item(543, 518), Item(859, 956), Item(859, 956),
	 Item(878, 828), Item(878, 828), Item(878, 828) };

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
	 */
	// ===============================================================

	// ============== EXECUTA TESTE DAS 10 INSTÂNCIAS ================
/*
	std::ofstream file("../results/results.csv");

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file
			<< "nItens,nKnapsacks,ExactTime,ColonyTime,ExactResult,ColonyResult,iterations\n";

	for (int i = 1; i < 11; ++i) {

		file.flush();
		auto instance = InstanceUtils::readFromFile(
				"../instances/instance" + std::to_string(i) + ".txt");

		unsigned concurentThreadsUsed = std::thread::hardware_concurrency();

		const clock_t begin_time_exact = clock();

		auto exact = Exact(instance);
		auto solutionExact = exact.solve(concurentThreadsUsed);

		float time_exact = (float(clock() - begin_time_exact) / CLOCKS_PER_SEC) / concurentThreadsUsed;

		Colony* colony = new Colony(instance, X, 0.9, 1, 1);

		const clock_t begin_time_colony = clock();

		auto solutionColony = colony->run();

		float time_colony = float(clock() - begin_time_colony) / CLOCKS_PER_SEC;

		file << (i * 2) << "," << i << "," << time_exact << ","
				<< time_colony << "," << solutionExact.getValue() << ","
				<< std::get<0>(solutionColony).getValue() << "," << std::get<1>(solutionColony)
				<< "\n";
	}
*/
	// ===============================================================

	// =========== EXECUTA TESTE EXATO DAS 10 INSTÂNCIAS =============
/*
	std::ofstream file("../results/exact_results.csv");

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file
			<< "nItens,nKnapsacks,ExactTime,ExactResult\n";

	for (int i = 1; i < 11; ++i) {

		file.flush();
		auto instance = InstanceUtils::readFromFile(
				"../instances/instance" + std::to_string(i) + ".txt");

		unsigned concurentThreadsUsed = std::thread::hardware_concurrency();

		const clock_t begin_time_exact = clock();

		auto exact = Exact(instance);
		auto solutionExact = exact.solve(concurentThreadsUsed);

		float time_exact = (float(clock() - begin_time_exact) / CLOCKS_PER_SEC) / concurentThreadsUsed;

		file << 10 << "," << i << "," << time_exact
				<< "," << solutionExact.getValue() << "\n";
		file.close();
	}
*/
	// ===============================================================


	// ======= EXECUTA META-HEURISTICOS DAS 10 INSTÂNCIAS =============
/*
	std::ofstream file("../results/heuristic_results.csv");

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file
			<< "nItens,nKnapsacks,ColonyTime,ColonyResult,iterations\n";

	for (int i = 1; i < 11; ++i) {

		file.flush();
		auto instance = InstanceUtils::readFromFile(
				"../instances/instance" + std::to_string(i) + ".txt");

		unsigned concurentThreadsUsed = std::thread::hardware_concurrency();


		Colony* colony = new Colony(instance, 10, 0.9, 1, 1);

		const clock_t begin_time_colony = clock();

		auto solutionColony = colony->run();

		float time_colony = float(clock() - begin_time_colony) / CLOCKS_PER_SEC;

		file << 10 << "," << i << "," << time_colony << "," << 
			std::get<0>(solutionColony).getValue() << "," << std::get<1>(solutionColony) << "\n";

	}
*/
	// ===============================================================


	// ======= EXECUTA META-HEURISTICOS DAS INSTÂNCIAS > 10 ==========

	std::ofstream file("../results/heuristic_results_after10.csv");

	if (!file.is_open()) {
		std::cerr << "Error opening file\n";
		return false;
	}

	file
			<< "nItens,nKnapsacks,ColonyTime,ColonyResult,iterations\n";

	for (int i = 11; i < 11; ++i) {

		file.flush();
		auto instance = InstanceUtils::readFromFile(
				"../instances/instance" + std::to_string(i) + ".txt");

		unsigned concurentThreadsUsed = std::thread::hardware_concurrency();


		Colony* colony = new Colony(instance, 10, 0.9, 1, 1);

		const clock_t begin_time_colony = clock();

		auto solutionColony = colony->run();

		float time_colony = float(clock() - begin_time_colony) / CLOCKS_PER_SEC;

		file << 10 << "," << i << "," << time_colony << "," << 
			std::get<0>(solutionColony).getValue() << "," << std::get<1>(solutionColony) << "\n";

	}

	// ===============================================================
	file.close();
	return 0;
}
