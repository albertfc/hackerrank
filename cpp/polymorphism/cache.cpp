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

class LRUCache: public Cache {
	int usage;

	int get(int k, int v) {
		Node *n;
		auto e = mp.find(k);
		if( e != mp.end()  ) {
			n = e->second;
			if( v != -1 )
				n->value = v;
		} else if( v != -1 ) {
			n = new Node(k,v);
			mp[k] = n;
			if( ++usage > cp ) {
				// remove tail
				if( tail ) {
					Node *old_tail = tail;
					if( tail->prev ) {
						tail->prev->next = NULL;
						tail = tail->prev;
					} else
						tail = NULL;
					if( old_tail == head )
						head = NULL;
					mp.erase( old_tail->key );
					delete old_tail;
					--usage;
				}
			}
		} else
			return -1;
		if( n == head )
			return head->value;
		// detach n
		if( n->prev ) {
			n->prev->next = n->next;
		}
		if( n->next ) {
			n->next->prev = n->prev;
		}
		n->next = NULL;
		// Set n as head
		Node * old_head = head;
		if( old_head && old_head != n ) {
			old_head->prev = n;
			n->next = old_head;
		}
		head = n;
		if( !tail )
			tail = head;
		return head->value;
	}

	public:
		LRUCache( int capacity ) {
			cp = capacity;
			tail = head = NULL;
			usage = 0;
		}
		virtual void set(int k, int v) {
			get( k, v );
		}

		virtual int get(int k) {
			return LRUCache::get( k , -1);
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

