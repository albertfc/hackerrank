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

template< typename X, typename Y >
struct pair_cmp {
	bool operator()( const pair<X,Y> &rhs, const pair<X,Y> &lhs ) const {
		return rhs.data0 < lhs.data0;
	}
};

template< typename T >
struct MyPair {
	T data0, data1;
	MyPair( T x, T y ) : data0(x), data1(y) {}
	inline bool operator<( const MyPair<T> & rhs) {
		return data0 < rhs.data0;
	}
	friend inline bool operator<( const MyPair<T> & lhs, const MyPair<T> & rhs) {
		return lhs.data0 < rhs.data0;
	}
	inline bool operator==( const MyPair<T> & rhs) {
		return data0 == rhs.data0;
	}
	inline bool operator!=( const MyPair<T> & rhs) {
		return !(*this == rhs);
	}
};
typedef MyPair<uint32_t> UintPair;

uint32_t largest_rectangle( vector<uint32_t> & h ) {
	uint32_t res = 0;
	stack<UintPair> s; // 0->heigh 1->i

	s.push( UintPair( h[0], 0 ) );
	for( uint32_t i=1; i<h.size(); ++i ) {
		if( h[i] ==  s.top().data0 )
			continue;
		if( h[i] > s.top().data0 ) { // going up
			s.push( UintPair( h[i], i ) );
		} else { // going down
			uint32_t j;
			while( !s.empty() && s.top().data0 > h[i] ) {
				j = s.top().data1;
				res = max( res, s.top().data0 * (i - j) );
				s.pop();
			}
			j = ( s.empty() ) ? 0 : j;
			s.push( UintPair( h[i], j ) );
		}
	}
	while( !s.empty() ) {
		res = max( res, s.top().data0 * ((uint32_t)h.size() - s.top().data1) );
		s.pop();
	}
	return res;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	vector<uint32_t> h(n);
	for( size_t i=0; i<n; ++i ) {
		cin >> h[i];
	}
	cout << largest_rectangle( h ) << endl;
}

