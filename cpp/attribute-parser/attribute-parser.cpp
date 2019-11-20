/* Copyright (C) 2019 Albert Farres - All Rights Reserved
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

#ifdef DEBUG
#define DBG(msg, args...) \
	do { \
		fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
		fflush( stdout ); \
	} while( 0 );
#else
#define DBG(msg, args...)
#endif

struct Node {
	std::map<std::string,std::string> attrs;
	std::map<std::string,Node*>       children;
	Node*                             parent;
};

void make_query( const Node * node, const char * query ) {
	// Check for attribute (end case)
	if( query[0] == '~' ) {
		const auto search = node->attrs.find( &query[1] );
		if( search != node->attrs.end() ) {
			cout << search->second << endl;
		} else {
			cout << "Not Found!" << endl;
		}
		return;
	}

	// Get tag name
	size_t i_ini = 0;
	if( query[0] == '.' )
		i_ini = 1;
	size_t i = i_ini;
	while( query[i] != '.' && query[i] != '~' ) i++;
	std::string tag_name( &query[i_ini], i-i_ini );

	// find node tag
	const auto search = node->children.find( tag_name );
	if( search != node->children.end() ) {
		// query recursively
		make_query( search->second, &query[i] );
	} else {
		cout << "Not Found!" << endl;
	}
}

Node * parse_HRML( Node * parent, const std::string & line ) {
	DBG( "%s\n", line.c_str() );

	// Check for a clossing tag
	if( line[1] == '/' ) {
		return parent->parent;
	}

	// We are on a openning tag
	Node * n = new Node();
	n->parent = parent;

	// Get name
	size_t i = 1;
	while( line[i] != ' ' && line[i] != '>' ) i++;
	std::string && tag_name = line.substr( 1, i-1 );

	// Get attrs
	while( line[i] != '>' ) {
		// get name
		size_t i_ini = ++i;
		while( line[i] != ' ' ) i++;
		std::string && key = line.substr( i_ini, i-i_ini);
		// skip \s=\s"
		i = i+4; i_ini = i;
		// get value
		while( line[i] != '"' ) i++;
		std::string && value = line.substr( i_ini, i-i_ini);
		// add attribute to node
		n->attrs.emplace( key , value );
		// advance
		i++;
	}

	// Build node and return
	parent->children.emplace( tag_name, n );
	return n;
}

void dps( const Node * n, string prefix ) {
	for (const auto & attribute : n->attrs) {
		cout << attribute.first << "=" << attribute.second << " ";
	}
	cout << endl;
	cout << prefix;
	for (const auto & child: n->children) {
		cout << child.first << " ";
		dps( child.second, prefix+"  " );
	}
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int n, q;
	cin >> n >> q;
	string line;
	getline( cin, line );

	Node root;
	root.parent = nullptr;

	Node * node = &root;
	for (int i = 0; i < n; ++i) {
		getline( cin, line );
		node = parse_HRML( node, line );
	}
	//dps( &root, "" );
	for (int i = 0; i < q; ++i) {
		getline( cin, line );
		make_query( &root, line.c_str() );
	}
}

