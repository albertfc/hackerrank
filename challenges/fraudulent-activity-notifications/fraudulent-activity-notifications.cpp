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

#if 0
class Median {
	const int _d;
	std::list<int> _left, _right;
	void move_to_left() {
		if( _right.size() - _left.size() > 1  ) {
			_left.push_back( _right.front() );
			_right.pop_front();
		}
	}
	void move_to_right() {
		if( _left.size() - _right.size() > 1  ) {
			_right.push_front( _left.back() );
			_left.pop_back();
		}
	}
public:
	Median( int d ): _d(d){}
	void push( int a ) {
		if( _left.empty() ) {
			_left.push_back( a );
			return;
		}

		if( _left.back() < a ) {
			_right.emplace( std::lower_bound( _right.begin(), _right.end(), a ), a );
			move_to_left();
		} else {
			_left.emplace( std::lower_bound( _left.begin(), _left.end(), a ), a );
			move_to_right();
		}
	}
	void pop( int a ) {
		if( _left.back() < a ) {
			const auto search_r = std::lower_bound( _right.begin(), _right.end(), a );
			if( search_r != _right.end() ) {
				_right.erase( search_r );
				move_to_right();
				return;
			}
		} else {
			const auto search_l = std::lower_bound( _left.begin(), _left.end(), a );
			if( search_l != _left.end() ) {
				_left.erase( search_l );
				move_to_left();
				return;
			}
		}

	}
	float get() const {
		if( _d % 2 ) { // odd
			if( _left.size() > _right.size() ) {
				return _left.back();
			} else {
				return _right.front();
			}
		} else { // even
			return (_left.back() + _right.front()) / 2.;
		}
	}
};
#endif

class Median {
	const int _d;
	std::multiset<int> _left, _right;
	void _move_to_left() {
		if( _right.size() - _left.size() > 1  ) {
			_left.emplace_hint( _left.end(), *(_right.begin()) );
			_right.erase( _right.begin() );
		}
	}
	void _move_to_right() {
		if( _left.size() - _right.size() > 1  ) {
			_right.emplace_hint( _right.begin(), *(_left.rbegin()));
			_left.erase( --_left.end() );
		}
	}
public:
	Median( int d ): _d(d){}
	void push( int a ) {
		if( _left.empty() ) {
			_left.emplace( a );
			return;
		}

		if( *(_left.rbegin()) < a ) {
			_right.emplace( a );
			_move_to_left();
		} else {
			_left.emplace( a );
			_move_to_right();
		}
	}
	void pop( int a ) {
		if( *(_left.rbegin()) < a ) {
			const auto search_r = _right.find( a );
			if( search_r != _right.end() ) {
				_right.erase( search_r );
				_move_to_right();
				return;
			}
		} else {
			const auto search_l = _left.find( a );
			if( search_l != _left.end() ) {
				_left.erase( search_l );
				_move_to_left();
				return;
			}
		}
	}
	float get() const {
		if( _d % 2 ) { // odd
			if( _left.size() > _right.size() ) {
				return *(_left.rbegin());
			} else {
				return *(_right.begin());
			}
		} else { // even
			return ( *(_left.rbegin()) + *(_right.begin()) ) / 2.;
		}
	}
};

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {

	int notices = 0;
	Median m(d);

	for (int i = 0; i < d; ++i) {
		m.push( expenditure[i] );
	}

	for (size_t i = d; i < expenditure.size(); ++i) {
		if( expenditure[i] >= 2*m.get() )
			notices++;

		m.pop( expenditure[i-d] );
		m.push( expenditure[i] );
	}

	return notices;
}


// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    cout << result << "\n";

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
