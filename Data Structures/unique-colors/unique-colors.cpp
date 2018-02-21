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

struct Vertex {
	list<Vertex*> adj; // adjacency list
	uint32_t id;
	uint32_t order; // visited order
	uint32_t color;
	uint32_t total_sum;
	uint32_t size;  // number of descendents
	map<uint32_t,uint32_t> sum; // sum of each adjacent node indexed by id
	Vertex * cv; // closest vertex with same color in the path to root
};

void first_step( Vertex * v, const Vertex * prev_v, uint32_t & curr_order, vector<set<uint32_t>> & c, vector<Vertex*> & o, vector<Vertex*> & l  ) {

	v->order  = curr_order++;
	o[v->order] = v;
	v->cv = l[v->color];

	for( Vertex * next_v : v->adj ) {
		if( next_v == prev_v ) // parent 
			continue;

		l[v->color] = v;
		first_step( next_v, v, curr_order, c, o,l );
		v->size += next_v->size;

		// add child sum
		v->sum[next_v->id]  = next_v->total_sum;
		// add child subtree size
		v->sum[next_v->id] += next_v->size;
		// remove duplicate colors
		uint32_t next_o = next_v->order;
		set<uint32_t>::iterator it;
		while( (it = c[v->color].lower_bound( next_o )) != c[v->color].end() ) {
			v->sum[next_v->id] -= o[*it]->size;
			next_o = o[*it]->order + o[*it]->size;
		}
		// update total sum
		v->total_sum += v->sum[next_v->id];
	}

	v->size++; // increase size
	v->total_sum++; // self connection
	c[v->color].insert( v->order ); // index v by color
	l[v->color] = v->cv; // Restore last vertex
}


void second_step( Vertex * v0, const uint32_t n, vector<set<uint32_t>> & c, vector<Vertex*> & o ) {

	queue<Vertex*> q;
	q.push( v0 );

	while( !q.empty() ) {
		Vertex* v = q.front();
		q.pop();
		for( Vertex * next_v: v->adj ) {
			if( next_v->order > v->order ) { // children
				q.push( next_v );
			} else { // parent
				// add parent sum
				v->sum[next_v->id]  = next_v->total_sum;
				// remove v contribution to parent sum
				v->sum[next_v->id] -= next_v->sum[v->id];
				// add parent subtree size
				v->sum[next_v->id] += n - v->size;
				//// remove duplicate colors
				// Find lowest ancestor with same color
				uint32_t next_o = 0;
				uint32_t last_o = n;
				if( v->cv ) { // found
					for( Vertex * next_oi: v->cv->adj ) { // search edge connecting to v
						if(( next_oi->order > v->cv->order ) // skip parent
						&& ( next_oi->order <= v->order ) // v->order must be in the range of next_oi->order and next_oi->order + next_oi->size
						&& ( v->order < next_oi->order + next_oi->size) ) {
							v->sum[next_v->id] -= n - next_oi->size;
							next_o = next_oi->order;
							last_o = next_oi->order + next_oi->size;
							break;
						}
					}
				}
				// search for duplicate colors in lowest ancestor subtree
				set<uint32_t>::iterator it;
				while( (it = c[v->color].lower_bound( next_o )) != c[v->color].end()
				    && o[*it]->order < last_o ) {
					const Vertex * oi = o[*it];
					next_o = oi->order + oi->size;
					if( oi == v ) // self
						continue;
					v->sum[next_v->id] -= oi->size;
				}
				// update total sum
				v->total_sum += v->sum[next_v->id];
			}
		}
	}
}


void unique_colors( vector<Vertex> & v, size_t color_size ) {

	// vertices visited so far indixed by its order;
	vector<Vertex*> o( v.size() );
	// vertices order visited so far indexed by its color;
	vector<set<uint32_t>> c( color_size );
	// last vertex in the path to root by color
	vector<Vertex*> l( color_size, nullptr );
	uint32_t order = 0;
	first_step( &v[0], nullptr, order, c, o, l );
	second_step( &v[0], v.size(), c, o );
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	vector<Vertex> v(n);
	uint32_t color_size = 0;
	for( size_t i=0; i<n; ++i ) {
		uint32_t color;
		cin >> color;
		v[i].color = color - 1;
		color_size = max( color_size, color );
		v[i].id = i;
		v[i].order = -1;
		v[i].total_sum = 0;
		v[i].size = 0;
	}
	for( size_t i=0; i<n-1; ++i ) {
		int x, y;
		cin >> x >> y;
		v[x-1].adj.push_back( &v[y-1] );
		v[y-1].adj.push_back( &v[x-1] );
	}

	unique_colors( v, color_size );
	for( size_t i=0; i<n; ++i )
		cout << v[i].total_sum << endl;
	return 0;
}

