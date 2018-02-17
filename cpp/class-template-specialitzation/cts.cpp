/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits {
	static string name( int i ) {
		return string( "hola" );
	}
};

template <> struct Traits<Color> {
	static const char * name( int i ) {

		const  map<Color, const char *> translate {
			{ Color::green, "green" },
			{ Color::red, "red" },
			{ Color::orange, "orange" }
		};

		auto it = translate.find( (Color)i );
		return it == translate.end() ? "unknown" : it->second;
	}
};

template <> struct Traits<Fruit> {
	static const char * name( int i ) {

		const  map<Fruit, const char *> translate {
			{ Fruit::apple, "apple" },
			{ Fruit::orange, "orange" },
			{ Fruit::pear, "pear" }
		};

		auto it = translate.find( (Fruit)i );
		return it == translate.end() ? "unknown" : it->second;
	}
};


// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int t = 0; std::cin >> t;

	for (int i=0; i!=t; ++i) {
		int index1; std::cin >> index1;
		int index2; std::cin >> index2;
		cout << Traits<Color>::name(index1) << " ";
		cout << Traits<Fruit>::name(index2) << "\n";
	}
}

