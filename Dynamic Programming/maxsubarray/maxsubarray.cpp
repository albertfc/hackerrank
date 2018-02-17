/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

#include <stdio.h>
#ifndef SOURCE_PATH_SIZE
#define SOURCE_PATH_SIZE 0
#endif
#define __FILENAME__ (__FILE__ + SOURCE_PATH_SIZE)

#ifndef NDEBUG
#define DBG(msg, args...) \
    do { \
        fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
        fflush( stdout ); \
    } while( 0 );
#else
#define DBG(msg, args...)
#endif
#define MSG(msg, args...) fprintf( stdout, msg, ##args )
#define WRN(msg, args...) fprintf( stdout, "Warning: %s:%d " msg, __FILENAME__, __LINE__, ##args )
#define ERR(msg, args...) fprintf( stderr, "Error: %s:%d " msg, __FILENAME__, __LINE__, ##args )
#define GOTO_ERR(msg, args...) \
    do{ \
        ERR( msg, ##args ); \
        goto errorl; \
    } while( 0 )

std::vector<int> res(2);
vector <int> & maxSubarray2(vector <int> arr) {
	int64_t max_sa, max_ss, aux;

	// Deal with consecutives negative numbers at the beginning of the array
	max_sa = max_ss = aux = INT64_MIN;
	int i = 0;
	for( i = 0; i < (int)arr.size(); i++ ) {
		aux = std::max( aux , (int64_t)arr[i] );
		if( aux >= 0 )
			break;
	}
	max_sa = max_ss = aux;

	// 
	aux = 0;
	for( i=i+1; i < (int)arr.size(); i++ ) {
		int64_t e = arr[i];

		max_ss = (e > 0 ) ? max_ss + e : max_ss;

		if( max_sa+aux+e < max_sa ) {
			aux += e;
		} else {
			max_sa += e+aux;
			aux = 0;
		}
	}
	max_sa = std::max( max_sa, (int64_t)arr[arr.size()-1] );

	res[0] = max_sa;
	res[1] = max_ss;
	return res;
}

// https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm_(Algorithm_3:_Dynamic_Programming)
vector <int> & maxSubarray(vector <int> arr) {
	int64_t max_sa, max_ss;
	int64_t max_sa_i; // max subarray at position i

	max_sa = max_ss = max_sa_i = arr[0];
	for( auto it = arr.begin()+1; it != arr.end(); ++it ) {
		int64_t e = *it;
		max_sa_i = std::max( max_sa_i+e, e );
		max_sa   = std::max( max_sa_i, max_sa );
		max_ss   = std::max( std::max( max_ss+e, e ), max_ss );
	}

	res[0] = max_sa;
	res[1] = max_ss;
	return res;
}

int main() {
	int t;
	cin >> t;
	for(int a0 = 0; a0 < t; a0++){
		int n;
		cin >> n;
		vector<int> arr(n);
		for(int arr_i = 0; arr_i < n; arr_i++){
			cin >> arr[arr_i];
		}
		vector <int> result = maxSubarray(arr);
		for (ssize_t i = 0; i < (ssize_t)result.size(); i++) {
			cout << result[i] << (i != (ssize_t)result.size() - 1 ? " " : "");
		}
		cout << endl;
	}
	return 0;
}
