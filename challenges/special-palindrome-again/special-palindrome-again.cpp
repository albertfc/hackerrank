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

// Complete the substrCount function below.
long substrCount(int n, string s) {

	long res = 0;

	// Count single chars
	res += s.size();

	// Count all same chars
	long count = 0;
	for (size_t i = 1; i < s.size(); ++i) {
		if( s[i] == s[i-1]) {
			count++;
		} else if( count ){
			res += (count * (count+1)) / 2;
			count = 0;
		}
	}
	res += (count * (count+1)) / 2;

	if( s.size() < 3 )
		return res;

	// Count all same chars except middle
	auto left_it = s.rend();
	auto curr_it = s.begin();
	auto right_it = s.begin()+1;
	for (size_t i = 2; i < s.size(); ++i) {
		auto curr_left_it =  --left_it;
		auto curr_right_it = ++right_it;
		curr_it++;
		
		//cout << *curr_left_it << " " << *curr_right_it << endl;
		while( curr_left_it != s.rend() && curr_right_it != s.end()
		   && *curr_it != *left_it && *curr_left_it == *curr_right_it && *curr_left_it == *left_it ) {
			res++;
			curr_left_it++;
			curr_right_it++;
			//cout << *curr_left_it << " " << *curr_right_it << endl;
		}
		//cout << endl;
	}

	return res;
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

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    cout << result << "\n";

    return 0;
}
