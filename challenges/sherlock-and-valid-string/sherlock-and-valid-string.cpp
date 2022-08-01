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

	if( s.size() < 3 )
		return "YES";

	array<int,26> freq{{0}};

	for (char c : s) {
		freq[c-'a'] += 1;
	}

	sort( freq.begin(), freq.end(), std::greater<int>() );

	if( freq[1] == 0 ) // string composed by 1 char
		return "YES";

	size_t i = 2;
	while( i < s.size() && freq[i] == freq[1] ) {i++;}
	if( freq[0]-freq[1] == 1 ) {
		if( i == s.size() || freq[i] == 0 )
			return "YES";
	} else if( freq[0] == freq[1] ) {
		if( i == s.size() || freq[i] == 0 || (i == s.size()-1 && freq[i]==1) || (freq[i]==1 && freq[i+1]==0 ) )
			return "YES";
	}
	return "NO";
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
