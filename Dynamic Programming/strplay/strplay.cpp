/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

#include <algorithm>

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
#include <bits/stdc++.h>

using namespace std;

int lcs_rec( const char * a, const char * b, int i, int j ) {
	if( i == 0 || j == 0 )
		return 0;
	if( a[i-1] == b[j-1] )
		return 1 + lcs_rec( a, b, i-1, j-1 );
	return std::max( lcs_rec( a, b, i-1, j ),
	                 lcs_rec( a, b, i, j-1 ));
}

template<int N,int M> struct matrix_t: std::array<std::array<int,N>,M> {
	void print( int n, int m ) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				printf( "%02d ", (*this)[i][j]);
			}
			cout << endl;
		}
	}
};
static matrix_t<3001,3001> tab;


int lcs_dp( const char * a, const char * b, int size_a, int size_b  ) {

	static bool first_time = true;
	if( first_time ) {
		// set to zero first row
		for (unsigned int i = 0; i < 3001; ++i) {
			tab[0][i] = 0;
		}
		// set to zero first col
		for (unsigned int i = 0; i < 3001; ++i) {
			tab[i][0] = 0;
		}
		first_time = false;
	}

	for (int i = 0; i < size_a; ++i) {
		for (int j = 0; j < size_b; ++j) {
			if( a[i] == b[j] ) {
				tab[i+1][j+1] = tab[i][j] + 1;
			} else {
				tab[i+1][j+1] = max( tab[i][j+1], tab[i+1][j] );
			}
		}
	}

	tab.print(size_a+1, size_b+1);

	int max = 0;
	for (int i = 0; i <= size_a; ++i) {
		//max = std::max( max, tab[i][size_a]*tab[size_a][size_a-i]);
		max = std::max( max, tab[1][i]*tab[size_a-i][size_a-i]);
	}
	return max;
}

int lcs_pali_rec( const string & original ) {
	string reversed( original.rbegin(), original.rend() );
	const char * c_reve = reversed.c_str();
	const char * c_orig = original.c_str();
	int size = original.size();
	int max = 0;
	for (int i = 1; i < size-1; ++i) {
		int aux1 = lcs_dp( &c_orig[0], &c_reve[size-i],      i,      i );
		int aux2 = lcs_dp( &c_orig[i], &c_reve[     0], size-i, size-i );
		max = std::max( max, aux1*aux2 );
	}
	return max;
}

int lcs_pali( const string & original ) {
	string reversed( original.rbegin(), original.rend() );
	cout << reversed << endl;
	const char * c_reve = reversed.c_str();
	const char * c_orig = original.c_str();
	int size = original.size();
	return lcs_dp( c_orig, c_reve, size, size );
}

/*
 * Complete the playWithWords function below.
 */
int playWithWords1(const string & s) {
	return lcs_pali( s );
}
void print( vector<vector<int>> & dp, int n ) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf( "%02d ", dp[i][j]);
		}
		cout << endl;
	}
}
#if 1
int playWithWords(string s) {
    /*
     * Write your code here.
     */
     int n=s.size(),m=0;
     vector<vector<int>> dp(n);
     for(int i=0;i<n;i++){
         dp[i]=vector<int>(n);
         dp[i][i]=1;
     }
     for (int cl=2; cl<=n; cl++) {
        for (int i=0; i<n-cl+1; i++){
            int j = i+cl-1; 
            if (s[i] == s[j] && cl == 2) 
               dp[i][j] = 2; 
            else if (s[i] == s[j]) 
               dp[i][j] = dp[i+1][j-1] + 2; 
            else
               dp[i][j] = max(dp[i][j-1], dp[i+1][j]); 
        } 
    }
	 print( dp, n );
    for(int i=0;i<n-1;i++){
        if(dp[0][i]*dp[i+1][n-1] > m)
            m=dp[0][i]*dp[i+1][n-1];
    } 
    return(m);

}
#endif

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	string s;
	getline(cin, s);

	int result = playWithWords(s);

	cout << result << "\n";

	return 0;
}

