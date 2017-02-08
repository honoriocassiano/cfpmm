/*
 * Exact.cpp
 *
 *  Created on: 1 de fev de 2017
 *      Author: aluno
 */

#include "Exact.h"

#include "flags.h"

#include <pthread.h>

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <numeric>
#include <vector>

#if DEBUG
#include <cstdio>
#endif

namespace cfpmm {

struct _thread_arg {
	const Exact * exact;
	long long unsigned start;
	long long unsigned end;
};

Exact::Exact(const Instance* _instance) :
		instance(_instance) {
}

Exact::~Exact() {
}

Solution Exact::solve(std::size_t _threads) const {
	std::vector<int> v_set((long long int) instance->getNumKnapsacks() + 1);

	std::iota(v_set.begin(), v_set.end(), -1);

	std::vector<std::vector<int>> v((long long int) instance->getNumItems(),
			v_set);

	const long long N = std::pow((long long) instance->getNumKnapsacks() + 1,
			(long long) instance->getNumItems());

	std::vector<int> u(v.size());

	Solution bestSolution(instance);
	double bestValue = 0.0;

	if (_threads == 1) {
#if DEBUG
		int progress = 1;
#endif

		for (long long n = 0; n < N; ++n) {

#if DEBUG
			auto temp = (int) (n * 100.0 / N) + 1;

			if (temp > progress) {
				std::printf("\rProgresso: %d%%", temp);
				std::fflush(stdout);

				progress = temp;
			}
#endif

			lldiv_t q { n, 0 };

			for (long long i = v.size() - 1; 0 <= i; --i) {

				q = std::div(q.quot, v[i].size());
				u[i] = v[i][q.rem];

			}

			Solution solution(instance);

			double value;

			for (int p = 0; p < u.size(); p++) {
				if (u[p] != -1) {
					if (solution.canUpdate(p, u[p])) {
						solution.update(p, u[p]);
						value = solution.getValue();

						if (value > bestValue) {
							bestValue = value;
							bestSolution = solution;
						}
					} else {
						solution.clear();
						break;
					}
				}
			}
		}

#if DEBUG
		std::printf("\n");
#endif
	} else {
		long long unsigned step = N / _threads;

		std::vector<std::pair<std::size_t, std::size_t>> indices;

		long long unsigned current = 0;

		for (int i = 0; i < _threads; ++i) {
			auto next = current + step;

			if (next > N) {
				next = N;
			}

			indices.push_back(std::make_pair(current, next));

			current += step;
		}

		std::vector<thread_arg> arguments;
		std::vector<pthread_t> threads;
		std::vector<Solution*> solutions;

		for (int i = 0; i < _threads; ++i) {
			arguments.push_back(
					thread_arg { this, indices[i].first, indices[i].second });

			threads.push_back(pthread_t());

			solutions.push_back(nullptr);
		}

		for (int i = 0; i < _threads; ++i) {
			pthread_create(&threads[i], nullptr, Exact::parallelSolve,
					&arguments[i]);
		}

		for (int i = 0; i < _threads; ++i) {
			pthread_join(threads[i], (void**) &solutions[i]);
		}

		for (const auto& sol : solutions) {
			if(sol->getValue() > bestSolution.getValue()) {
				bestSolution = *sol;
			}
		}

		for (const auto& sol : solutions) {
			delete sol;
		}
	}

	return bestSolution;
}

void* Exact::parallelSolve(void* param) {

	auto arg = (thread_arg*) param;

	auto exact = arg->exact;

	std::vector<int> v_set((long long int) exact->getInstance()->getNumKnapsacks() + 1);

	std::iota(v_set.begin(), v_set.end(), -1);

	std::vector<std::vector<int>> v((long long int) exact->getInstance()->getNumItems(),
			v_set);

	std::vector<int> u(v.size());

	Solution* bestSolution = new Solution(exact->getInstance());
	double bestValue = 0.0;

	for (long long n = arg->start; n < arg->end; ++n) {

		lldiv_t q { n, 0 };

		for (long long i = v.size() - 1; 0 <= i; --i) {

			q = std::div(q.quot, v[i].size());
			u[i] = v[i][q.rem];
		}

		Solution solution(exact->getInstance());

		double value;

		for (int p = 0; p < u.size(); p++) {
			if (u[p] != -1) {
				if (solution.canUpdate(p, u[p])) {
					solution.update(p, u[p]);
					value = solution.getValue();

					if (value > bestValue) {
						bestValue = value;
						*bestSolution = solution;
					}
				} else {
					solution.clear();
					break;
				}
			}
		}
	}

	return bestSolution;
}

}
