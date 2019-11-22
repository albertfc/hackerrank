/* Copyright (C) 2019 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>
using namespace std;

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

#include<iostream>

using namespace std;

class A
{
	public:
		A(){
			callA = 0;
		}
	private:
		int callA;
		void inc(){
			callA++;
		}

	protected:
		void func(int & a)
		{
			a = a * 2;
			inc();
		}
	public:
		int getA(){
			return callA;
		}
};

class B
{
	public:
		B(){
			callB = 0;
		}
	private:
		int callB;
		void inc(){
			callB++;
		}
	protected:
		void func(int & a)
		{
			a = a * 3;
			inc();
		}
	public:
		int getB(){
			return callB;
		}
};

class C
{
	public:
		C(){
			callC = 0;
		}
	private:
		int callC;
		void inc(){
			callC++;
		}
	protected:
		void func(int & a)
		{
			a = a * 5;
			inc();
		}
	public:
		int getC(){
			return callC;
		}
};

class D: public A,B,C
{

	int val;
	public:
	//Initially val is 1
	D()
	{
		val = 1;
	}

	//Implement this function
	void update_val(int new_val)
	{
		while( new_val % 2 == 0 ) { new_val = new_val / 2; A::func( val );}
		while( new_val % 3 == 0 ) { new_val = new_val / 3; B::func( val );}
		while( new_val % 5 == 0 ) { new_val = new_val / 5; C::func( val );}
	}
	//For Checking Purpose
	void check(int); //Do not delete this line.
};



void D::check(int new_val)
{
	update_val(new_val);
	cout << "Value = " << val << endl << "A's func called " << getA() << " times " << endl << "B's func called " << getB() << " times" << endl << "C's func called " << getC() << " times" << endl;
}


int main()
{
	D d;
	int new_val;
	cin >> new_val;
	d.check(new_val);

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


