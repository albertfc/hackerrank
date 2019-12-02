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

// Complete the findShortest function below.

/*
 * For the unweighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] to <name>_to[i].
 *
 */
int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, int val) {
	vector<std::unordered_set<int>> adj(graph_nodes); //adjacency list
	vector<bool> visited( graph_nodes, false ); // visited list
	deque<int> bfs_queue; // BFS queue
	vector<pair<bool,deque<int>::reverse_iterator>> bfs_map(graph_nodes); // BFS map (id -> BFS queue location; bool flags iterator validity)

	// build bfs queue and map
	for (int i = 0; i < graph_nodes; ++i) {
		if( ids[i] == val ) {
			bfs_queue.push_back( i );
			bfs_map[i] = make_pair( true, bfs_queue.rbegin() );
		} else {
			bfs_map[i] = make_pair( false, bfs_queue.rend() );
		}
	}

	size_t iteration_size = bfs_queue.size();
	if( iteration_size < 2 )
		return -1;

	// build adj list
	for (size_t i = 0; i < graph_from.size(); ++i) {
		adj[graph_from[i]-1].emplace( graph_to[i]-1 );
		adj[graph_to[i]-1].emplace( graph_from[i]-1 );
	}

	size_t iteration_counter = 0;
	size_t distance = 0;
	while( !bfs_queue.empty() ) {
		// pop front
		auto front = bfs_queue.front();
		bfs_queue.pop_front();
		bfs_map[front].first = false;
		visited[front] = true;
		if( iteration_size--  == 0 ) {
			iteration_size = iteration_counter;
			iteration_counter = 0;
			distance += 2;
		}

		// push adj not visited
		for (auto i : adj[front]) {
			if( visited[i] )
				continue;
			if( ! bfs_map[i].first ) {
				bfs_queue.push_back( i );
				bfs_map[i] = make_pair( true, bfs_queue.rbegin() );
				iteration_counter++;
			} else { // found !
				if( std::distance( bfs_map[i].second, bfs_queue.rbegin() )+1 < iteration_size ) {
					// added in previous iteration
					distance += 1;
				} else {
					distance += 2;
				}
				bfs_queue.clear();
				break;
			}
		}
	}

	return distance;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int graph_nodes;
    int graph_edges;

    cin >> graph_nodes >> graph_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> graph_from(graph_edges);
    vector<int> graph_to(graph_edges);

    for (int i = 0; i < graph_edges; i++) {
        cin >> graph_from[i] >> graph_to[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string ids_temp_temp;
    getline(cin, ids_temp_temp);

    vector<string> ids_temp = split_string(ids_temp_temp);

    vector<long> ids(graph_nodes);

    for (int i = 0; i < graph_nodes; i++) {
        long ids_item = stol(ids_temp[i]);

        ids[i] = ids_item;
    }

    int val;
    cin >> val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int ans = findShortest(graph_nodes, graph_from, graph_to, ids, val);

    cout << ans << "\n";

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
