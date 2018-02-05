#include <bits/stdc++.h>

using namespace std;

int unboundedKnapsack_rec(int k, vector <int> & arr, int i ) {
	if( i < 0 || k <= 0 )
		return 0;

	int aux = unboundedKnapsack_rec( k, arr, i-1 );
	if( arr[i] >  k )
		return aux;
	return std::max( aux, arr[i] + unboundedKnapsack_rec( k-arr[i], arr, i ) );
}

void print_matrix( const int n, const int m, const int * matrix )
{
	for( int i = 0; i < n; i++ ) {
		std::cout << i << ": ";
		for( int j = 0; j < m; j++ )
			std::cout << matrix[i*m+j] << " ";
		std::cout << std::endl;
	}
}

// time O(k*n)
// space O(k*n)
int unboundedKnapsack_dp1(int k, vector <int> & arr) {
	int res = 0;
	int tab[k+1][arr.size()+1];

	// Init first row with zeros
	for( int j = 0; j < (int)arr.size()+1; j++ )
		tab[0][j] = 0;
	// Init first col with zeros
	for( int i = 0; i < k+1; i++ )
		tab[i][0] = 0;

	for( int j = 1; j < (int)arr.size()+1; j++ )
		for( int i = 1; i < k+1; i++ ) {
			int aux1 = tab[i][j-1];
			int aux2 = tab[i-1][j];
			int aux3 = 0;
			if( i-arr[j-1] >=0 ) {
				aux3 = tab[i-arr[j-1]][j] + arr[j-1];
				aux3 = (aux3 <= i) ? aux3 : 0;
			}
			tab[i][j] = max( aux1, max( aux2, aux3 ) );
			res = max( res, tab[i][j] );
			if( res == k )
				return res;
		}
	//print_matrix( k+1, arr.size()+1, (int*)tab );
	return res;
}

// time O(k*n)
// space O(k)
int unboundedKnapsack_dp2(int k, vector <int> & arr) {
	int res = 0;
	int tab[k+1];

	// Init with zeros
	for( int i = 0; i < k+1; i++ )
		tab[i] = 0;

	for( int j = 0; j < (int)arr.size(); j++ ) {
		for( int i = 1; i < k+1; i++ ) {
			int aux1 = tab[i];
			int aux2 = tab[i-1];
			int aux3 = 0;
			if( i-arr[j] >=0 ) {
				aux3 = tab[i-arr[j]] + arr[j];
				aux3 = (aux3 <= i) ? aux3 : 0;
			}
			tab[i] = max( aux1, max( aux2, aux3 ) );
			res = max( res, tab[i] );
		}
		if( res == k )
			return res;
	}
	//print_matrix( k+1, arr.size()+1, (int*)tab );
	return res;
}
int unboundedKnapsack(int k, vector <int> & arr) {
	// Complete this function
	//return unboundedKnapsack_rec( k, arr, arr.size()-1 );
	//return unboundedKnapsack_dp1( k, arr );
	return unboundedKnapsack_dp2( k, arr );
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
		int k;
		cin >> n >> k;
		vector<int> arr(n);
		for(int arr_i = 0; arr_i < n; arr_i++){
			cin >> arr[arr_i];
		}
		int result = unboundedKnapsack(k, arr);
		cout << result << endl;
	}
	return 0;
}

