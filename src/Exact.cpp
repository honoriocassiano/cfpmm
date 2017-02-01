/*
 * Exact.cpp
 *
 *  Created on: 1 de fev de 2017
 *      Author: aluno
 */

#include "Exact.h"

#include "flags.h"

#include <cstdlib>
#include <cmath>

#include <numeric>
#include <vector>

#if DEBUG
#include <cstdio>
#endif

namespace cfpmm {

Exact::Exact(const Instance* _instance) :
		instance(_instance) {
}

Exact::~Exact() {
}

Solution Exact::solve() const {
	std::vector<int> v_set((long long int) instance->getNumKnapsacks() + 1);

	std::iota(v_set.begin(), v_set.end(), -1);

	std::vector<std::vector<int>> v((long long int) instance->getNumItems(),
			v_set);

	const long long N = std::pow((long long) instance->getNumKnapsacks() + 1,
			(long long) instance->getNumItems());

	std::vector<int> u(v.size());

	Solution bestSolution(instance);
	double bestValue = 0.0;

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

	return bestSolution;
}
}
