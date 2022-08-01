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

// Complete the maxRegion function below.
int maxRegion(vector<vector<int>> grid) {

	const auto n = grid.size();
	const auto m = grid[0].size();
	vector<std::unordered_set<long>> adj( n*m );

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			if( !grid[i][j] )
				continue;
			if( i > 0 && grid[i-1][j] ) // up center
				adj[i*m+j].emplace( (i-1)*m+j );
			if( i > 0 && j+1 < m && grid[i-1][j+1] ) // up right
				adj[i*m+j].emplace( (i-1)*m+j+1 );
			if( j+1 < m && grid[i][j+1] ) // center right
				adj[i*m+j].emplace( i*m+j+1 );
			if( i+1 < n && j+1 < m && grid[i+1][j+1] ) // down right
				adj[i*m+j].emplace( (i+1)*m+j+1 );
			if( i+1 < n && grid[i+1][j] ) // down center
				adj[i*m+j].emplace( (i+1)*m+j );
			if( i+1 < n && j > 0 && grid[i+1][j-1] ) // down left 
				adj[i*m+j].emplace( (i+1)*m+j-1 );
			if( j > 0 && grid[i][j-1] ) // center left 
				adj[i*m+j].emplace( i*m+j-1 );
			if( i > 0 && j > 0 && grid[i-1][j-1] ) // up left 
				adj[i*m+j].emplace( (i-1)*m+j-1 );
		}
	}

	vector<bool> visited(n*m, false);
	int max_region = 0;
	size_t i = 0;
	do {
		if( !grid[i/m][i%m] || visited[i] )
			continue;

		int curr_region = 0;
		queue<long> bfs;
		bfs.push( i );
		while( ! bfs.empty() ) {
			const auto curr = bfs.front();
			bfs.pop();
			if( visited[curr] )
				continue;
			visited[curr] = true;
			curr_region++;

			for (const auto j: adj[curr]) {
				bfs.push( j );
			}
		}
		max_region = max( curr_region, max_region );
	} while( ++i<n*m );

	return max_region;
}

#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int res = maxRegion(grid);

    cout << res << "\n";

    return 0;
}
