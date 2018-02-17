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

typedef vector<list<pair<int,bool>>> AdjList ;


pair<uint64_t,uint64_t> kundu( int parent, int v, bool color, AdjList & adj, uint64_t & current_size, uint64_t parent_pivot_triplets, uint64_t & total_triplets ) {

	DBG( "size %zu\n", current_size );
	if( current_size > 0 ) {
		if( current_size  == 1 ) {
			total_triplets = color;
		} else if( current_size == 2 ) {
			total_triplets = ( color && total_triplets ) ? 1 : 0;
		} else {
			//uint64_t current_pairs = (current_size * (current_size -1)) / 2;
			//total_triplets += (color) ? parent_pivot_triplets : 0;
		}
	}

	uint64_t child_pivot_triplets = 0;
	uint64_t depth = 0;
	uint64_t pivot_triplets = (color) ? current_size : parent_pivot_triplets;
	uint64_t orig_size = current_size;
	current_size += 1;
	auto edges = adj[v];
	for( auto next_v: edges ) {
		if( next_v.first == parent ) // previous vertex
			continue;
		auto p = kundu( v, next_v.first, next_v.second, adj, current_size, pivot_triplets, total_triplets );
		depth += p.first;
		child_pivot_triplets += (next_v.second) ? depth : p.second;
		total_triplets += (color) ? child_pivot_triplets * orig_size : 0;
		pivot_triplets += child_pivot_triplets;
	}

	return make_pair( 1 + depth, child_pivot_triplets );
}

void kundu_wrapper( AdjList & adj ) {

	if( adj.size() < 3 )
		cout << "0" << endl;

	uint64_t size = 0;
	uint64_t red;
	kundu( -1, 0, false, adj, size, 0, red );
	cout << red % (uint64_t)(10e9+7) << endl;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	AdjList adj(n);
	//set<int> visit;
	for( size_t i=0; i<n-1; ++i ) {
		int x, y;
		char c;
		cin >> x >> y >> c;
		adj[x-1].push_back( make_pair( y-1, c =='r' ) );
		adj[y-1].push_back( make_pair( x-1, c =='r' ) );
		//visit.insert( i );
	}
	//visit.insert( n-1 );
#ifndef NDEBUG
	for( size_t v=0; v<n-1; ++v )
		for( auto e : adj[v] )
			DBG( "V %zu --> %d : %d\n", v, e.first, e.second );
#endif
	kundu_wrapper( adj );
	return 0;
}

