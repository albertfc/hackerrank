/* Copyright (C) 2022 Albert Farres - All Rights Reserved
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

#ifndef NDEBUG
#define DBG(msg, args...) \
	do { \
		fprintf( stdout, "DEBUG %s:%d -- " msg, __FILENAME__, __LINE__, ##args ); \
		fflush( stdout ); \
	} while( 0 );
#else
#define DBG(msg, args...)
#endif

class HotelRoom {
	public:
		HotelRoom(int bedrooms, int bathrooms) 
			: bedrooms_(bedrooms), bathrooms_(bathrooms) {}

		virtual ~HotelRoom() {}

		virtual int get_price() {
			return 50*bedrooms_ + 100*bathrooms_;
		}
	private:
		int bedrooms_;
		int bathrooms_;
};

class HotelApartment : public HotelRoom {
	public:
		HotelApartment(int bedrooms, int bathrooms) 
			: HotelRoom(bedrooms, bathrooms) {}

		int get_price() override {
			return HotelRoom::get_price() + 100;
		}
};

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int n;
	cin >> n;
	vector<HotelRoom*> rooms;
	for (int i = 0; i < n; ++i) {
		string room_type;
		int bedrooms;
		int bathrooms;
		cin >> room_type >> bedrooms >> bathrooms;
		if (room_type == "standard") {
			rooms.push_back(new HotelRoom(bedrooms, bathrooms));
		} else {
			rooms.push_back(new HotelApartment(bedrooms, bathrooms));
		}
	}

	int total_profit = 0;
	for (auto room : rooms) {
		total_profit += room->get_price();
	}
	cout << total_profit << endl;

	for (auto room : rooms) {
		delete room;
	}
	rooms.clear();

	return 0;
}
