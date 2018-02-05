#include <iostream>
#include <vector>
#include <cstdint>

//#define DEBUG 1

#include <stdio.h>
#ifdef DEBUG
#define DBG(msg, args...) \
    do { \
        fprintf( stdout, "DEBUG %s:%d -- " msg, __FILE__, __LINE__, ##args ); \
        fflush( stdout ); \
    } while( 0 );
#else
#define DBG(msg, args...)
#endif
#define MSG(msg, args...) fprintf( stdout, msg, ##args )
#define WRN(msg, args...) fprintf( stdout, "Warning: %s:%d " msg, __FILE__, __LINE__, ##args )
#define ERR(msg, args...) fprintf( stderr, "Error: %s:%d " msg, __FILE__, __LINE__, ##args )
#define GOTO_ERR(msg, args...) \
    do{ \
        ERR( msg, ##args ); \
        goto errorl; \
    } while( 0 )

int64_t ce_rec( const int32_t n, const uint32_t m, const std::vector<uint32_t> & c )
{
	if( n == 0 ) // Found a solution
		return 1;
	if( n < 0 )  // No solution
		return 0;
	if( m <= 0 && n >= 1 ) // No more coins and still have change --> no solution
		return 0;

	return ce_rec( n, m-1, c ) + ce_rec( n-c[m-1], m, c );
}

void print_matrix( const uint32_t n, const uint32_t m, const uint64_t * matrix )
{
	for( int i = 0; i < n; i++ ) {
		std::cout << i << ": ";
		for( int j = 0; j < m; j++ )
			std::cout << matrix[i*m+j] << " ";
		std::cout << std::endl;
	}
}

int64_t ce( const uint32_t n, const uint32_t m, const std::vector<uint32_t> & c )
{
	// 1 <= n <= 250
	// 1 <= m <= 50
	// With these size is safe to have tab on the stack
	uint64_t tab[n+1][m+1];

	// Init first row with ones
	for( int j = 0; j < m+1; j++ )
		tab[0][j] = 1;
	// Init first col with zeros
	for( int i = 0; i < n+1; i++ )
		tab[i][0] = 0;

	for( int i = 1; i < n+1; i++ )
		for( int j = 1; j < m+1; j++ ) {
			tab[i][j] = tab[i][j-1];
			if( i - (int32_t)c[j-1] >= 0 )
				tab[i][j] += tab[ i - c[j-1] ][j];
		}

#ifdef DEBUG
	print_matrix( n, m, (const uint64_t *)tab );
#endif
	return tab[n][m];
}

int main() {

	// Read n and m
	uint32_t n, m;
	std::cin >> n;
	std::cin >> m;
	DBG( "n = %d\n", n );
	DBG( "m = %d\n", m );

	// read ci
	std::vector<uint32_t> c(m);
	for( int i = 0; i < m; i++ )
		std::cin >> c[i];
#ifdef DEBUG
	DBG( "" );
	for( auto i: c )
		std::cout << i << " ";
	std::cout << std::endl;
#endif

	MSG( "%ld\n", ce( n, m, c ) );
}
