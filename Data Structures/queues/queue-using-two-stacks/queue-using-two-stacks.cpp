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

template <typename T>
class TwoStacks {
	private:
		stack<T> _push, _pop;
		T _push_front;
	public:
		void push( T x ) {
			if( _push.empty() )
				_push_front = x;
			_push.push( x );
		}
		void pop( void ) {
			if( _pop.empty() )
				while( !_push.empty() ) {
					_pop.push( _push.top() );
					_push.pop();
				}
			_pop.pop();
		}
		T front( void ) {
			return _pop.empty() ? _push_front : _pop.top();
		}
};

// dup2 & open
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	TwoStacks<int64_t> queue;
	size_t q;
	cin >> q;
	for( size_t i=0; i<q; ++i ) {
		size_t t;
		cin >> t;
		switch( t ) {
			case 1:
				int64_t x;
				cin >> x;
				queue.push( x );
				break;
			case 2:
				queue.pop();
				break;
			case 3:
				cout << queue.front() << endl;
				break;
			default:
				break;
		}
	}
	return 0;
}

