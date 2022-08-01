/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;


template <int n, bool...digits>
struct CheckValues {
	static void check(int x, int y)
	{
		CheckValues<n-1, 0, digits...>::check(x, y);
		CheckValues<n-1, 1, digits...>::check(x, y);
	}
};
// Function partial specialization is not yet allowed as per the standard.

#if 0
// use operator call
template<int power, bool... digits>
struct _reversed_binary_value {
	int operator()() const { return 0;}
};

template<int power, bool... digits>
struct _reversed_binary_value<power,1,digits...> {
	int operator()() const {
		return power + _reversed_binary_value<power*2,digits...>()();
	}
};

template<int power, bool... digits>
struct _reversed_binary_value<power,0,digits...> {
	int operator()() const {
		return _reversed_binary_value<power*2,digits...>()();
	}
};

template<bool... digits>
int __attribute__ ((noinline)) reversed_binary_value() {
	return _reversed_binary_value<1,digits...>()();
}

#else 
// Use inline static function inside a struct
template<int power, bool... digits>
struct _reversed_binary_value {
	inline static int run() { return 0;}
};

template<int power, bool... digits>
struct _reversed_binary_value<power,1,digits...> {
	inline static int run() {
		return power + _reversed_binary_value<power*2,digits...>::run();
	}
};

template<int power, bool... digits>
struct _reversed_binary_value<power,0,digits...> {
	inline static int run() {
		return _reversed_binary_value<power*2,digits...>::run();
	}
};

template<bool... digits>
int __attribute__ ((noinline)) reversed_binary_value() {
	return _reversed_binary_value<1,digits...>::run();
}
#endif

template <bool...digits>
struct CheckValues<0, digits...> {
	static void check(int x, int y)
	{
		int z = reversed_binary_value<digits...>();
		std::cout << (z+64*y==x);
	}
};

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int t; std::cin >> t;

	for (int i=0; i!=t; ++i) {
		int x, y;
		cin >> x >> y;
		CheckValues<6>::check(x, y);
		cout << "\n";
	}
	//cout << reversed_binary_value<1,0,0,1,1,0,1,0,0,1,0>() << endl;
}

