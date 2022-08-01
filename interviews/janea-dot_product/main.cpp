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



/*
 * Complete the 'cosine_similarity' function below.
 *
 * The function is expected to return a DOUBLE.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY a_keys
 *  2. DOUBLE_ARRAY a_values
 *  3. INTEGER_ARRAY b_keys
 *  4. DOUBLE_ARRAY b_values
 */

double cosine_similarity(vector<int> a_keys, vector<double> a_values, vector<int> b_keys, vector<double> b_values) {

	std::unordered_map<int,double> a;
	std::unordered_map<int,double> b;

	int i = 0;
	for (auto e : a_keys) {
		a.emplace(e, a_values[i++]);
	}
	i = 0;
	for (auto e : b_keys) {
		b.emplace(e, b_values[i++]);
	}

	// dot product and magnitudes
	double dotp = 0.0;
	double mag_a = 0.0;
	double mag_b = 0.0;
	i = 0;
	for (auto e : a_keys) {
		double a_val = a_values[i++];
		auto it = b.find(e);
		if (it != b.end()) {
			dotp += a_val * it->second;
			a.erase(a.find(e));
		}
		mag_a += a_val * a_val;

	}
	i = 0;
	for (auto e : b_keys) {
		double b_val = b_values[i++];
		auto it = a.find(e);
		if (it != a.end()) {
			dotp += b_val * it->second;
			b.erase(b.find(e));
		}
		mag_b += b_val * b_val;
	}

	return dotp / (sqrt(mag_a) * sqrt(mag_b));
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);


    ofstream fout(getenv("OUTPUT_PATH"));

    string a_keys_count_temp;
    getline(cin, a_keys_count_temp);

    int a_keys_count = stoi(ltrim(rtrim(a_keys_count_temp)));

    vector<int> a_keys(a_keys_count);

    for (int i = 0; i < a_keys_count; i++) {
        string a_keys_item_temp;
        getline(cin, a_keys_item_temp);

        int a_keys_item = stoi(ltrim(rtrim(a_keys_item_temp)));

        a_keys[i] = a_keys_item;
    }

    string a_values_count_temp;
    getline(cin, a_values_count_temp);

    int a_values_count = stoi(ltrim(rtrim(a_values_count_temp)));

    vector<double> a_values(a_values_count);

    for (int i = 0; i < a_values_count; i++) {
        string a_values_item_temp;
        getline(cin, a_values_item_temp);

        double a_values_item = stod(ltrim(rtrim(a_values_item_temp)));

        a_values[i] = a_values_item;
    }

    string b_keys_count_temp;
    getline(cin, b_keys_count_temp);

    int b_keys_count = stoi(ltrim(rtrim(b_keys_count_temp)));

    vector<int> b_keys(b_keys_count);

    for (int i = 0; i < b_keys_count; i++) {
        string b_keys_item_temp;
        getline(cin, b_keys_item_temp);

        int b_keys_item = stoi(ltrim(rtrim(b_keys_item_temp)));

        b_keys[i] = b_keys_item;
    }

    string b_values_count_temp;
    getline(cin, b_values_count_temp);

    int b_values_count = stoi(ltrim(rtrim(b_values_count_temp)));

    vector<double> b_values(b_values_count);

    for (int i = 0; i < b_values_count; i++) {
        string b_values_item_temp;
        getline(cin, b_values_item_temp);

        double b_values_item = stod(ltrim(rtrim(b_values_item_temp)));

        b_values[i] = b_values_item;
    }

    double result = cosine_similarity(a_keys, a_values, b_keys, b_values);

    cout << result << "\n";

    fout.close();

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

