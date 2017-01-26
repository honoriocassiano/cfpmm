// Code found at http://stackoverflow.com/questions/5279051/how-can-i-create-cartesian-product-of-vector-of-vectors

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

void cartesian( vector<vector<int> >& v ) {
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

// int main() {

// 	vector<int> v	{ -1, 0, 1 };
// 	vector<vector<int>> v2	(2, v);

// 	cartesian(v2);
// 	return 0;
// }