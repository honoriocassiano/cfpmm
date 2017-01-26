// Code found at http://stackoverflow.com/questions/5279051/how-can-i-create-cartesian-product-of-vector-of-vectors

#ifndef CARTESIAN_H_
#define CARTESIAN_H_

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

void cartesian( int nItems,  int nKnapsacks) {
	
	vector<int> v_set(nKnapsacks+1);
	
	std::iota(v_set.begin(), v_set.end(), -1);
	
	vector<vector<int>> v  (nItems, v_set);
	
	auto product = []( long long a, vector<int>& b ) { 
		return a*b.size();
	};

	const long long N = accumulate( v.begin(), v.end(), 1LL, product );

	vector<int> u(v.size());

	for( long long n = 0 ; n < N ; ++n ) {

		lldiv_t q { n, 0 };

		for( long long i = v.size() - 1; 0 <= i; --i ) {

			q = div( q.quot, v[i].size() );
			u[i] = v[i][q.rem];

		}
		
		// Do what you want here with u.
		for( int x : u ) cout << x << ' ';
		cout << '\n';
	}
}

#endif