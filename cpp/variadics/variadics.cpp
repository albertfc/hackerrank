/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

#if 0
template<bool b, bool...digits>
struct Reversed_binary_value{
	int operator()() {
		Reversed_binary_value<digits...>bb;
		return bb();
	}
};

template<>
struct Reversed_binary_value<0>{
	int operator()() { return 0; }
};

template<>
struct Reversed_binary_value<1>{
	int operator()() { return 1; }
};

template<bool b>
struct Reversed_binary_value<1,b>{
	int operator()() {
		Reversed_binary_value<b> bb;
		return 2 + bb();
	}
};

template<bool b1, bool b2>
struct Reversed_binary_value<1,b1,b2>{
	int operator()() {
		Reversed_binary_value<b1,b2> bb;
		return 4 + bb();
	}
};

template<bool b1, bool b2, bool b3>
struct Reversed_binary_value<1,b1, b2, b3>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3> bb;
		return 8 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4>
struct Reversed_binary_value<1,b1, b2, b3, b4>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4> bb;
		return 16 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5> bb;
		return 32 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6> bb;
		return 64 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7> bb;
		return 128 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8> bb;
		return 256 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9> bb;
		return 512 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10> bb;
		return 1024 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10, bool b11>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11> bb;
		return 2048 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10, bool b11, bool b12>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12> bb;
		return 4096 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10, bool b11, bool b12, bool b13>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13> bb;
		return 8192 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10, bool b11, bool b12, bool b13, bool b14>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14> bb;
		return 16384 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10, bool b11, bool b12, bool b13, bool b14, bool b15>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15> bb;
		return 32768 + bb();
	}
};

template<bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10, bool b11, bool b12, bool b13, bool b14, bool b15, bool b16>
struct Reversed_binary_value<1,b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16>{
	int operator()() {
		struct Reversed_binary_value<b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16> bb;
		return 65536 + bb();
	}
};
template <bool...digits>
int reversed_binary_value( ) {
	Reversed_binary_value<digits...> b;
	return b();
}

#endif

template <bool a> int reversed_binary_value() { return a; }

template < bool... d,bool a, bool b> int reversed_binary_value() {
  return (reversed_binary_value<b, d...>() << 1) + a;
}

template <int n, bool...digits>
struct CheckValues {
	static void check(int x, int y)
	{
		CheckValues<n-1, 0, digits...>::check(x, y);
		CheckValues<n-1, 1, digits...>::check(x, y);
	}
};

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

