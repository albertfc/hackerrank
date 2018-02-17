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

// https://stackoverflow.com/questions/8300125/union-find-data-structure
class UnionFind {
	uint64_t num_sets;
	uint64_t * size;
	uint64_t * id;

	public:
	// Create an empty union find data structure with N isolated sets.
	UnionFind( const uint64_t n ): num_sets( n )   {
		id   = new uint64_t[n];
		size = new uint64_t[n];
		for(size_t i=0; i<n; i++) {
			id[i]   = i;
			size[i] = 1;
		}
	}
	~UnionFind(){
		delete [] id;
		delete [] size;
	}
	// Return the id of component corresponding to object p.
	uint64_t find( uint64_t p ) {
		uint64_t root = p;
		while( root != id[root] )
			root = id[root];
		while (p != root) {
			uint64_t newp = id[p];
			id[p] = root;
			p = newp;
		}
		return root;
	}
	// Replace sets containing x and y with their union.
	void merge( uint64_t x, uint64_t y ) {
		uint64_t i = find( x );
		uint64_t j = find( y );
		if( i == j )
			return;

		// make smaller root point to larger one
		if( size[i] < size[j] ) {
			id[i]    = j;
			size[j] += size[i];
		} else {
			id[j]    = i;
			size[i] += size[j];
		}
		num_sets--;
	}
	// Are objects x and y in the same set?
	bool connected( uint64_t x, uint64_t y ) {
		return find(x) == find(y);
	}
	// Return the number of disjoint sets.
	uint64_t count( void ) {
		return num_sets;
	}
	uint64_t set_size( uint64_t p ) {
		return size[ find( p ) ];
	}
};

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n, q;
	cin >> n >> q;
	UnionFind uf(2*n);
	for( size_t i=0; i<q; ++i ) {
		char qtype;
		uint64_t a, b;
		cin >> qtype;
		switch( qtype ) {
			case 'Q':
				cin >> a;
				cout << uf.set_size( a ) << endl;
				break;
			case 'M':
				cin >> a >> b;
				uf.merge( a, b );
		}
	}
	return 0;
}

