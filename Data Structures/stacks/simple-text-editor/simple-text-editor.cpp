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

class Operation {
	public:
	virtual void apply( string & s) = 0;
	virtual ~Operation() {};
};
class OPdel: public Operation {
	private:
		size_t _k;
	public:
	OPdel( size_t k ): _k( k ) {};
	virtual void apply( string & s ) {
		s.erase( s.size()-_k, _k );
	}
};
class OPappend: public Operation {
	private:
		string _s;
	public:
	OPappend( string & s ): _s( s ) {};
	virtual void apply( string & s ) {
		s.append( _s );
	}
};

class Editor {
	private:
		string _data;
		stack<Operation*> _ops;

	public:
	void append( string & s ) {
		_ops.push( new OPdel( s.size() ) );
		_data.append( s );
		DBG( "%s: %s\n", __FUNCTION__, _data.c_str() );
	}

	void del( size_t k ) {
		string aux = _data.substr( _data.size()-k, k );
		_ops.push( new OPappend( aux ) );
		_data.erase( _data.size()-k, k );
		DBG( "%s: %s\n", __FUNCTION__, _data.c_str() );
	}

	void print( size_t k ) {
		cout << _data[k-1] << endl;
	}

	void undo( void ) {
		if( _ops.empty() )
			return;
		Operation * op = _ops.top();
		op->apply( _data );
		delete op;
		_ops.pop();
		DBG( "%s: %s\n", __FUNCTION__, _data.c_str() );
	}

};

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	string a;
	size_t k;
	size_t q;
	cin >> q;
	Editor ed;
	for( size_t i=0; i<q; i++ ) {
		int op;
		cin >> op;
		switch( op ) {
			case 1:
				cin >> a;
				ed.append( a );
				break;
			case 2:
				cin >> k;
				ed.del( k );
				break;
			case 3:
				cin >> k;
				ed.print( k );
				break;
			case 4:
				ed.undo();
				break;
			default:
				break;
		}
	}

	return 0;
}

