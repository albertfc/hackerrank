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

// dup2 & open
#include <fcntl.h>
#include <unistd.h>

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

#define MAX_N 30000

typedef vector<std::unordered_set<int>> AdjList;

int dfs(const int n, const AdjList& adj, vector<bool>& visited) {
	if (visited[n]) {
		return 0;
	}

	int res = 1;
	visited[n] = true;
	for (const auto i : adj[n]) {
		res += dfs(i,adj,visited);
	}

	return res;
}

/*
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */
vector<int> componentsInGraph(vector<vector<int>> gb) {
	vector<int> res {numeric_limits<int>::max(), numeric_limits<int>::min()};
	int size = 0;

	// build adjencecy list
	AdjList adj(MAX_N);
	for (const auto& edge: gb) {
		adj[edge[0]-1].insert(edge[1]-1);
		adj[edge[1]-1].insert(edge[0]-1);
		size = max(size, max(edge[0],edge[1]));
	}
	adj.resize(size);

	// keep dfs until all nodes are visited
	vector<bool> visited(size, false);
	for (int i = 0; i < size; ++i) {
		int count = dfs(i,adj,visited);
		if (count>1) {
			res[0] = min(count, res[0]);
			res[1] = max(count, res[1]);
		}
	}

	return res;
}

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);


    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> gb(n);

    for (int i = 0; i < n; i++) {
        gb[i].resize(2);

        string gb_row_temp_temp;
        getline(cin, gb_row_temp_temp);

        vector<string> gb_row_temp = split(rtrim(gb_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int gb_row_item = stoi(gb_row_temp[j]);

            gb[i][j] = gb_row_item;
        }
    }

    vector<int> result = componentsInGraph(gb);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

