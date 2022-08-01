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


bool is_anagram( const array<int,26> & freq_a, const char *b, size_t b_size ) {
	static array<int,26> freq_b;
	freq_b = {{0}};
	for (size_t i = 0; i < b_size; ++i) {
		freq_b[b[i]-'a'] += 1;
	}
	return freq_a == freq_b;
}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {
	int total = 0;

	static array<int,26> freq_a;
	for (size_t i = 1; i < s.size(); ++i) {
		// count anagrams of size i
		for (size_t j = 0; j < s.size()-i; ++j) {
			// reference: substring [j,k)
			size_t k = j+i;
			freq_a = {{0}};
			for (size_t h = j; h < k; ++h) {
				freq_a[s[h]-'a'] += 1;
			}
			for (int l = j+1; l <= s.size()-i; ++l) {
				// variable: substring [l,l+i)
				total += is_anagram( freq_a, s.c_str()+l, i ) ? 1 : 0;
			}
		}
	}

	return total;
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
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        cout << result << "\n";
    }

    return 0;
}
