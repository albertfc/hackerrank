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

uint64_t bricks_dp( vector<uint64_t> & stack ) {

	auto n = stack.size();
	uint64_t tab[n+1];
	uint64_t sum[3] = {0,0,0};

	tab[n] = 0;
	for( int i=n-1; i>=0; i-- ) {
		sum[2] = sum[1];
		sum[1] = sum[0];
		if( i != (int)n-1 ) {
			sum[0] = stack[i+1] + sum[1];
		}
		if( i>(int)n-4 ) {
			tab[i] = stack[i] + tab[i+1];
			continue;
		}
		tab[i] = 0;
		uint64_t hand = 0;
		for( size_t j=0; j<3; j++ ) {
			hand += stack[i+j];
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

