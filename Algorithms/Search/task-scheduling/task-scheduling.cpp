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

#ifndef NDEBUG
#define DBG(msg, args...) \
	do { \
		fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
		fflush( stdout ); \
	} while( 0 );
#else
#define DBG(msg, args...)
#endif

vector<string> split_string(string);

/*
 * Complete the taskScheduling function below.
 */
using node_t = array<int,3>; // [0] deadline, [1] duration, [2] overshoot
struct sort_by_deadline{
	bool operator()( const node_t & a, const node_t & b ) {
		return a[0] < b[0];
	}
};
using set_t = std::multiset<node_t, sort_by_deadline>;
static set_t dl( {{{0,0,0}}} ); // sorted data by deadline

int taskScheduling_slow(int d, int m) {

	static int max_overshoot = 0;

	node_t tmp = {{d,m,0}};
	for (auto it = dl.emplace( tmp ); it != dl.end(); ++it) {
		auto prev_it = --it;
		auto curr_it = ++it;

		int curr_deadline  = (*curr_it)[0];
		int curr_duration  = (*curr_it)[1];
		int prev_deadline  = (*prev_it)[0];
		int prev_overshoot = (*prev_it)[2];

		int * curr_oveshoot = (int*)&(*curr_it)[2];
		*curr_oveshoot = curr_deadline - (prev_deadline - prev_overshoot + curr_duration);

		max_overshoot = max( -(*curr_oveshoot), max_overshoot );
	}

	return max_overshoot;
}

struct node2_t {
	node2_t *p, *l, *r;
	int o; // overshoot
	int d; // deadline
	int m; // minutes
	int max; // max overshoot;
	node2_t( node2_t *_p, node2_t *_l, node2_t *_r, int _o, int _d, int _m, int _max ) :
		p( _p ), l( _l ), r( _r ), o( _o ), d( _d ), m( _m ), max( _max ) {}
};

struct sort_by_deadline2{
	bool operator()( const node2_t * a, const node2_t * b ) {
		return a->d < b->d;
	}
};
using set2_t = std::set<node2_t*, sort_by_deadline2>;
static node2_t root( nullptr, nullptr, nullptr, 0, 0, 0,std::numeric_limits<int>::max() );
static set2_t dl2( {&root} ); // sorted data by deadline

int taskScheduling(int d, int m) {

	static int max_overshoot = 0;

	node2_t * node = new node2_t( nullptr, nullptr, nullptr, 0, d, m, std::numeric_limits<int>::max() );

	// insert node in a BST
	node2_t * prev;
	node2_t * curr = &root;
	while( curr ) {
		prev = curr;
		curr =  (d > curr->d) ? curr->r : curr->l;
	}
	if( prev->d > d )
		prev->l = node;
	else
		prev->r = node;
	node->p = prev;

	// compute overshoot by this node
	auto search = dl2.insert( node );
	prev = *(--(search.first));
	node->o = d - (prev->d + m);
	node->max = node->o;

	// walk up overshoot
	curr = node;
	node2_t * p = curr->p;
	while( p ) {
		if( p->l == curr ) { // less
			p->o += -node->m;
		}
		p->max = std::min( p->max, p->o + ((p->r) ? p->r->max : 0) - ((p->l) ? p->l->max : 0) );
		max_overshoot = std::min( max_overshoot, p->max );

		curr = p;
		p = curr->p;
	}

	return -max_overshoot;
	//return (root.max < 0) ? -root.max : 0;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string dm_temp;
        getline(cin, dm_temp);

        vector<string> dm = split_string(dm_temp);

        int d = stoi(dm[0]);

        int m = stoi(dm[1]);

        int result = taskScheduling(d, m);

        cout << result << "\n";
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
