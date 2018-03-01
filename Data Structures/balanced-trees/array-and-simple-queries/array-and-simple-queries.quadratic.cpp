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

struct Node {
	Node( const uint32_t _min, const uint32_t _max ) : min( _min ), max( _max ) {
		closed = min == max;
	}
	uint32_t min, max;
	bool closed;
};

list<Node> l;

void process( uint32_t th1, uint32_t add1_left, uint32_t add1_right, uint32_t th2, uint32_t add2_left, uint32_t add2_right ) {

	for( auto it=l.begin(); it!=l.end(); ++it ) {
		auto & n = *it;
		if( n.closed ) {
			if( n.max < th1 ) {
				n.max += add1_left;
			} else {
				n.max += add1_right;
				if( n.max < th2 ) {
					n.max += add2_left;
				} else {
					n.max += add2_right;
				}
			}
		} else {
			if( n.min < th1 && n.max < th1 ) {
				n.min += add1_left;
				n.max += add1_left;
			} else if ( n.min < th1 && n.max >= th1 ) {
				l.emplace( next( it ), th1, n.max );
				n.min += add1_left;
				n.max  = th1-1+add1_left;
				n.closed = n.min == n.max;
			} else {
				n.min += add1_right;
				n.max += add1_right;

				if( n.min < th2 && n.max < th2 ) {
					n.min += add2_left;
					n.max += add2_left;
				} else if ( n.min < th2 && n.max >= th2 ) {
					l.emplace( next( it ), th2, n.max );
					n.min += add2_left;
					n.max  = th2-1+add2_left;
					n.closed = n.min == n.max;
				} else {
					n.min += add2_right;
					n.max += add2_right;
				}
			}

		}
	}

}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n, m;
	cin >> n >> m;
	vector<uint32_t> a(n+1);
	for( size_t i=1; i<n+1; ++i ) {
		cin >> a[i];
	}
	l.emplace_back( 1, n );
	for( size_t i=0; i<m; ++i ) {
		uint32_t q, j, k;
		cin >> q >> j >> k;

		switch( q ) {
			case 1:
				process( j, k-j+1, 0, k+1, -(j-1), 0 );
				break;
			case 2:
				process( j, 0, 0, k+1, n-k, -(k-j+1) );
				break;
		}
	}

	vector<int64_t> res(n+1);
	size_t x = 1;
	for( auto & n: l ) {
		if( n.closed )
			res[n.max] = a[x++];
		else
			for( size_t y=n.min; y<=n.max; y++ )
				res[y] = a[x++];
	}
	cout << abs( res[n]-res[1] ) << endl;
	for( size_t z=1; z<n+1; ++z )
		cout << res[z] << " ";
}

