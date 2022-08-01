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

// Complete the triplets function below.
long triplets_slow(vector<int> a, vector<int> b, vector<int> c) {

	// Sort and remove duplicates
	const set<int> set_a( a.begin(), a.end() );
	const set<int> set_b( b.begin(), b.end() );
	const set<int> set_c( c.begin(), c.end() );

	long total = 0;
	for (const auto q : set_b) {
		const auto tmp1 = std::distance( set_a.begin(), set_a.upper_bound( q ) );
		const auto tmp2 = std::distance( set_c.begin(), set_c.upper_bound( q ) );
		total += tmp1 * tmp2;
	}

	return total;
}
//
// Complete the triplets function below.
long triplets(vector<int> a, vector<int> b, vector<int> c) {

	// Sort and remove duplicates
	const set<int> set_a( a.begin(), a.end() );
	const set<int> set_b( b.begin(), b.end() );
	const set<int> set_c( c.begin(), c.end() );

	// sorted array -> [0]: value; [1]: position
	vector<array<int,2>> va( set_a.size() );
	size_t i = 0;
	for (auto p : set_a) {
		va[i][0] = p;
		va[i][1] = i;
		i++;
	}
	vector<array<int,2>> vc( set_c.size() );
	i = 0;
	for (auto r :  set_c) {
		vc[i][0] = r;
		vc[i][1] = i;
		i++;
	}

	// sort using a custom function object
	struct {
		bool operator()(const array<int,2> & a,const array<int,2> & b) const {
			return a[0] < b[0];
		}
	} customLess;

	long total = 0;
	array<int,2> search;
	auto tmp1 = va.begin();
	auto tmp2 = vc.begin();
	// for each q qet the number of elemets <= in a and c. Multiply them and you have the number of 
	// triplets with this q
	for (const auto q : set_b) {
		search[0] = q;
		tmp1 = std::upper_bound( tmp1, va.end(), search, customLess );
		const auto val1 = tmp1 != va.end() ? (*tmp1)[1] : va.size();
		tmp2 = std::upper_bound( tmp2, vc.end(), search, customLess );
		const auto val2 = tmp2 != vc.end() ? (*tmp2)[1] : vc.size();
		total += val1 * val2;
	}

	return total;
}


vector<string> split_string(string);

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string lenaLenbLenc_temp;
    getline(cin, lenaLenbLenc_temp);

    vector<string> lenaLenbLenc = split_string(lenaLenbLenc_temp);

    int lena = stoi(lenaLenbLenc[0]);

    int lenb = stoi(lenaLenbLenc[1]);

    int lenc = stoi(lenaLenbLenc[2]);

    string arra_temp_temp;
    getline(cin, arra_temp_temp);

    vector<string> arra_temp = split_string(arra_temp_temp);

    vector<int> arra(lena);

    for (int i = 0; i < lena; i++) {
        int arra_item = stoi(arra_temp[i]);

        arra[i] = arra_item;
    }

    string arrb_temp_temp;
    getline(cin, arrb_temp_temp);

    vector<string> arrb_temp = split_string(arrb_temp_temp);

    vector<int> arrb(lenb);

    for (int i = 0; i < lenb; i++) {
        int arrb_item = stoi(arrb_temp[i]);

        arrb[i] = arrb_item;
    }

    string arrc_temp_temp;
    getline(cin, arrc_temp_temp);

    vector<string> arrc_temp = split_string(arrc_temp_temp);

    vector<int> arrc(lenc);

    for (int i = 0; i < lenc; i++) {
        int arrc_item = stoi(arrc_temp[i]);

        arrc[i] = arrc_item;
    }

    long ans = triplets(arra, arrb, arrc);

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
