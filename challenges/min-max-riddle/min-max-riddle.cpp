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

// Complete the riddle function below.
vector<long> riddle_quadratic(vector<long> arr) {
    // complete this function
	vector<long> res(arr.size(), 0);;

	vector<long> prev_min(arr.size(), 0);
	for (size_t i = 0; i < arr.size(); ++i) {
		for (size_t j = i; j > 0; --j) {
			prev_min[j] = min(prev_min[j-1], arr[i]);
			res[j] = max(res[j], prev_min[j]);
		}
		prev_min[0] = arr[i];
		res[0] = max(res[0], prev_min[0]);
	}

	return res;
}


// not necessary to remove erase postiions
vector<long> riddle_nlogn1(vector<long> arr) {
	vector<long> res(arr.size(), 0);;

	// sort using a custom function object
	vector<array<int,2>> sorted_array(arr.size());
	struct {
		bool operator()(array<int,2> & a, array<int,2> & b) const {
			return a[0] < b[0];
		}
	} valueLess;
	for (size_t i = 0; i < arr.size(); ++i) {
		sorted_array[i][0] = arr[i];
		sorted_array[i][1] = i;
	}
	sort( sorted_array.begin(), sorted_array.end(), valueLess );

	std::unordered_map<int,int> larger_win; // value -> larger window with this values as its minimum
	set<int> idx_set;
	idx_set.emplace(-1);
	idx_set.emplace(arr.size());
	for (size_t i = 0; i < sorted_array.size(); ++i) {
		size_t j = i;
		std::unordered_set<std::unique_ptr<pair<set<int>::iterator,int>>> pos_set;
		do {
			const auto pos = idx_set.emplace( sorted_array[j][1] ).first;
			auto pos_copy0 = pos;
			auto pos_copy1 = pos;
			const auto prev_pos = --pos_copy0;
			const auto next_pos = ++pos_copy1;
			const auto win_size = *next_pos - *prev_pos -1;
			const auto search = larger_win.emplace( sorted_array[j][0], win_size );
			if( ! search.second )
				search.first->second = max( search.first->second, win_size );

			std::unique_ptr<pair<set<int>::iterator,int>> tmp( new pair<set<int>::iterator,int>);
			*tmp = make_pair( next_pos, sorted_array[j][1] );
			pos_set.emplace( std::move( tmp ) );

			idx_set.erase( pos );
			j++;
		} while( j < sorted_array.size() && sorted_array[j-1][0] == sorted_array[j][0] );
		//for (size_t k = i; k < j; ++k) {
		//idx_set.emplace( sorted_array[k][1] );
		//}

		for (const auto & e: pos_set) {
			idx_set.emplace_hint( e->first, e->second );
		}
		i = j-1;
	}

	map<int,int> win_max; // window size -> max value
	for (const auto & e : larger_win) {
		const auto search = win_max.emplace( e.second, e.first );
		if( ! search.second )
			search.first->second = max( search.first->second, e.first );
	}

	for (const auto & e: win_max) {
		res[e.first-1] = e.second;
	}

	int last_value = 0;
	for (auto it = res.rbegin(); it != res.rend(); ++it) {
		if( *it && *it > last_value )
			last_value = *it;
		else
			*it = last_value;
	}

	return res;
}

// O(nlogn): uses a sorted set to find next and previous smaller indices
vector<long> riddle_nlogn(vector<long> arr) {
	vector<long> res(arr.size(), 0);;

	// sort array be value keeping original positions
	vector<array<int,2>> sorted_array(arr.size());
	struct {
		bool operator()(array<int,2> & a, array<int,2> & b) const {
			return a[0] < b[0];
		}
	} valueLess;
	for (size_t i = 0; i < arr.size(); ++i) {
		sorted_array[i][0] = arr[i];
		sorted_array[i][1] = i;
	}
	sort( sorted_array.begin(), sorted_array.end(), valueLess );

	// build a map like this: value -> larger window with this key as its minimum
	std::unordered_map<int,int> larger_win;
	set<int> idx_set;
	idx_set.emplace(-1);
	idx_set.emplace(arr.size());
	for (size_t i = 0; i < sorted_array.size(); ++i) {
		const auto pos = idx_set.emplace( sorted_array[i][1] ).first;
		auto pos_copy0 = pos;
		auto pos_copy1 = pos;
		const auto prev_pos = --pos_copy0;
		const auto next_pos = ++pos_copy1;
		const auto win_size = *next_pos - *prev_pos -1;
		const auto search = larger_win.emplace( sorted_array[i][0], win_size );
		if( ! search.second )
			search.first->second = max( search.first->second, win_size );
	}

	// invert previous map. For repeated windows sizes keep the maximum value
	unordered_map<int,int> win_max; // window size -> max value
	for (const auto & e : larger_win) {
		const auto search = win_max.emplace( e.second, e.first );
		if( ! search.second )
			search.first->second = max( search.first->second, e.first );
	}

	// build solution
	for (const auto & e: win_max) {
		res[e.first-1] = e.second;
	}
	int last_value = 0;
	for (auto it = res.rbegin(); it != res.rend(); ++it) {
		if( *it && *it > last_value )
			last_value = *it;
		else
			*it = last_value;
	}

	return res;
}

vector<long> riddle(vector<long> arr) {
	vector<long> res(arr.size(), 0);;

	//// build a map like this: value -> larger window with this key as its minimum
	stack<array<long,2>> idx_stack;
	idx_stack.push( {{-1,-1}} ); // keep at top {value, pos} of the (left) closest smaller value to current arr[i]
	vector<long> prev_small( arr.size() ); // save previous top for each i
	for (size_t i = 0; i < arr.size(); ++i) {
		while( ! idx_stack.empty() && idx_stack.top()[0] >= arr[i] ) {idx_stack.pop();}
		prev_small[i] = idx_stack.top()[1];
		idx_stack.push( {{arr[i], (long)i}} );
	}
	// do the same but backwards, so we get the right closest smaller 
	// win size with arr[i] as its minimun value is the diference between these smallers (left & right) indices
	idx_stack = stack<array<long,2>>();
	idx_stack.push( {{-1,(long)arr.size()}} );
	std::unordered_map<long,long> larger_win;
	for (long i = arr.size()-1; i >= 0; --i) {
		while( ! idx_stack.empty() && idx_stack.top()[0] >= arr[i] ) {idx_stack.pop();}
		const auto next_small_i = idx_stack.top()[1];
		idx_stack.push( {{arr[i], (long)i}} );
		const auto win_size = next_small_i - prev_small[i] -1;
		const auto search = larger_win.emplace( arr[i], win_size );
		if( ! search.second )
			search.first->second = max( search.first->second, win_size );
	}

	// invert previous map. For repeated windows sizes keep the maximum value
	unordered_map<long,long> win_max; // window size -> max value
	for (const auto & e : larger_win) {
		const auto search = win_max.emplace( e.second, e.first );
		if( ! search.second )
			search.first->second = max( search.first->second, e.first );
	}

	// build solution
	for (const auto & e: win_max) {
		res[e.first-1] = e.second;
	}
	int last_value = 0;
	for (auto it = res.rbegin(); it != res.rend(); ++it) {
		if( *it && *it > last_value )
			last_value = *it;
		else
			*it = last_value;
	}

	return res;
}
// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<long> res = riddle(arr);

    for (int i = 0; i < res.size(); i++) {
        cout << res[i];

        if (i != res.size() - 1) {
            cout << " ";
        }
    }

    cout << "\n";

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
