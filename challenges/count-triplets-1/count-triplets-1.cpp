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

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the countTriplets function below.
long countTriplets_old(vector<long> arr, long r) {

	vector<array<long,3>> tmp(arr.size()); // 0->val 1->id 2->exponent
	size_t i = 0;
	for (auto & e : tmp) {
		e[0] = arr[i];
		e[1] = i;
		e[2] = -1;
		i++;
	}

	// sort using a custom function object
    struct {
        bool operator()(const array<long,3> & a, const array<long,3> &b) const
        {   
            return a[0] < b[0];
        }   
    } valueLess;
	sort( tmp.begin(), tmp.end(), valueLess );

	if( r == 1 ) {
		long res = 0;
		vector<array<long,3>>::iterator prev_search, curr_search;
		curr_search = tmp.begin();
		do {
			prev_search = curr_search;
			const auto elem = *prev_search;
			curr_search = std::upper_bound( prev_search, tmp.end(), elem, valueLess );
			const auto n_elems = std::distance( prev_search, curr_search );
			// n! / (3! * (n-3!))
			res += (n_elems * (n_elems-1) * (n_elems-2)) / (3*2);
		} while( curr_search != tmp.end() );
		return res;
	}

	// compute exponents
	std::unordered_map<long,int> powers; // power -> # of powers
	int exp = 0;
	for (auto & e : tmp) {
		while( e[0] > (long)std::pow(r,exp) ) { exp++; }
		if( e[0] != (long)std::pow(r,exp) )
			continue;

		e[2] = exp;
		auto search = powers.emplace( exp, 1 );
		if( ! search.second ) // element already exits
			search.first->second++; // increment counter
	}

	// sort using a custom function object
    struct {
        bool operator()(array<long,3> & a, array<long,3> &b) const
        {   
            return a[1] < b[1];
        }   
    } idLess;
	sort( tmp.begin(), tmp.end(), idLess );

	long triplets = 0;
	for (const auto & e : tmp) {
		if( e[2] < 0 )
			continue;

		const auto search0 = powers.find( e[2]+1 );
		const auto search1 = powers.find( e[2]+2 );
		if( search0 != powers.end() && search1 != powers.end() ) {
			triplets += search0->second * search1->second;
		}

		// decrement counter for current exponent
		const auto search2 = powers.find( e[2] );
		if( --search2->second == 0 ) // erase when it reaches 0
			powers.erase( search2 );
	}

	return triplets;
}

long countTriplets(vector<long> arr, long r) {
	long triplets = 0;
	unordered_map<long,long> left, right;

	// init right
	for (const auto e : arr) {
		const auto search = right.emplace( e, 1 );
		if( ! search.second ) // element already exits
			search.first->second++; // increment counter
	}

	for (const auto e : arr) {
		// decrement counter for current element in right map
		const auto search = right.find( e );
		if( --search->second == 0 ) // erase when it reaches 0
			right.erase( search );

		// count elems equal to arr[i]/r at left and equal to arr[i]*r at right
		if( e % r == 0) {
			const auto search0 = left.find( e/r );
			const auto search1 =right.find( e*r );
			if( search0 != left.end() && search1 != right.end() ) {
				triplets += search0->second * search1->second;
			}
		}

		// increment counter for current element in left map
		const auto search3 = left.emplace( e, 1 );
		if( ! search3.second ) // element already exits
			search3.first->second++; // increment counter
	}

	return triplets;
}


// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string nr_temp;
    getline(cin, nr_temp);

    vector<string> nr = split(rtrim(nr_temp));

    int n = stoi(nr[0]);

    long r = stol(nr[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long ans = countTriplets(arr, r);

    cout << ans << "\n";

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
