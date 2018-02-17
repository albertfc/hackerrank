/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Matrix {
	vector<vector<int>> a;

	Matrix & operator+( Matrix & m ) {
		for( size_t i=0; i<a.size(); i++ )
			for( size_t j=0; j<a[i].size(); j++ )
				a[i][j] += m.a[i][j];
		return *this;
	}
};

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);
	int cases,k;
	cin >> cases;
	for(k=0;k<cases;k++) {
		Matrix x;
		Matrix y;
		Matrix result;
		int n,m,i,j;
		cin >> n >> m;
		for(i=0;i<n;i++) {
			vector<int> b;
			int num;
			for(j=0;j<m;j++) {
				cin >> num;
				b.push_back(num);
			}
			x.a.push_back(b);
		}
		for(i=0;i<n;i++) {
			vector<int> b;
			int num;
			for(j=0;j<m;j++) {
				cin >> num;
				b.push_back(num);
			}
			y.a.push_back(b);
		}
		result = x+y;
		for(i=0;i<n;i++) {
			for(j=0;j<m;j++) {
				cout << result.a[i][j] << " ";
			}
			cout << endl;
		}
	}  
	return 0;
}

