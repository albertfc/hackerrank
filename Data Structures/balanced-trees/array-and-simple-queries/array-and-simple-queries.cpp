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

struct Node {
	size_t i; // original idx in A
	Node *l, *r, *p; // Children and parent
	uint64_t sz; // subtree size
	unsigned priority;
};

// https://en.wikipedia.org/wiki/Treap
// http://opendatastructures.org/ods-python/7_2_Treap_Randomized_Binary.html
// https://threads-iiith.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-2
//
// The key node is the current idx in A.
// We can compute it implicitly for a node t as:
//        sz(t->l) + sz(p->l) for all parents of t such that t occurs in the right subtree of p.


inline void update_size( Node * p ) {
	p->sz  = 1 + ((p->l) ? p->l->sz : 0)
	           + ((p->r) ? p->r->sz : 0);
}

void right_rotation( Node * root ) {
	Node * pivot = root->l;

	root->l = pivot->r;
	if( root->l )
		root->l->p = root;
	pivot->p = root->p;
	if( pivot->p && pivot->p->l == root )
		pivot->p->l = pivot;
	else if( pivot->p && pivot->p->r == root )
		pivot->p->r = pivot;
	pivot->r = root;
	root->p  = pivot;

	update_size( root );
	update_size( pivot );
}

void left_rotation( Node * root ) {
	Node * pivot = root->r;

	root->r = pivot->l;
	if( root->r )
		root->r->p = root;
	pivot->p = root->p;
	if( pivot->p && pivot->p->l == root )
		pivot->p->l = pivot;
	else if( pivot->p && pivot->p->r == root )
		pivot->p->r = pivot;
	pivot->l = root;
	root->p  = pivot;

	update_size( root );
	update_size( pivot );
}

void add( Node *& root, Node * n, size_t key ) {
	n->sz = 1;
	n->l = nullptr;
	n->r = nullptr;
	n->p = nullptr;

	// Binary search for n in the tree
	Node  * parent = nullptr;
	Node ** p_child = nullptr;
	Node  * curr = root;
	size_t parent_key = 0;
	while( curr ) {
		// Compute implicit key
		size_t curr_key = 1 + parent_key + (( curr->l ) ? curr->l->sz : 0);
		parent = curr;
		if( key < curr_key ) { // left subtree
			p_child = &(curr->l);
			curr = curr->l;
		} else { // right subtree
			p_child = &(curr->r);
			curr = curr->r;
			parent_key = curr_key;
		}
	}

	// n is the new root
	if( !p_child ) {
		root = n;
		return;
	}

	// Insert n as his parent child
	*p_child = n;
	n->p = parent;
	update_size( parent );

	// Perform a tree rotations that reverses the parent-child relation until n fullfills its priority
	while( n->p && n->p->priority > n->priority ) {
		if( n->p->l == n ) // right rotation
			right_rotation( n->p );
		else
			left_rotation( n->p );
	}

	// update sizes and root pointer
	root = n;
	Node * next = n->p;
	while( next ) {
		root = next;
		update_size( next );
		next = next->p;
	}
}

Node * del( Node * n ) {
	// Perform tree rotations that move n downwards until it becomes a leaf
	while( n->l || n->r ) {
		if( !n->r )
			right_rotation( n );
		else if( !n->l )
			left_rotation( n );
		else if( n->l->priority < n->r->priority )
			right_rotation( n );
		else
			left_rotation( n );
	}

	// Disconect n
	if( n->p ) {
		if( n->p->l == n )
			n->p->l = nullptr;
		else
			n->p->r = nullptr;
	}

	// update sizes until root and return pointer
	Node * root = n;
	while( root->p ) {
		update_size( root );
		root = root->p;
	}
	return root;
}

void split( Node * root, Node *& l, Node *& r, size_t key ) {
	Node n = {}; // init everything to 0 (also priority)
	add( root, &n, key );
	assert( &n == root && "n must be root" );
	l = root->l;
	r = root->r;
	if( l )
		l->p = nullptr;
	if( r )
		r->p = nullptr;
}

Node * merge( Node * l, Node * r ) {
	Node n = {};
	n.priority = UINT_MAX;
	n.l = l;
	n.r = r;
	if( l )
		l->p = &n;
	if( r )
		r->p = &n;
	update_size( &n );

	return del( &n );
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n, m;
	cin >> n >> m;
#ifndef NDEBUG
	srand( 1 );
#else
	srand( time( nullptr ) ); // // use current time as seed for random generator
#endif
	vector<uint32_t> a(n);
	vector<Node> nodes(n);
	Node * root = nullptr;
	for( size_t i=0; i<n; ++i ) {
		cin >> a[i];
		nodes[i].i = i+1;
#ifndef NDEBUG
		nodes[i].priority = rand() % 100;
#else
		nodes[i].priority = rand();
#endif
		add( root, &nodes[i], i+1 );
	}

	for( size_t i=0; i<m; ++i ) {
		uint32_t q, j, k;
		cin >> q >> j >> k;

		Node *jl, *jr, *kl, *kr;
		split( root, jl, jr, j-1 );
		split(   jr, kl, kr, k-j+1 );
		root = merge( jl, kr );
		switch( q ) {
			case 1:
				root = merge( kl, root );
				break;
			case 2:
				root = merge( root, kl );
				break;
		}
	}

	Node * next = root;
	while( next->l )
		next = next->l;
	int64_t a1 = a[next->i - 1];
	next = root;
	while( next->r )
		next = next->r;
	int64_t an = a[next->i - 1];
	cout << abs( a1 - an ) << endl;

	// DFS to print A
	set<size_t> v;
	stack<Node*> s;
	s.push( root );
	while( !s.empty() ) {
		Node * n = s.top();
		if( v.end() == v.find( n->i ) && n->l ) {
			s.push( n->l );
			v.insert( n->i );
			continue;
		}
		cout << a[n->i - 1] << " ";
		s.pop();
		if( n->r )
			s.push( n->r );
	}
}

