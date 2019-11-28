/* Copyright (C) 2019 Albert Farres - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT
 * license, which unfortunately won't be written for another century.
 *
 * You should have received a copy of the MIT license with this file. If not,
 * please write to: albertfc@gmail.com.
 */
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the checkMagazine function below.
void checkMagazine_list(vector<string> magazine, vector<string> note) {
    auto sorted_magz = list<string>( magazine.begin() , magazine.end() );
	sorted_magz.sort();
	for (const auto & word : note) {
		auto search = std::lower_bound( sorted_magz.begin(), sorted_magz.end(), word );
		if( search != sorted_magz.end() && *search == word ) {
			sorted_magz.erase( search );
		} else {
			cout << "No" << endl;
			return;
		}
	}
	cout << "Yes" << endl;
}

// Complete the checkMagazine function below.
void checkMagazine(vector<string> magazine, vector<string> note) {
	// MAP word -> # repetitions
	std::unordered_map<string,int> magz_umap( magazine.size() );
	for (const auto & word : magazine) {
		auto e = magz_umap.emplace( word, 1 );
		if( !e.second ) // if not inserted, increment the repetitions counter
			e.first->second += 1;
	}

	for (const auto & word : note) {
		auto search = magz_umap.find( word );
		if( search != magz_umap.end() && search->second-- > 0 )
			continue; // keep searchig until no word or no more repetitions
		cout << "No" << endl;
		return;
	}
	cout << "Yes" << endl;
}

// dup2 & open
#include <fcntl.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
	if( argc > 1 )
		dup2(open(argv[1], 0), 0);

    string mn_temp;
    getline(cin, mn_temp);

    vector<string> mn = split_string(mn_temp);

    int m = stoi(mn[0]);

    int n = stoi(mn[1]);

    string magazine_temp_temp;
    getline(cin, magazine_temp_temp);

    vector<string> magazine_temp = split_string(magazine_temp_temp);

    vector<string> magazine(m);

    for (int i = 0; i < m; i++) {
        string magazine_item = magazine_temp[i];

        magazine[i] = magazine_item;
    }

    string note_temp_temp;
    getline(cin, note_temp_temp);

    vector<string> note_temp = split_string(note_temp_temp);

    vector<string> note(n);

    for (int i = 0; i < n; i++) {
        string note_item = note_temp[i];

        note[i] = note_item;
    }

    checkMagazine(magazine, note);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

