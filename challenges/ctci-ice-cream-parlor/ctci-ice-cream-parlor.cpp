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

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the whatFlavors function below.
void whatFlavors(vector<int> cost, int money) {
	// cost -> idx list (save only the first two idx)
	std::unordered_map<int,vector<int>> umap;

	// Build map
	for (size_t i = 0; i < cost.size(); ++i) {
		auto e = umap.emplace( cost[i], vector<int>(1,i+1) );
		if( !e.second && e.first->second.size() < 2 ) // if not inserted
			e.first->second.push_back(i+1);
	}

	// Seacrh map
	for (size_t i = 0; i < cost.size(); ++i) {
		const auto c = money-cost[i];
		const auto search = umap.find( c );
		if( search == umap.end() ) // Not found c
			continue; // keep searchig
		if( cost[i] == c && search->second.size() < 2 ) // found but this c is the same as cost[i]
			continue; // keep searchig
		
		// Found a solution!
		size_t res[2];
		res[0] = i+1;
		res[1] = (cost[i] != c) ? search->second[0] : search->second[1];
		cout << res[0] << " " << res[1] << endl;
		return;
	}

}



// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] )
{
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int money;
        cin >> money;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string cost_temp_temp;
        getline(cin, cost_temp_temp);

        vector<string> cost_temp = split_string(cost_temp_temp);

        vector<int> cost(n);

        for (int i = 0; i < n; i++) {
            int cost_item = stoi(cost_temp[i]);

            cost[i] = cost_item;
        }

        whatFlavors(cost, money);
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
