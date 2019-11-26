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

#include <bits/stdc++.h>

using namespace std;

#if 0
//static vector<int> overlaps(10e9+2);
//static vector<int> n_intervals(10e9+2);
static vector<int> overlaps(10e6+2, 0);
static vector<int> n_intervals(10e6+2, 0);
/*
 * Complete the intervalSelection function below.
 */
int intervalSelection(vector<vector<int>> intervals) {
	//std::fill(overlaps.begin(), overlaps.end(), 0);
	//std::fill(n_intervals.begin(), n_intervals.end(), 0);
	int max_j = 0;
	for (auto v : intervals) {
		auto i = v[0];
		auto j = v[1];
		max_j = std::max( max_j, j );
		overlaps[i] += 1;
		overlaps[j+1] -= 1;
		n_intervals[i] += 1;
	}
	for (int i = 1; i < max_j+1; ++i) {
		overlaps[i] += overlaps[i-1];
		n_intervals[i] = n_intervals[i-1] + std::min( n_intervals[i], std::max( 0, 2 - (overlaps[i] - n_intervals[i]) ));
		//cout << overlaps[i] << " ";
	}
	//cout << endl;
	int res = n_intervals[max_j];
	for (int i = 1; i < max_j+1; ++i) {
		//cout << n_intervals[i] << " ";
		overlaps[i] = 0;
		n_intervals[i] = 0;
	}
	//cout << endl;
	return res;
}

/*
 * Complete the intervalSelection function below.
 */
int intervalSelection(vector<vector<int>> intervals) {

	std::unordered_map<int64_t,int> u_overlaps(1002);
	std::unordered_map<int64_t,int> u_n_intervals(1002);

	u_overlaps.emplace( 0, 0 );
	u_n_intervals.emplace( 0, 0 );
	for (auto v : intervals) {
		auto i = v[0];
		auto j = v[1];
		u_overlaps[i] += 1;
		u_overlaps[j+1] -= 1;
		u_n_intervals[i] += 1;
	}

	std::map<int64_t,int> overlaps( u_overlaps.begin(), u_overlaps.end() );
	int64_t prev_i = 0;
	for (auto e : overlaps) {
		auto i = e.first;
		if( i == 0 ) {
			continue;
		}
		u_overlaps[i] += u_overlaps[prev_i];
		prev_i = i;
		//cout << u_n_intervals[i] << " ";
	}
	//cout << endl;

	std::map<int64_t,int> n_intervals( u_n_intervals.begin(), u_n_intervals.end() );
	prev_i = 0;
	for (auto e : n_intervals) {
		auto i = e.first;
		if( i == 0 ) {
			continue;
		}
		u_n_intervals[i] = u_n_intervals[prev_i] + std::min( u_n_intervals[i], std::max( 0, 2 - (u_overlaps[i] - u_n_intervals[i]) ));
		prev_i = i;
		//cout << u_n_intervals[i] << " ";
	}
	//cout << endl;


	int res = u_n_intervals[prev_i];
	return res;
}

/*
 * Complete the intervalSelection function below.
 */
int intervalSelection(vector<vector<int>> intervals) {

	// [0] -> # overlaps ; [1] -> # intervals
	std::unordered_map<int64_t,array<int,2>> unordered_data(1002);

	array<int,2> zero = {0};
	unordered_data.emplace( 0, zero );
	// O(n)
	for (auto v : intervals) {
		auto i = v[0];
		auto j = v[1];
		auto ei = unordered_data.emplace( i, zero );
		ei.first->second[0] += 1; // increment # of overlaps
		ei.first->second[1] += 1; // increment # of intervals
		auto ej = unordered_data.emplace( j+1, zero );
		ej.first->second[0] -= 1; // decrement # of intervals
	}

	// O(log(n))
	std::map<int64_t,array<int,2>> sorted_data( unordered_data.begin(), unordered_data.end() );
	// O(n)
	const auto * prev_e = &(*(sorted_data.begin()));
	for (auto & e : sorted_data) {
		e.second[0] += prev_e->second[0];
		e.second[1]  = prev_e->second[1] + std::min( e.second[1], std::max( 0, 2 - (e.second[0] - e.second[1]) ));
		prev_e = &e;
		cout << e.second[1] << " ";
	}
	cout << endl;
	return prev_e->second[1];
}

void combinations( list<int> & in, list<list<int>> & out ) {

	if( in.size() == 0 )
		return;

	int e = in.front();
	in.pop_front();
	combinations( in, out );

	list<list<int>> my_out;
	for (auto l : out) {
		l.push_back( e );
		my_out.push_back( l );
	}
	for (const auto & l : my_out) {
		out.push_back( l );
	}

	out.emplace_back();
	out.back().push_back( e );
}

int max_overlap(vector<vector<int>> intervals) {
	// i -> # overlaps 
	std::unordered_map<int64_t,int> unordered_data(1002);

	unordered_data.emplace( 0, 0);
	// O(n)
	for (auto v : intervals) {
		auto i = v[0];
		auto j = v[1];
		auto ei = unordered_data.emplace( i, 0 );
		ei.first->second += 1; // increment # of overlaps
		auto ej = unordered_data.emplace( j+1, 0 );
		ej.first->second -= 1; // decrement # of intervals
	}

	// O(log(n))
	std::map<int64_t,int> sorted_data( unordered_data.begin(), unordered_data.end() );
	// O(n)
	int res = 0;
	const auto * prev_e = &(*(sorted_data.begin()));
	for (auto & e : sorted_data) {
		e.second += prev_e->second;
		res = std::max( res, e.second );
		prev_e = &e;
		//cout << e.second[1] << " ";
	}
	//cout << endl;
	return res;

}

/*
 * Complete the intervalSelection function below.
 */
int intervalSelection(vector<vector<int>> intervals) {

	list<int> in;
	list<list<int>> out;

	for (int i = 0; i < intervals.size(); ++i) {
		in.push_back( i );
	}

	size_t max = 0;
	vector<vector<int>> res;
	combinations( in, out );
	for (auto & c : out) {
		vector<vector<int>> tmp;
		for (auto i : c ) {
			tmp.push_back( intervals[i] );
			if( max_overlap( tmp ) < 3 ) {
				if( tmp.size() > max ) {
					max = tmp.size();
					res = tmp;
				}
			}
		}
	}

	for (auto v : res) {
		cout << v[0] << " " << v[1] << endl;
	}


	return max;

}
#endif

/*
 * Complete the intervalSelection function below.
 */
int intervalSelection(vector<vector<int>> intervals) {

	// sort vector by closing points
	struct {
		bool operator()( vector<int> & a, vector<int> & b ) {
			return a[1] < b [1];
		}
	} custom_less;
	std::sort( intervals.begin(), intervals.end(), custom_less );

	int last_overlap = 0; // last point overlaped by two intervals
	int total = 1;
	auto & last = intervals[0]; // last interval selected
	for (size_t i = 1; i < intervals.size(); ++i) {
		auto & curr = intervals[i];

		if( curr[0] <= last_overlap )
			continue;

		last_overlap = last[1] < curr[0] ? last_overlap : last[1];
		total++;
		last = curr;
	}

	return total;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] )
{
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int s_itr = 0; s_itr < s; s_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> intervals(n);
        for (int intervals_row_itr = 0; intervals_row_itr < n; intervals_row_itr++) {
            intervals[intervals_row_itr].resize(2);

            for (int intervals_column_itr = 0; intervals_column_itr < 2; intervals_column_itr++) {
                cin >> intervals[intervals_row_itr][intervals_column_itr];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = intervalSelection(intervals);

        cout << result << "\n";
    }

    return 0;
}

