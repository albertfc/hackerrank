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

// Complete the isValid function below.
string isValid(string s) {
	// build freq histogram
	array<int, 26> freqs = {{0}};
	for (const auto& c: s) {
		freqs[c-'a'] += 1;
	}
	// build map: #freq -> #times_appears
	map<int,int> freqs_map;
	for (const auto& f : freqs) {
		if (!f) {
			continue; // discard freqs == 0
		}
		auto elem = freqs_map.insert({f,0}).first;
		elem->second++; // update #times_appears counter
		if (freqs_map.size() > 2) {
			return "NO"; // too much freqs
		}
	}
	// check:
	//   - there is only one freq (except 0)
	//   - there are only two cosecutive freqs and the largest freq appears only once
	//   - there are only two freqs and one is (1,1)
	//   - otherwise is not valid
	if (freqs_map.size() == 1) {
		return "YES";
	} else { // (freqs_map.size() == 2)
		const int first_freq        = freqs_map.begin() ->first;
		const int first_freq_count  = freqs_map.begin() ->second;
		const int second_freq       = freqs_map.rbegin()->first;
		const int second_freq_count = freqs_map.rbegin()->second;
		if (second_freq-first_freq==1 && second_freq_count==1) {
			return "YES";
		} else if (first_freq==1 && first_freq_count==1) {
			return "YES";
		} else {
			return "NO";
		}
	}
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string s;
    getline(cin, s);

    string result = isValid(s);

    cout << result << "\n";

    return 0;
}
