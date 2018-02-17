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

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int64_t res = 0;
	size_t n, m;
	cin >> n >> m;
	vector<int64_t> v(n+1,0);
	for( size_t l=0; l<m; l++ ) {
		size_t i,j;
		int64_t k;
		cin >> i >> j >> k;
		// Store the difference between current prev and next elem
		v[i] += k;
		if( j+1 <= n )
			v[j+1] -= k;
	}
	int64_t aux = 0;
	for( size_t l=1; l<=n; l++ ) {
		aux += v[l];
		res = max( aux, res );
	}
	cout << res << endl;

	return 0;
}

