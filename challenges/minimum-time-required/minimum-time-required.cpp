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

#define DIV_ROUND_UP( a, b ) ((a) + ((b) - 1)) / (b)

vector<string> split_string(string);

// Complete the minTime function below.
long minTime_slow(vector<long> machines, long goal) {
	sort( machines.begin(), machines.end() );
	vector<int> tab( goal * machines[0], 0 );

	for (auto e : machines) {
		for (size_t j = e-1; j < tab.size(); j+=e) {
			tab[j] += 1;
		}
	}

	int counter = 0;
	size_t i = 0;
	for (i = 0; i < tab.size() && counter < goal; ++i) {
		counter += tab[i];
	}
	return i;
}

// Complete the minTime function below.
long minTime_wrong(vector<long> machines, long goal) {

	vector<long> & days_per_machine = machines;
	const auto n = days_per_machine.size();
	// [0] : total days need to build [1] machines by machines [2]
	list<array<long,3>> res( n );

	sort( days_per_machine.begin(), days_per_machine.end() );
	size_t i = 0;
	for (auto & e : res) {
		e[2]  = days_per_machine[i];
		e[1]  = goal / n + (i < (goal % n) ? 1 : 0);
		e[0]  = e[2] * e[1];
		i++;
		//DBG( "e[0] %d\n", e[0]);
		//DBG( "e[1] %d\n", e[1]);
		//DBG( "e[2] %d\n", e[2]);
	}

	struct {
		bool operator()(const array<long,3> & a, const array<long,3> & b) const
		{
			if( a[0] == b[0] )
				return a[2] < b[2];
			else
				return a[0] < b[0];
		}
	} customLess;
	res.sort( customLess );

	long prev_max = std::numeric_limits<long>::max();
	long curr_max = res.back()[0];
		auto max = res.back();
		auto min = res.front();
	while( prev_max >= curr_max ) {
		max = res.back();
		res.pop_back();
		min = res.front();
		res.pop_front();

		//DBG( "max[0] %d\n", max[0]);
		//DBG( "max[1] %d\n", max[1]);
		//DBG( "max[2] %d\n", max[2]);
		//DBG( "min[0] %d\n", min[0]);
		//DBG( "min[1] %d\n", min[1]);
		//DBG( "min[2] %d\n", min[2]);
		//DBG( "\n");

		max[1] -= 1;
		max[0] -= max[2];
		min[1] += 1;
		min[0] += min[2];

		res.insert( std::lower_bound( res.begin(), res.end(), max, customLess ), max );
		res.insert( std::lower_bound( res.begin(), res.end(), min, customLess ), min );

		prev_max = curr_max;
		curr_max = res.back()[0];
		//DBG( "prev_max %d\n", prev_max );
		//DBG( "curr_max %d\n", curr_max );
	}
#if 0
	for (auto & e : res) {
		printf( "%03d ", e[2] );
	}
	cout << endl;
	for (auto & e : res) {
		printf( "%03d ", e[1] );
	}
	cout << endl;
	for (auto & e : res) {
		printf( "%03d ", e[0] );
	}
	cout << endl;
#endif

	return prev_max;
}

long minTime(vector<long> machines, long goal) {
	// get fast and slowest machines
	sort( machines.begin(),machines.end() );
	auto n = machines.size();
	int64_t fast = machines[0];
	int64_t slow = machines[n-1];

	// lower bound: all machines at the same pace of the fattest one
	auto lower_bound = fast * (goal / n);
	// upper bound: all machines at the same pace of the slowest one
	auto upper_bound = slow * DIV_ROUND_UP( goal , n );

	long low_goal = 0, up_goal = 0;
	for (auto e : machines) {
		low_goal += lower_bound / e;
		 up_goal += upper_bound / e;
	}

	// dicotomic search between lower and upper bounds
	int64_t prev_bound, curr_bound, curr_goal;
	do {
		prev_bound = curr_bound;
		curr_bound = lower_bound + DIV_ROUND_UP(upper_bound-lower_bound,2);
		curr_goal = 0;
		for (auto e : machines) {
			curr_goal += curr_bound / e;
		}
		if( curr_goal > goal )
			upper_bound = curr_bound;
		else
			lower_bound = curr_bound;
	} while( curr_goal != goal && curr_bound != prev_bound );
	// minimize solution found
	do {
		curr_bound--;
		curr_goal = 0;
		for (auto e : machines) {
			curr_goal += curr_bound / e;
		}
	} while( curr_goal == goal );

	return curr_bound+1;
}



// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string nGoal_temp;
    getline(cin, nGoal_temp);

    vector<string> nGoal = split_string(nGoal_temp);

    int n = stoi(nGoal[0]);

    long goal = stol(nGoal[1]);

    string machines_temp_temp;
    getline(cin, machines_temp_temp);

    vector<string> machines_temp = split_string(machines_temp_temp);

    vector<long> machines(n);

    for (int i = 0; i < n; i++) {
        long machines_item = stol(machines_temp[i]);

        machines[i] = machines_item;
    }

    long ans = minTime(machines, goal);

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
