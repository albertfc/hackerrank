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
#define __FILENAME__ (&__FILE__[SOURCE_PATH_SIZE])

#ifndef NDEBUG
#define DBG(msg, args...) \
	do { \
		fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
		fflush( stdout ); \
	} while( 0 );
#else
#define DBG(msg, args...)
#endif

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
#if 0
// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
	//build 'matrix' connections
	vector<std::unordered_set<int>> connections(n);
	for( const auto & v: cities ) {
		connections[ v[0]-1 ].emplace( v[1]-1 );
		connections[ v[1]-1 ].emplace( v[0]-1 );
	}

	// iterate for al cities
	// if it has not access to a lib, build a lib
	// otherwise check what is cheaper, build a road or a lib
	vector<bool> has_acces_to_a_lib(n);
	has_acces_to_a_lib[0] = true;
	long total = c_lib;
	for( int i = 1; i<n; i++ ) {
		has_acces_to_a_lib[i] = false;
		for( const auto & city: connections[i] ) {
			if( has_acces_to_a_lib[city] ) {
				has_acces_to_a_lib[i] = true;
				break;
			}
		}
		if( ! has_acces_to_a_lib[i] ) {
			total += c_lib;
			has_acces_to_a_lib[i] = true;
		} else {
			total += ( c_road < c_lib ) ? c_road : c_lib;
		}
	}

	return total;
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
	// for each connected subgraph (with size m), check whats is cheaper:
	// - build a lib in each city : m * c_lib
	// - build one lib and m-1 roads to connect all cities: c_lib + (m-1)*c_road

	if( c_road >= c_lib )
		return n * c_lib;

	//build 'matrix' connections
	vector<std::unordered_set<int>> connections(n);
	for( const auto & v: cities ) {
		connections[ v[0]-1 ].emplace( v[1]-1 );
		connections[ v[1]-1 ].emplace( v[0]-1 );
	}

	
	vector<bool> is_city_visited(n,false);
	long total = 0;
	// iterate until all cities are visted
	while( true ) {
		// find next city not visited
		int city = 0;
		while( is_city_visited[city] ) {city++;}
		if( city == n ) // no more cities to visit
			break;

		// visit all its connections and count them
		int visited = 0;
		unordered_set<int> search;
		search.emplace( city );
		while( !search.empty() ) {
			auto curr_city_it = search.begin();
			int curr_city = *curr_city_it;
			search.erase( curr_city_it );
			is_city_visited[curr_city] = true;
			for( const auto & neighbor: connections[curr_city] ) {
				if( !is_city_visited[neighbor] && search.find( neighbor ) == search.end() )
					search.emplace( neighbor );
			}
			visited++;
		}

		// chack whats is cheaper
		long opt1 = visited * c_lib;
		long opt2 = c_lib + (visited-1)*c_road;

		total += (opt1<opt2) ? opt1 : opt2;
	}

	return total;
}
#endif

long dfs( const int n, vector<bool> & visited, const vector<std::unordered_set<int>> & adj ) {
	if( visited[n] )
		return 0;

	long res = 1;
	visited[n] = true;
	for( const auto  v :adj[n] ) {
		res += dfs( v, visited, adj );
	}

	return res;
}


long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
	// for each connected subgraph (with size m), check whats is cheaper:
	// - build a lib in each city : m * c_lib
	// - build one lib and m-1 roads to connect all cities: c_lib + (m-1)*c_road

	//if( c_road >= c_lib )
	//return n * c_lib;

	//build 'matrix' connections
	vector<std::unordered_set<int>> connections(n);
	for( const auto & v: cities ) {
		connections[ v[0]-1 ].emplace( v[1]-1 );
		connections[ v[1]-1 ].emplace( v[0]-1 );
	}

	long total = 0;
	vector<bool> visited(n,false);
	for( int i = 0; i<n; i++ ) {
		long tmp;
		if( (tmp = dfs( i, visited, connections )) == 0 )
			continue;
		// chack whats is cheaper
		long opt1 = tmp * c_lib;
		long opt2 = c_lib + (tmp-1)*c_road;
		total += (opt1<opt2) ? opt1 : opt2;
	}

	return total;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

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
