/* Copyright (C) 2019 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <stdio.h>
#ifndef SOURCE_PATH_SIZE
#define SOURCE_PATH_SIZE 0
#endif
#define __FILENAME__ (__FILE__ + SOURCE_PATH_SIZE)

#ifdef DEBUG
#define DBG(msg, args...) \
	do { \
		fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
		fflush( stdout ); \
	} while( 0 );
#else
#define DBG(msg, args...)
#endif
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
	private:
		string scrollName;
	public:
		Spell(): scrollName("") { }
		Spell(string name): scrollName(name) { }
		virtual ~Spell() { }
		string revealScrollName() {
			return scrollName;
		}
};

class Fireball : public Spell { 
	private: int power;
	public:
			 Fireball(int power): power(power) { }
			 void revealFirepower(){
				 cout << "Fireball: " << power << endl;
			 }
};

class Frostbite : public Spell {
	private: int power;
	public:
			 Frostbite(int power): power(power) { }
			 void revealFrostpower(){
				 cout << "Frostbite: " << power << endl;
			 }
};

class Thunderstorm : public Spell { 
	private: int power;
	public:
			 Thunderstorm(int power): power(power) { }
			 void revealThunderpower(){
				 cout << "Thunderstorm: " << power << endl;
			 }
};

class Waterbolt : public Spell { 
	private: int power;
	public:
			 Waterbolt(int power): power(power) { }
			 void revealWaterpower(){
				 cout << "Waterbolt: " << power << endl;
			 }
};

class SpellJournal {
	public:
		static string journal;
		static string read() {
			return journal;
		}
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
	/* Enter your code here */

	static int tab[1001][1001];
	struct lcs {
		lcs( ) {} // https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
		int max( int a , int b ) {
			return (a > b ) ? a : b;
		}
		void operator()(const string & a, const string & b){
			// set to zero first row
			for (unsigned int i = 0; i < b.size(); ++i) {
				tab[0][i] = 0;
			}
			// set to zero first col
			for (unsigned int i = 0; i < a.size(); ++i) {
				tab[i][0] = 0;
			}
			int i = 1;
			for (char ci : a) {
				int j = 1;
				for (char cj : b) {
					if( ci == cj ) {
						tab[i][j] = tab[i-1][j-1] + 1;
					} else {
						tab[i][j] = max( tab[i-1][j], tab[i][j-1] );
					}
					j++;
				}
				i++;
			}
			cout << tab[a.size()][b.size()] << endl;
		}
	};

	if( Fireball * ptr = dynamic_cast<Fireball*>( spell ) )
		ptr->revealFirepower();
	else if( Frostbite * ptr = dynamic_cast<Frostbite*>( spell ) )
		ptr->revealFrostpower();
	else if( Thunderstorm * ptr = dynamic_cast<Thunderstorm*>( spell ) )
		ptr->revealThunderpower();
	else if( Waterbolt * ptr = dynamic_cast<Waterbolt*>( spell ) )
		ptr->revealWaterpower();
	else
		lcs( )(spell->revealScrollName(),  SpellJournal::read()) ;

}

class Wizard {
	public:
		Spell *cast() {
			Spell *spell;
			string s; cin >> s;
			int power; cin >> power;
			if(s == "fire") {
				spell = new Fireball(power);
			}
			else if(s == "frost") {
				spell = new Frostbite(power);
			}
			else if(s == "water") {
				spell = new Waterbolt(power);
			}
			else if(s == "thunder") {
				spell = new Thunderstorm(power);
			} 
			else {
				spell = new Spell(s);
				cin >> SpellJournal::journal;
			}
			return spell;
		}
};

//int main() {
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int T;
	cin >> T;
	Wizard Arawn;
	while(T--) {
		Spell *spell = Arawn.cast();
		counterspell(spell);
	}
	return 0;
}

#if 0
// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);
}
#endif


