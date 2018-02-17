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
struct Node {
	T value;
	Node * left;
	Node * right;
};

void swap_rec( Node<int> * n, const unsigned k, const unsigned depth ) {
	if( !n )
		return;

	if( depth % k == 0 ) { // swap children
		Node<int> * aux = n->left;
		n->left  = n->right;
		n->right = aux;
	}

	swap_rec( n->left,  k, depth+1 );
	swap_rec( n->right, k, depth+1 );
}

void inorder( Node<int> * n ) {
	if( !n )
		return;

	inorder( n->left );
	cout << n->value << " ";
	inorder( n->right );
}

void swap( Node<int> * root, unsigned k ) {
	swap_rec( root, k, 1 );

	inorder( root );
	cout << endl;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	vector<Node<int>> v(n);
	for( size_t i=0; i<n; ++i ) {
		int l, r;
		cin >> l >> r;
		v[i].value = i+1;
		v[i].left  = (l != -1) ? &(v[l-1]) : nullptr;
		v[i].right = (r != -1) ? &(v[r-1]) : nullptr;
	}
	size_t t;
	cin >> t;
	for( size_t i=0; i<t; ++i ) {
		size_t k;
		cin >> k;
		swap( &(v[0]), k );
	}

	return 0;
}

