/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

typedef struct node_t {
	node_t * child;
	bool prefix;
} node;
node root[10] = {{NULL}};

bool no_prefix_set( const string & s ) {
	node * prev = NULL;
	node * n = root;
	for( const char & c : s  ) {
		n = &n[c-'a'];
		if( n->prefix )
			return true;
		if( n->child == NULL )
			n->child = (node*)calloc( sizeof(node), 10 );
		prev = n;
		n = n->child;
	}
	prev->prefix = true;
	for( int i=0; i<10; i++ )
		if( n[i].child )
			return true;
	return false;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	size_t n;
	cin >> n;
	for(size_t arr_i = 0; arr_i < n; arr_i++){
		string sti;
		cin >> sti;
		if( no_prefix_set( sti ) ) {
			cout << "BAD SET" << endl << sti << endl;
			return 0;
		}
	}
	cout << "GOOD SET" << endl;
	return 0;
}

