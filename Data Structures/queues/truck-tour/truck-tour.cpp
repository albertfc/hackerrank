/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

int64_t truck_tour( vector<int64_t> & p, vector<int64_t> & d )
{
	size_t res = 0;

	int64_t total = 0;
	int64_t debt  = 0;
	for( size_t i=res; i<p.size(); i++ ) {
		total += p[i] - d[i];
		if( total<0 ) {
			debt += total;
			total = 0;
			res   = i+1;
		}
	}
	if( total+debt < 0 )
		return -1;
	else
		return res;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	vector<int64_t> p(n);
	vector<int64_t> d(n);
	for(size_t arr_i = 0; arr_i < n; arr_i++){
		cin >> p[arr_i];
		cin >> d[arr_i];
	}
	size_t result = truck_tour(p, d);
	cout << result << endl;
	return 0;
}

