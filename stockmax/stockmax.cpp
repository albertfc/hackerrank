#include <bits/stdc++.h>

using namespace std;

int64_t stockmax_rec(int64_t i, vector <int64_t> & prices, int64_t stocks) {

	if( i == (int64_t)prices.size() )
		return 0;

	int64_t res;
	int64_t still = stockmax_rec( i+1, prices, stocks );
	int64_t buy = stockmax_rec( i+1, prices, stocks+1) - prices[i];
	res = std::max( still, buy );
	if( stocks ) {
		int64_t sell = stocks * prices[i] + stockmax_rec( i+1, prices, 0 );
		res = std::max( res, sell);
	}
	return res;
}

template< typename T >
void print64_t_vector( std::vector<T> v )
{
	for( auto & e: v )
		std::cout << e << " ";
	std::cout << std::endl;
}

int64_t stockmax_dp(vector <int64_t> & prices) {

	int64_t res = 0;
	vector<int64_t> dp(prices.size()+1);

	int64_t aux2;
	
	dp[0] = 0;
	// for each day
	for( int64_t i=1; i<(int64_t)prices.size()+1; ++i ){
		int64_t max_sell = INT_MIN;
		dp[i] = dp[i-1] - prices[i-1];
		// for each stock
		for( int64_t j=i-1; j>0; --j ) {
			int64_t buy = dp[j-1] - prices[i-1];
			int64_t still = dp[j];
			int64_t aux  = std::max( buy, still );
			if( j < i-1 ) {
				max_sell = std::max( max_sell, aux2+prices[i-1] );
				aux = std::max( aux, max_sell );
			}
			aux2 = dp[j];
			dp[j] = aux;
			res = std::max( res, dp[j] );
		}
		dp[0] = std::max( 0L, dp[1]+prices[i-1] );
		res = std::max( res, dp[0] );
		//#ifndef NDEBUG
		//print64_t_vector( dp );
		//#endif
	}
	return res;
}

int64_t stockmax_linear(vector <int64_t> & prices) {

	vector<int64_t> maxims(prices.size());

	maxims[maxims.size()-1] = prices[prices.size()-1];
	for( auto i=maxims.size()-1; i-- > 0; ) {
		maxims[i] = std::max( maxims[i+1], prices[i] );
	}

	//print64_t_vector( maxims );

	int64_t profit = 0;
	int64_t stocks = 0;
	for( unsigned i=0; i<maxims.size(); ++i ) {
		if( prices[i] < maxims[i] ) { // buy
			profit -= prices[i];
			//if( __builtin_sub_overflow( profit, prices[i], &profit ) )
			//abort();
			stocks += 1;
		} else if( prices[i] == maxims[i] ) { // sell
			profit += prices[i] * stocks;
			stocks = 0;
		} else
			continue;
	}

	return profit;
}


int64_t stockmax(vector <int64_t> & prices) {
	// Complete this function
	//std::cout << stockmax_rec( 0, prices, 0 ) << std::endl;
	//std::cout << stockmax_dp( prices ) << std::endl;
	return stockmax_linear( prices );
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int64_t t;
	cin >> t;
	//t = 1;
	for(int64_t a0 = 0; a0 < t; a0++){
		int64_t n;
		cin >> n;
		//n = 4;
		//vector<int64_t> prices = {1, 3, 1, 2};
		vector<int64_t> prices(n);
		for(int64_t prices_i = 0; prices_i < n; prices_i++){
			cin >> prices[prices_i];
		}
		int64_t result = stockmax(prices);
		cout << result << endl;
	}
	return 0;
}

