/* Copyright (C) 2018 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
	Node* prev;
	Node* next;
	int key;
	int value;
	Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
	Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
	protected: 
		map<int,Node*> mp; //map the key to the node in the linked list
		int cp;  //capacity
		Node* tail; // double linked list tail pointer
		Node* head; // double linked list head pointer
		virtual void set(int, int) = 0; //set function
		virtual int get(int) = 0; //get function
};

struct LRUCache: public Cache {
	int curr_cp;
	LRUCache(int c): curr_cp(0) {cp = c; tail = nullptr; head = nullptr;}

	void set_head( Node* n ) {
		if (head == n) {
			return;
		}
		// remove from list
		if (n->prev) {
			n->prev->next = n->next;
		}
		if (n->next) {
			n->next->prev = n->prev;
		}
		// fix tail
		if (tail == n && n->prev) {
			tail = n->prev;
		}
		// add to head
		if (head) {
			head->prev = n;
		}
		n->next = head;
		n->prev = nullptr;
		head = n;
	}

	virtual void set(int k, int v) override {
		// find key
		Node* n;
		try {
			n = mp.at(k);
			n->value = v;
			// if found set node at head
			set_head( n );
		}catch(std::out_of_range) {
			// if not found set new node at head and remove tail if full
			n = new Node(k,v);
			mp.emplace(k,n);
			curr_cp++;
			if (tail && curr_cp > cp) {
				if (tail->prev) {
					tail->prev->next = nullptr;
				}
				auto* old_tail = tail;
				tail = tail->prev;
				mp.erase( mp.find(old_tail->key) ); // remove from map
				delete old_tail; // delete node
				curr_cp--;
			}
			if( !tail )
				tail = n;
			set_head(n);
		}
	}

	virtual int get(int k) override {
		// find key
		Node* n;
		try {
			n = mp.at(k);
		}catch(std::out_of_range) {
			return -1;
		}
		// set key at head
		set_head( n );

		return n->value;
	}
};

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

	int n, capacity,i;
	cin >> n >> capacity;
	LRUCache l(capacity);
	for(i=0;i<n;i++) {
		string command;
		cin >> command;
		if(command == "get") {
			int key;
			cin >> key;
			cout << l.get(key) << endl;
		} 
		else if(command == "set") {
			int key, value;
			cin >> key >> value;
			l.set(key,value);
		}
	}
	return 0;
}

