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

int largest_proper_divisor(int n) {
	if (n == 0) {
		throw invalid_argument("largest proper divisor is not defined for n=0");
	}
	if (n == 1) {
		throw invalid_argument("largest proper divisor is not defined for n=1");
	}
	for (int i = n/2; i >= 1; --i) {
		if (n % i == 0) {
			return i;
		}
	}
	return -1; // will never happen
}

void process_input(int n) {
	int d = 0;
	try {
		d = largest_proper_divisor(n);
		cout << "result=" << d << endl;
	} catch (std::invalid_argument& e) {
		cout << e.what() << endl;
	}
	cout << "returning control flow to caller" << endl;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int n;
	cin >> n;
	process_input(n);
	return 0;
}
