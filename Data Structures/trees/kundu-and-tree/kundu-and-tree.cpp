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


//https://math.stackexchange.com/questions/838792/counting-triplets-with-red-edges-in-each-pair?newreg=60eee35f0b3844de852bda39f6dfec88
int get_maximal_allblack_subtree_order( int v, AdjList & adj, set<int> & visit ) {
	int res = 0;
	auto edges = adj[v];
	for( auto next_v: edges ) {
		if( next_v.second ) // red edge
			continue;
		if( visit.find( next_v.first ) == visit.end() ) // cycle
			continue;
		visit.erase( next_v.first );
		res += 1 + get_maximal_allblack_subtree_order( next_v.first, adj, visit );
	}
	return res;

}

void kundu( AdjList & adj, set<int> & visit ) {

	if( adj.size() < 3 )
		cout << "0" << endl;

	uint64_t n = visit.size();
	uint64_t res = 0;
	while( !visit.empty() ) {
		int v = *(visit.begin());
		visit.erase( v );
		uint64_t n_i = get_maximal_allblack_subtree_order( v, adj, visit );
		n_i = ( n_i ) ? n_i + 1 : 0;
		res += n_i * (n_i-1) * (3*n - 2*n_i - 2);
	}
	res = (n*(n-1)*(n-2) - res) / 6;
	cout << res % (uint64_t)(1e9+7) << endl;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	AdjList adj(n);
	set<int> visit;
	for( size_t i=0; i<n-1; ++i ) {
		int x, y;
		char c;
		cin >> x >> y >> c;
		adj[x-1].push_back( make_pair( y-1, c =='r' ) );
		adj[y-1].push_back( make_pair( x-1, c =='r' ) );
		visit.insert( i );
	}
	visit.insert( n-1 );
	kundu( adj, visit );
	return 0;
}

