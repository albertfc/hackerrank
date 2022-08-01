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

class Median {
	typedef  typename multiset<int>::iterator iterator;

	multiset<int>   _data; // sorted values
	deque<iterator> _iterators;
	iterator        _median;

	bool is_next( iterator begin, const iterator& find, const iterator& end ) {
		while( begin != end && *begin == *find ) {
			if (begin == find) {
				return true;
			}
			begin++;
		}
		return false;
	}

	public:
	Median(const vector<int>& v, const int n) {
		for (int i = 0; i < n; ++i) {
			_iterators.push_back( _data.insert(v[i]) );
		}
		_median = _data.begin();
		advance(_median, _data.size()/2);
	}
	int get_double() const {
		int res;
		//auto check = _data.begin();
		//advance(check, _data.size()/2);
		if( _data.size() % 2 == 0 ) {
			res = *_median + *prev(_median);
			//res = *check + *prev(check);
		} else {
			res = *_median * 2;
			//res = *check*2;
		}
		//DBG("%d\n", res);
		return res;
	}
	void pop_front() {
		const auto old_el_it = _iterators.front();
		const auto old_el = *old_el_it;
		_iterators.pop_front();
		if        ( !(_data.size()%2) && old_el >  *_median) {
			_median--;
		//} else if ( !(_data.size()%2) && old_el <  *_median) {
		//	_median++;
		//} else if (  _data.size()%2 && old_el >  *_median) {
		//	_median--;
		} else if (  _data.size()%2 && old_el <  *_median) {
			_median++;
		} else if ( old_el == *_median ) {
			if (_median == old_el_it) {
				if (!(_data.size()%2)) {
					_median--;
				} else {
					_median++;
				}
			} else {
				if (         _data.size()%2  &&  is_next(_median,old_el_it,_data.end())) {
					// nothing
				} else if (  _data.size()%2  && !is_next(_median,old_el_it,_data.end())) {
					_median++;
				} else if (!(_data.size()%2) &&  is_next(_median,old_el_it,_data.end())) {
					_median--;
				} else if (!(_data.size()%2) && !is_next(_median,old_el_it,_data.end())) {
					// nothing
				}
			}
		}
		_data.erase( old_el_it );

		//auto check = _data.begin();
		//advance(check, _data.size()/2);
		//if( check != _median ) {
		//	DBG( "POP check = %d | _median = %d\n", *check, *_median);
		//	DBG("POP size = %lu\n", _data.size());
		//	DBG("POP old = %d\n", old_el);
		//	DBG( "POP real distance: %ld\n", distance(_data.begin(), check))
		//	DBG( "POP calc distance: %ld\n", distance(_data.begin(), _median))
		//	abort();
		//} //else
		//	DBG("POP %d\n", old_el);
	}
	void push_back( const int& new_el ) {
		_iterators.push_back( _data.insert(new_el) );
		if        (  (_data.size()%2) && new_el <  *_median ) {
			_median--;
		//} else if (  _data.size()%2 && new_el >= *_median ) {
		//	_median++;
		} else if ( !(_data.size()%2) && new_el >= *_median ) {
			_median++;
		//} else if ( !_data.size()%2 && new_el <  *_median ) {
		//	_median--;
		}

		//auto check = _data.begin();
		//advance(check, _data.size()/2);
		//if( check != _median ) {
		//	DBG( "PUSH check = %d | _median = %d\n ", *check, *_median);
		//	DBG("PUSH size = %lu\n", _data.size());
		//	DBG("PUSH new = %d\n", new_el);
		//	DBG( "PUSH real distance: %ld\n", distance(_data.begin(), check))
		//	DBG( "PUSH calc distance: %ld\n", distance(_data.begin(), _median))
		//	abort();
		//} //else
		//	DBG("PUSH %d\n", new_el);
	}
};

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
	Median median(expenditure,d);
	int count = 0;
	// loop expenditures keeping last 'd' expenditures sorted to directly compute median
	for (int i = d; i < expenditure.size(); i++) {
		if (expenditure[i] >= median.get_double()) {
			//DBG("%d\n", expenditure[i]);
			count++;
		}
		median.push_back(expenditure[i]);
		median.pop_front();
	}
	return count;
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
