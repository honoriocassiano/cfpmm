// Code found at http://stackoverflow.com/questions/5279051/how-can-i-create-cartesian-product-of-vector-of-vectors

#ifndef CARTESIAN_H_
#define CARTESIAN_H_

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

#include "Instance.h"
#include "Solution.h"

using namespace std;
using namespace cfpmm;

void cartesian( Instance* instance ) {
	
	vector<int> v_set((long long int) instance->getNumKnapsacks() + 1);
	
	std::iota(v_set.begin(), v_set.end(), -1);
	
	vector<vector<int>> v  ((long long int) instance->getNumItems(), v_set);
	
	auto product = []( long long a, vector<int>& b ) { 
		return a*b.size();
	};

	const long long N = accumulate( v.begin(), v.end(), 1LL, product );

	vector<int> u(v.size());

	cfpmm::Solution bestSolution(instance);
	double bestValue = 0.0;
	
	for( long long n = 0 ; n < N ; ++n ) {

		lldiv_t q { n, 0 };

		for( long long i = v.size() - 1; 0 <= i; --i ) {

			q = div( q.quot, v[i].size() );
			u[i] = v[i][q.rem];

		}
		
		cfpmm::Solution solution(instance);
		
		// bool canUp = true;
		double value;
		
		for( int p = 0; p < u.size(); p++ ) {
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
		
		// if (canUp) {
		// 	for( int x : u ) cout << x << ' ';
		// 	cout << "\t = " << value << "\n";
		// }
		
		// Do what you want here with u.
		// for( int x : u ) cout << x << ' ';
		// cout << '\n';
	}
	
	cout << "\n\tResultado exato: \n" << bestSolution << "\t = " << bestValue << "\n";
}

#endif