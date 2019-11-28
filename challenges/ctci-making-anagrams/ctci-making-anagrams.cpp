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

// Complete the makeAnagram function below.
int makeAnagram(string a, string b) {
	int res = 0;

	// init tmp string with enough space!
	string tmp1(a.size(),' '), tmp2(b.size(),' ');

	sort( a.begin(), a.end() );
	sort( b.begin(), b.end() );

	auto end1 = set_difference( a.begin(), a.end(), b.begin(), b.end(), tmp1.begin() );
	res += distance( tmp1.begin(), end1 );
	auto end2 = set_difference( b.begin(), b.end(), a.begin(), a.end(), tmp2.begin() );
	res += distance( tmp2.begin(), end2 );

	return res;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    cout << res << "\n";

    return 0;
}

