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

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Person {
	string name;
	int age;

	virtual void getdata() = 0;
	virtual void putdata() = 0;
};

class Professor: public Person {
	static int counter;
	int id;
	int publications;

	virtual void getdata() {
		cin >> name;
		cin >> age;
		cin >> publications;
		id = counter++;
	}
	virtual void putdata() {
		cout << name << " " << age << " " << publications << " " << id << endl;
	}
};

class Student: public Person {
	static int counter;
	int id;
	int marks_sum = 0;

	virtual void getdata() {
		cin >> name;
		cin >> age;
		for (int i = 0; i < 6; ++i) {
			int tmp;
			cin >> tmp;
			marks_sum += tmp;
		}
		id = counter++;
	}
	virtual void putdata() {
		cout << name << " " << age << " " << marks_sum << " " << id << endl;
	}
};

int Professor::counter = 1;
int Student::counter = 1;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

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


