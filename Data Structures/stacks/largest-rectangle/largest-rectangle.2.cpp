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

struct Building {
	int _height;
	int _idx;

	Building(int height, int idx): _height(height), _idx(idx) {}

	long area( const Building& b) const {
		const long height = min(_height, b._height);
		const long base   = abs(_idx - b._idx)+1;
		return base*height;
	}

	friend bool operator>(const Building& l, const Building& r) {
		return l._height > r._height;
	}
};

long largest_rectangle( vector<int> & h ) {
	deque<Building> s;

	long res = h[0];
	s.emplace_back(h[0],0);

	// stack height and idx of previous short buildings
	for (int i = 1; i < h.size(); ++i) {
		const Building curr_b = Building(h[i],i);

		// check largest retangle for stacked values
		for (const auto& b : s) {
			res = max(res, max((long)h[i],curr_b.area(b)));
		}

		// update stack
		int back_idx = -1;
		while(!s.empty() && s.back()>curr_b) {
			back_idx = s.back()._idx;
			s.pop_back();
		}
		if( back_idx > -1 ) {
			s.emplace_back(h[i],back_idx);
		} else {
			s.push_back(curr_b);
		}
	}

	return res;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	vector<int> h(n);
	for( size_t i=0; i<n; ++i ) {
		cin >> h[i];
	}
	cout << largest_rectangle( h ) << endl;
}

