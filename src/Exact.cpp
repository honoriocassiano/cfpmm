/*
 * Exact.cpp
 *
 *  Created on: 1 de fev de 2017
 *      Author: aluno
 */

#include "Exact.h"

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

namespace cfpmm {

Exact::Exact(const Instance* _instance) :
		instance(_instance) {
}

Exact::~Exact() {
}

Solution Exact::solve() {
	std::vector<int> v_set((long long int) instance->getNumKnapsacks() + 1);

	std::iota(v_set.begin(), v_set.end(), -1);

	std::vector<std::vector<int>> v((long long int) instance->getNumItems(), v_set);

	auto product = []( long long a, std::vector<int>& b ) {
		return a*b.size();
	};

	const long long N = std::accumulate(v.begin(), v.end(), 1LL, product);

	std::vector<int> u(v.size());

	Solution bestSolution(instance);
	double bestValue = 0.0;

	for (long long n = 0; n < N; ++n) {

		lldiv_t q { n, 0 };

		for (long long i = v.size() - 1; 0 <= i; --i) {

			q = std::div(q.quot, v[i].size());
			u[i] = v[i][q.rem];

		}

		Solution solution(instance);

		// bool canUp = true;
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
					// canUp = false;
					break;
				}
			}
		}
	}

	return bestSolution;
}
}
