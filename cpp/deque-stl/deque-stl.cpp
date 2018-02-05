/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

template< typename T >
void print_list( std::list<T> l )
{
	std::cout << "LIST: ";
	for( const auto & e: l )
		std::cout << e << " ";
	std::cout << std::endl;
}


// O(n * log2(k)) in time
// O(k) in space
void printKMax1(int arr[], int n, int k){

	list<int> l;
	list<decltype(l.begin())> ll;
	// push back first k elems
	for( int i=0; i<k; i++ ) {
		// insert arr[i] keeping list ordered O(log2 k)
		auto lb = std::lower_bound( l.begin(), l.end(), arr[i] );
		ll.push_back( l.insert( lb, arr[i] ) );
	}
	// get max O(1)
	std::cout << l.back() << " ";
	//print_list( l );
	for( int i=k; i<n; i++ ) {
		// remove front O(1)
		auto aux = ll.front();
		l.erase( aux );
		ll.pop_front();
		// insert arr[i] keeping list ordered O(log2 k)
		auto lb = std::lower_bound( l.begin(), l.end(), arr[i] );
		ll.push_back( l.insert( lb, arr[i] ) );
		// get max O(1)
		std::cout << l.back() << " ";
		//print_list( l );
	}
	std::cout << std::endl;
}

// O(n) in time
// O(k) in space
void printKMax(int arr[], int n, int k){
	deque<int> q;
	for(int i=0;i<k;i++)
	{
		while(!q.empty() && arr[i]>=arr[q.back()]){
			q.pop_back();
		}
		q.push_back(i);
	}
	for(int i=k;i<n;i++){
		cout<<arr[q.front()]<<" ";
		while(!q.empty() && q.front()<=i-k){
			q.pop_front();
		}
		while(!q.empty() && arr[i]>=arr[q.back()]){
			q.pop_back();
		}
		q.push_back(i);

	}
	cout<<arr[q.front()]<<endl;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int t;
	cin >> t;
	while(t>0) {
		int n,k;
		cin >> n >> k;
		int i;
		int arr[n];
		for(i=0;i<n;i++)
			cin >> arr[i];
		printKMax(arr, n, k);
		t--;
	}
	return 0;
}

