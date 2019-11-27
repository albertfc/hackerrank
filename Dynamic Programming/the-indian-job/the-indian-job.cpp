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

bool is_subset_sum( const std::vector<int> & v, int i, int sum ) {
	if( i < 0 )
		return sum == 0;
	else
		return is_subset_sum( v, i-1, sum ) || is_subset_sum( v, i-1, sum - v[i] );
}

#if 0
/*
 * Complete the indianJob function below.
 */
string indianJob(int g, vector<int> arr) {
    /*
     * Write your code here.
     */
	int total_sum = 0;
	for (auto ai : arr) {
		total_sum += ai;
	}
	bool found = false;
	for (int sum = ceil(total_sum/2.) ; sum < g+1 && !found ; ++sum) {
		found = is_subset_sum( arr, arr.size()-1, sum );
	}
	return found ? "YES" : "NO";
}
#endif

std::array<std::array<bool,1000002>,101> dp;

/*
 * Complete the indianJob function below.
 */
string indianJob(int g, vector<int> arr) {
    /*
     * Write your code here.
     */

	// clear dp table
	for (int j = 0; j <= g; ++j) {
		dp[0][j] = false;
	}

	for (int i = 1; i <= (int)arr.size() ; ++i) {
		for (int j = 0; j <= g; ++j) {
			if( arr[i-1] == j ) { // ai == current sum
				dp[i][j] = true;
			} else {
				dp[i][j] = dp[i-1][j];
				if( j - arr[i-1] >= 0 )
					dp[i][j] |= dp[i-1][ j-arr[i-1] ];
			}
		}
	}

	int total_sum = 0;
	for (auto ai : arr) {
		total_sum += ai;
	}
	bool found = false;
	for (int sum = total_sum-g ; sum < g+1 && !found ; ++sum) {
		found = dp[arr.size()][sum];
	}

#if 0
	for (int i = 0; i <= (int)arr.size() ; ++i) {
		for (int j = 0; j <= g; ++j) {
			bool a = dp[i][j] ? true : false;
			cout << a << " ";
		}
		cout << endl;
	}
#endif

	return found ? "YES" : "NO";

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
        string ng_temp;
        getline(cin, ng_temp);

        vector<string> ng = split_string(ng_temp);

        int n = stoi(ng[0]);

        int g = stoi(ng[1]);

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int arr_itr = 0; arr_itr < n; arr_itr++) {
            int arr_item = stoi(arr_temp[arr_itr]);

            arr[arr_itr] = arr_item;
        }

        string result = indianJob(g,arr);

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
