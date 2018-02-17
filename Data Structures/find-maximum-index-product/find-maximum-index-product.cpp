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

// O(n)
uint32_t max_ip( const vector<uint32_t> & a ) {
	if( a.size() < 3 )
		return 0;

	bool up, down;
	size_t di, ui; // i where we first go down/up
	di = ui = 0;
	down = up = false;
	// find rightmost local min
	size_t i=a.size()-2;
	while( i>0 && (!down || !up) ) {
		bool right = a[i] < a[i+1];
		bool left  = a[i] < a[i-1];
		di = (right) ? i+1 : di;
		ui = (left) ? i-1 : ui;
		down |= right;
		up   |= down && left;
		--i;
	}
	DBG( "left = %zu -- right == %zu\n", ui+1, di+1 );
	return (down && up) ? (di+1)*(ui+1) : 0;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	vector<uint32_t> a(n);
	for( size_t i=0; i<n; ++i ) {
		cin >> a[i];
	}
	cout << max_ip( a ) << endl;
	return 0;
}

