#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <cstddef>

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
#define MSG(msg, args...) fprintf( stdout, msg, ##args )
#define WRN(msg, args...) fprintf( stdout, "Warning: %s:%d " msg, __FILENAME__, __LINE__, ##args )
#define ERR(msg, args...) fprintf( stderr, "Error: %s:%d " msg, __FILENAME__, __LINE__, ##args )
#define GOTO_ERR(msg, args...) \
    do{ \
        ERR( msg, ##args ); \
        goto errorl; \
    } while( 0 )

int sd_rec( const int i, const char *p, const int j, const char *q, const int s )
{
	if( i < 0 || j < 0 )
		return 0;
	if( p[i] == q[j] )
		return 1 + sd_rec( i-1, p, j-1, q, s );
	else if( s > 0 )
		return 1 + sd_rec( i-1, p, j-1, q, s-1 );
	else
		return 0;
}


int sd_rec_main( const int n, const char *p, const char *q, const int s )
{
	// Compute longuest common suffix for each possible p q combination and return the maximum.
	// Use s as number of differences you can fine in a given suffix
	int res = 0;
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ ) {
			res = std::max( res, sd_rec( i, p, j, q, s ) );
		}
	return res;
}

#ifndef NDEBUG
void print_matrix( const int n, const int m, const int * matrix )
{
	for( int i = 0; i < n; i++ ) {
		std::cout << i << ": ";
		for( int j = 0; j < m; j++ )
			std::cout << matrix[i*m+j] << " ";
		std::cout << std::endl;
	}
}
#endif

int*** allocate_3d( const ssize_t rows, const ssize_t cols, const ssize_t planes )
{
	int * mem = (int *)malloc( sizeof( int ) * rows * cols * planes );
	int ***cube = (int ***)malloc( sizeof(int**) * planes );

	for( ssize_t k = 0; k < planes; k++ ) {
		int **plane = (int **)malloc( sizeof(int*) * rows );
		cube[k] = plane;
		for( ssize_t i = 0; i < rows; i++ )
			cube[k][i] = &mem[ k*rows*cols + i*cols ];
	}
	return cube;
}

int sd_dp( const int n, const char *p, const char *q, const int s )
{
	int res = 0;

	//int tab[s+2][n+1][n+1]; // max n is 1500, safe to be in stack
	int ***tab = allocate_3d( n+1, n+1, s+2);

	for( int i = 0; i < n+1; i++ )
		for( int j = 0; j < n+1; j++ )
			tab[0][i][j] = -1;

	for( int k = 1; k <= s+1; k++ )
	{
		// Init first row with zeros
		for( int j = 0; j < n+1; j++ )
			tab[k][0][j] = 0;
		// Init first col with zeros
		for( int i = 0; i < n+1; i++ )
			tab[k][i][0] = 0;

		// Init first k rows with 1..i
		for( int i = 1; i < k; i++ )
			for( int j = 1; j < n+1; j++ )
				tab[k][i][j] = i;
		// Init first k cols with 1..j
		for( int i = 1; i < n+1; i++ )
			for( int j = 1; j < k; j++ )
				tab[k][i][j] = j;

		for( int i = k; i < n+1; i++ )
			for( int j = k; j < n+1; j++ ) {
				if( p[i-1] == q[j-1] ) {
					tab[k][i][j] = tab[k][i-1][j-1] + 1;
					for( int l = 1; l < k; l++ )
						tab[k][i][j] = std::max( tab[k][i][j], l+tab[k-l][i-l-1][j-l-1] );
					res = std::max( res, tab[k][i][j] );
				} else
					tab[k][i][j] = tab[k-1][i-1][j-1] + 1;
			}
#ifndef NDEBUG
		DBG( "%d matrix -- res = %d\n", k, res );
		print_matrix( n+1, n+1, &tab[k][0][0] );
#endif
	}
	return res;
}

//static int tab[2][1500][1500]; // max n is 1500, safe to be in stack
int sd_dp2( const int n, const char *p, const char *q, const int s )
{
	int res = 0;
	//int tab[2][n+1][n+1]; // max n is 1500, safe to be in stack
	int ***tab = allocate_3d( n+1, n+1, 2);
	// tab[0] -> k
	// tab[1] -> L

	for( int k = 0; k < 2; k++ ) {
		// Init first row with zeros
		for( int j = 0; j < n+1; j++ )
			tab[k][0][j] = 0;
		// Init first col with zeros
		for( int i = 0; i < n+1; i++ )
			tab[k][i][0] = 0;
	}

	for( int i = 1; i < n+1; i++ )
		for( int j = 1; j < n+1; j++ ) {
			if( p[i-1] == q[j-1] ) {
				tab[0][i][j] = tab[0][i-1][j-1];
				tab[1][i][j] = tab[1][i-1][j-1] + 1;
			} else {
				const int next_k = tab[0][i-1][j-1] + 1;
				if( next_k <= s ) { // there is room for more differences
					tab[0][i][j] = next_k;
					tab[1][i][j] = tab[1][i-1][j-1] + 1;
				} else if( s ) { // no more room for differences
					// count common symbols from start to first difference
					int l = tab[1][i-1][j-1];
					int c = 0;
					while( p[i-1-l] == q[j-1-l] ) {l--; c++;}
					tab[0][i][j] = tab[0][i-1][j-1];
					// New L is previous minus counted common symbols
					tab[1][i][j] = tab[1][i-1][j-1]-c;
				} else { // s == 0
					tab[0][i][j] = 0;
					tab[1][i][j] = 0;
				}
			}
			res = std::max( res, tab[1][i][j] );
		}

#ifndef NDEBUG
		DBG( "matrix0 -- res = %d\n", res );
		print_matrix( n+1, n+1, &tab[0][0][0] );
		DBG( "matrix1 -- res = %d\n", res );
		print_matrix( n+1, n+1, &tab[1][0][0] );
#endif
	return res;
}

int main() {

	// Read T
	int t;
	std::cin >> t;
	//t = 1;
	DBG( "t = %d\n", t );
	// for each case
	for( int i = 0; i < t; i++ ) {
		// Read S
		int s;
		std::cin >> s;
		//s = 2;
		// Read P and Q
		std::string p, q;
		std::cin >> p;
		std::cin >> q;
		//p = "tabriz";
		//q = "torino";

		DBG( "s = %d; p = %s; q = %s\n", s, p.c_str(), q.c_str() );

		auto res = sd_dp2( q.size(), p.c_str(), q.c_str(), s );
		DBG( "%d\n", sd_rec_main( q.size(), p.c_str(), q.c_str(), s ) );
		assert( "Failed test" && res == sd_rec_main( q.size(), p.c_str(), q.c_str(), s ));
		std::cout << res  << std::endl;
	}
}
