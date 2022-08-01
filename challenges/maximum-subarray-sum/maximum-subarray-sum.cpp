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

// Complete the maximumSum function below.
long maximumSum_quadratic(vector<long> a, long m) {

	long max_sum = 0;
	vector<long> prev_sum(a.size(), 0);
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = i; j > 0; --j) {
			prev_sum[j] = (prev_sum[j-1] + a[i]) % m;
			max_sum = std::max(max_sum, prev_sum[j]);
		}
		prev_sum[0] = a[i] % m;
		max_sum = std::max(max_sum, prev_sum[0]);
	}

	return max_sum;
}

long maximumSum(vector<long> a, long m) {

	// mod sum from 0 up to position i
	vector<long> sum(a.size(), 0);
	sum[0] = a[0] % m;
	for (size_t i = 1; i < a.size(); ++i) {
		sum[i] = (sum[i-1] + a[i] ) % m;
	}
	
	// Given sum array, a sum subarray within A0-Ai (ending at Ai) will only
	// produce a larger mod sum if sum[j] (j = start of the subarray) is
	// greater than sum[i] and as close to sum[i] as possible.
	//
	set<long> sorted_sum;
	sorted_sum.emplace( sum[0] );
	long max_sum = sum[0];
	for (size_t i = 1; i < a.size(); ++i) {
		long max_sum_up_to_i = max( sum[i], a[i] % m );
		auto search = sorted_sum.upper_bound( sum[i] );
		if( search != sorted_sum.end() ) {
			max_sum_up_to_i =  max( max_sum_up_to_i, m + ((sum[i] - *search) % m) );
		}
		max_sum = max( max_sum, max_sum_up_to_i );
		sorted_sum.emplace_hint( search, sum[i] );
	}

	return max_sum;
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
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        long m = stol(nm[1]);

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split_string(a_temp_temp);

        vector<long> a(n);

        for (int i = 0; i < n; i++) {
            long a_item = stol(a_temp[i]);

            a[i] = a_item;
        }

        long result = maximumSum(a, m);

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
