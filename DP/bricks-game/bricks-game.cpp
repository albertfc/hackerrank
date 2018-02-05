/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

typedef pair<uint64_t,uint64_t> res_t;
res_t bricks_rec( vector<uint64_t> & stack, size_t top, bool player ) {
	res_t res = res_t(0,0);

	uint64_t score = 0;
	for( int i = 0; i < 3; i++ ) {
		if( top+i < stack.size() ) {
			score += stack[top+i];
			res_t aux = bricks_rec( stack, top+i+1, !player );
			aux = (player) ? res_t( aux.first + score, aux.second ) : res_t( aux.first, aux.second + score );
			res = (player) ? (aux.first  > res.first ) ? aux : res
			               : (aux.second > res.second) ? aux : res;
		}
	}
	return res;
}

#define K 3
uint64_t bricks_dp( vector<uint64_t> & stack ) {

	auto n = stack.size();
	uint64_t tab[n+1]; // tab[i] contains the max score with a stack of size [i:n]
	uint64_t sum[K] = {0}; // sum[0] is the sum of stack from i+1 till the end, sum2 from i+2, etc

	// Init tab and sum from end to n-(K+1)
	tab[n]   = 0;
	tab[n-1] = stack[n-1];
	for( int i=n-2; i>(int)n-(K+1); i-- ) {
		for( int l=K-1; l>0; l-- )
			sum[l] = sum[l-1];
		sum[0] = stack[i+1] + sum[1];
		tab[i] = stack[i] + tab[i+1];
	}

	for( int i=n-(K+1); i>=0; i-- ) {
		for( int l=K-1; l>0; l-- )
			sum[l] = sum[l-1];
		sum[0] = stack[i+1] + sum[1];
		tab[i] = 0;
		uint64_t hand = 0;
		for( size_t j=0; j<K; j++ ) {
			hand += stack[i+j];
			// current score is the sum of popped bricks plus what we scored in the previous play
			// previous score is the total amount up to that point minus what our oponent earned (sum[j] - tab[i+j+1])
			// best score is the max of the K plays
			tab[i] = std::max( tab[i], hand + sum[j] - tab[i+j+1] );
		}
	}

	return tab[0];
}

uint64_t bricks( vector<uint64_t> & stack ) {

	//return bricks_rec( stack, 0, true ).first;
	return bricks_dp( stack );
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int t;
	cin >> t;
	for(int64_t a0 = 0; a0 < t; a0++){
		int n;
		cin >> n;
		vector<uint64_t> arr(n);
		for(int arr_i = 0; arr_i < n; arr_i++){
			cin >> arr[arr_i];
		}
		uint64_t result = bricks(arr);
		cout << result << endl;
	}
	return 0;
}

