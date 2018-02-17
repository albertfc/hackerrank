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

#define NDEBUG 1
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

#if 0
uint64_t array_pairs00( const vector<uint64_t> & v ) {

	size_t n = v.size();
	if( n < 3 )
		return 0;
	uint64_t res = v[0]*v[1] <= max( v[0], v[1] );

	list<decltype(v.begin())> l;
	l.push_back( v.begin() );
	for( auto it=next(v.begin()); it!=v.end(); ++it ) {
		uint64_t vi   = *it;
		uint64_t vim1 = *prev( it );
		if( vi < vim1 ) {
			l.push_back( it );
			auto jt=l.begin();
			auto jt_next = next( jt );
			while( jt_next != l.end() ) {
				auto current_max = *prev( *jt_next );
				auto threshold = current_max / vi;
				auto max_it = upper_bound( *jt, *jt_next, threshold );
				res += distance( *jt, max_it );
				jt = jt_next; jt_next = next( jt_next );
			}
		}
	}
	l.push_back( v.end() );
	auto jt=l.begin();
	auto jt_next = next( jt );
	while( jt_next != l.end() ) {
		auto current_max = *prev( *jt_next );
		auto threshold = current_max / v[v.size()-1];
		auto max_it = upper_bound( *jt, *jt_next, threshold );
		res += distance( *jt, max_it );
		jt = jt_next; jt_next = next( jt_next );
	}


	return res;
}

uint64_t array_pairs_O2( const vector<uint64_t> & v ) {
	uint64_t res = 0;

	for( int i=v.size()-1; i>0; --i ) {
		uint64_t curr_max = v[i];
		for( int j=i-1; j>=0; --j ) {
			curr_max = max( v[j], curr_max );
			res += (v[j] * v[i] > curr_max) ? 0 : 1;
#ifndef NDEBUG
			if( v[j] * v[i] <= curr_max )
				DBG( "%03d %03d\n", i, j );
#endif
		}
	}
	return res;
}
#endif

typedef pair<uint64_t, uint64_t> MyPair; // first: val, second: idx

bool valueLess( const MyPair & a, const MyPair & b ) {
	return a.first < b.first;
}

bool idxLess( const MyPair & a, const MyPair & b ) {
	return a.second < b.second;
}

uint64_t array_pairs( vector<MyPair> & v, const size_t begin_idx, const size_t end_idx , const size_t max_idx  ) {

	auto size = end_idx-begin_idx;
	if( size < 2 )
		return 0;
	if( size == 2 )
		return v[begin_idx].first*v[end_idx-1].first <= max( v[begin_idx].first, v[end_idx-1].first );

	uint64_t res = 0;

	// sort left and right
	auto begin =  v.begin()+begin_idx;
	auto max   =  v.begin()+max_idx;
	auto end   =  v.begin()+end_idx;
	sort( begin, max, valueLess );
	sort( max+1, end, valueLess );

	// compute res
	MyPair one_factor = make_pair( 1, 0 );
	MyPair max_factor = make_pair(  max->first/(end-1)->first, 0 );
	auto it_aux = upper_bound( begin, max, max_factor, valueLess );
	res += distance( begin, it_aux ) * distance( max+1, end )
	    +  distance( begin, upper_bound( begin, max, one_factor, valueLess ) )
	    +  distance( max+1, upper_bound( max+1, end, one_factor, valueLess ) );
	for( auto it=it_aux; it!=max; ++it ) {
		max_factor = make_pair( max->first/it->first, 0 );
		res += distance( max+1, upper_bound( max+1, end, max_factor, valueLess ) );
	}
	
	// call recursive left
	if( max_idx > 0 ) {
		size_t left_max_idx = v[max_idx-1].second;
		sort( begin, max, idxLess );
		res += array_pairs( v, begin_idx, max_idx, left_max_idx );
	}

	// call recursive right
	if( max_idx < end_idx-1 ) {
		size_t right_max_idx = v[end_idx-1].second;
		sort( max+1, end, idxLess );
		res += array_pairs( v, max_idx+1, end_idx, right_max_idx );
	}

	return res;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n ;
	vector<MyPair> v(n);
	MyPair vmax = make_pair(0,0);
	for( size_t i=0; i<n; ++i ) {
		uint64_t vi;
		cin >> vi;
		v[i].first  = vi;
		v[i].second = i;
		vmax = (vi > vmax.first ) ? v[i] : vmax;
	}
	cout << array_pairs( v, 0, v.size(), vmax.second ) << endl;
	return 0;
}

