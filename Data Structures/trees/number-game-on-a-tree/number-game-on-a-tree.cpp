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


namespace afc {
template <class T> 
struct allocator {
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	template <class U> struct rebind { typedef allocator<U> other; };
	allocator() throw() {}
	allocator(const allocator&) throw() {}

	template <class U> allocator(const allocator<U>&) throw(){}

	~allocator() throw() {}

	pointer address(reference x) const { return &x; }
	const_pointer address(const_reference x) const { return &x; }

	pointer allocate(size_type s, void const * = 0) {
		DBG( "allocate\n" );
		if (0 == s)
			return NULL;
		pointer temp = (pointer)malloc(s * sizeof(T)); 
		if (temp == NULL)
			throw std::bad_alloc();
		return temp;
	}

	void deallocate(pointer p, size_type) {
		free(p);
	}

	size_type max_size() const throw() { 
		return std::numeric_limits<size_t>::max() / sizeof(T); 
	}

	void construct(pointer p, const T& val) {
		DBG( "construct with p\n" );
		new((void *)p) T(val);
	}

	void construct( const T& val) {
		DBG( "construct\n" );
		new T(val);
	}

	void destroy(pointer p) {
		p->~T();
	}
};

template <typename T> struct list : public std::list<T,afc::allocator<uint32_t>> {};
}

template <typename T> struct matrix : public vector<vector<T>> {
	matrix( size_t n ): vector<vector<T>>( n ) {}
};

// insert e keeping list ordered O(log2 k)
template< typename T >
inline void add_sorted( afc::list<T> & l, T e ) {
	auto lb = lower_bound( l.begin(), l.end(), e );
	l.insert( lb, e );
}

// true wins
// false losses
template< typename T >
bool get_play_result( afc::list<T> & l ) {
	assert( l.size() > 0 && "weight list size cannot be zero!" );

	// Odd cardinality wins
	if( l.size() % 2 )
		return true;

	size_t prev_e = l.front(); // prev elem
	bool   prev_c = 1; // prev cardinality
	for( auto it=next( l.begin() ); it!=l.end(); ++it ) {
		if( prev_e == *it ) {
			prev_c = !prev_c;
		} else if( !prev_c ){ // Even cardinality
			prev_e = *it;
			prev_c = 1;
		} else {
			break;
		}
	}

	return prev_c;
}

uint32_t get_andy_wins( const vector<uint32_t[2]> & adj ) {

	size_t wins = 0;
	const size_t n = adj.size();
	matrix<afc::list<uint32_t>> res( n);
	// compute game result for each pair of nodes and accumulate
	for( size_t i=0; i<n; ++i ) {
		res[i].resize( i+1 );
		res[i][0].resize( i+1 );
		for( size_t j=0; j<i; ++j ) {
			DBG( "i:%zu adj[i]: %zd j:%zu\n", i, adj[i][0], j );
			size_t k = max( (size_t)adj[i][0], j );
			size_t l = min( (size_t)adj[i][0], j );
			res[i][j] = res[k][l];
			add_sorted( res[i][j], adj[i][1] );
			wins += get_play_result( res[i][j] );
		}
	}
	return wins;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t g;
	cin >> g;
	for( size_t i=0; i<g; ++i ) {
		size_t n;
		cin >> n;
		vector<uint32_t[2]> m(n);
		for( size_t j=0; j<n-1; ++j ) {
			uint32_t x,y,w;
			cin >> x >> y >> w;
			if( x > y ) {
				m[x-1][0] = y-1;
				m[x-1][1] = w;
			} else {
				m[y-1][0] = x-1;
				m[y-1][1] = w;
			}
		}
		cout << get_andy_wins( m ) << endl;
	}
	return 0;
}

