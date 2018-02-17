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

typedef vector<list<int>> AdjList ;

int get_connected_vertices( int orig, int v, AdjList & adj, set<int> & visit ) {
	int res = 0;
	auto edges = adj[v];
	for( auto next_v: edges ) {
		if( next_v == orig ) // previous vertex
			continue;
		if( visit.find( next_v ) == visit.end() ) // cycle
			continue;
		visit.erase( next_v );
		res += 1 + get_connected_vertices( v, next_v, adj, visit );
	}
	return res;
}

void max_min( AdjList & adj, set<int> & visit ) {
	int _min = numeric_limits<int>::max();
	int _max = 0;
	while( !visit.empty() ) {
		int v = *(visit.begin());
		visit.erase( v );
		int res = 1 + get_connected_vertices( -1, v, adj, visit );
		_max = max( res, _max );
		_min = min( res, _min );
	}
	cout << _min << " " << _max << endl;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	AdjList adj(2*n);
	set<int> visit;
	for( size_t i=0; i<n; ++i ) {
		int x, y;
		cin >> x >> y;
		adj[x-1].push_back( y-1 );
		adj[y-1].push_back( x-1 );
		visit.insert( x-1 );
		visit.insert( y-1 );
	}
#ifndef NDEBUG
	for( size_t v=0; v<n*2; ++v )
		for( auto e : adj[v] )
			DBG( "V %u --> %d\n", v, e );
#endif
	max_min( adj, visit );
	return 0;
}

