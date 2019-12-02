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

#if 0
// Complete the abbreviation function below.
string abbreviation(string a, string b) {
	size_t i = 0;
	size_t j = 0;
	while( i<a.size() && j<b.size() ) {
		if( a[i] == b[j] || toupper( a[i] ) == b[j] ) {
			i++; j++;
		} else if( islower( a[i]) ) {
			i++;
		} else {
			return "NO";
		}
	}
	if( j<b.size() ) {
		return "NO";
	}
	while( i<a.size() ) {
		if( !islower( a[i]) ) {
			return "NO";
		}
		i++;
	}
	return "YES";
}
#endif

bool abbr_rec(const string & a, const string & b, int i, int j) {
	if( i < 0  && j < 0 )
		return true;
	else if( i<0 )
		return false;
	else if( j<0 )
		return islower( a[i] ) && abbr_rec( a,b,i-1,j );

	if( a[i] == b[j] )
		return abbr_rec( a,b,i-1,j-1 );

	if( islower( a[i] ) )
		return abbr_rec( a,b,i-1,j )
		   ||( toupper( a[i] ) == b[j] && abbr_rec( a,b,i-1,j-1 ) );

	return false;
}

array<array<bool,1001>,1001> dp;
bool abbr_dp( const string & a, const string & b ) {
	dp[0][0] = true;
	for (size_t i = 1; i <= a.size(); ++i) {
		dp[i][0] = dp[i-1][0] && islower( a[i-1] );
	}
	for (size_t j = 1; j <= b.size(); ++j) {
		dp[0][j] = false;
	}

	for (size_t i = 1; i <= a.size(); ++i) {
		for (size_t j = 1; j <= b.size(); ++j) {
			dp[i][j] = 
				( a[i-1] == b[j-1] ) ? dp[i-1][j-1] :
				( islower( a[i-1]) ) ? dp[i-1][  j] || ( dp[i-1][j-1] && toupper( a[i-1] ) == b[j-1] ) :
				false;
		}
	}
	return dp[a.size()][b.size()];
}

string abbreviation(string a, string b) {
	//if( abbr_rec( a,b,a.size()-1,b.size()-1) )
	if( abbr_dp( a,b ) )
		return "YES";
	else
		return "NO";
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        cout << result << "\n";
    }

    return 0;
}
