/* Copyright (C) 2019 Albert Farres - All Rights Reserved
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
#define __FILENAME__ (&__FILE__[SOURCE_PATH_SIZE])

#ifndef NDEBUG
#define DBG(msg, args...) \
	do { \
		fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
		fflush( stdout ); \
	} while( 0 );
#else
#define DBG(msg, args...)
#endif

// Complete the candies function below.
long candies_greedy(int n, vector<int> arr) {

	vector<int> res( n, 1 );
	vector<array<int,2>> sorted_array(n);

    // sort using a custom function object
    struct {
        bool operator()(array<int,2> & a, array<int,2> & b) const
        {   
            return a[0] < b[0];
        }   
    } valueLess;
	for (size_t i = 0; i < arr.size(); ++i) {
		sorted_array[i][0] = arr[i];
		sorted_array[i][1] = i;
	}
	sort( sorted_array.begin(), sorted_array.end(), valueLess );

	for (const auto & e : sorted_array) {
		if( (e[1] == 0 || arr[e[1]-1] >= e[0])
		 && (e[1] == n-1 || arr[e[1]+1] >= e[0]) )
			continue;
		res[e[1]] = 1 + max( e[1] ==   0 ? 1 : res[e[1]-1],
		                     e[1] == n-1 ? 1 : res[e[1]+1] );
	}

	return std::accumulate( res.begin(), res.end(), 0 );
}

long candies(int n, vector<int> arr) {

	vector<long> res( n, 1 );

	for (size_t i = 1; i < arr.size(); ++i) {
		if( arr[i] > arr[i-1] )
			res[i] = res[i-1] + 1;
	}
	long sum = res[n-1];
	for (long i = arr.size()-2; i >= 0; --i) {
		if( arr[i] > arr[i+1] )
			res[i] = max( res[i+1]+1, res[i] );
		sum += res[i];
	}

	return sum;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    cout << result << "\n";

    return 0;
}
