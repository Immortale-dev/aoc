#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Item) {
	PARSE_SETUP;
	PARSE(string) line = COUNT(7);
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Item) items = UNTIL_END();
};

Input input(std::cin);

bool fit(vector<int> &lock, vector<int> &key) {
	for (int i=0;i<lock.size();i++) {
		if (lock[i] + key[i] > 5) return false;
	}
	return true;
}

ll first() {
	vector<vector<int>> locks;
	vector<vector<int>> keys;

	for (auto &item : input.items) {
		if (item.line[0][0] == '#') {
			vector<int> lock;
			for (int l=0;l<item.line[0].size();l++) {
				for (int i=0;i<item.line.size();i++) {
					if (item.line[i][l] != '#') {
						lock.push_back(i-1);
						break;
					}
				}
			}
			locks.push_back(lock);
		} else {
			vector<int> key;
			for (int l=0;l<item.line[0].size();l++) {
				for (int i=item.line.size()-1;i>=0;i--) {
					if (item.line[i][l] != '#') {
						key.push_back(item.line.size()-1-i-1);
						break;
					}
				}
			}
			keys.push_back(key);
		}
	}

	int res = 0;
	for (auto &lock : locks) {
		for (auto &key : keys) {
			if (fit(lock, key)) res++;
		}
	}

	return res;
}

ll second() {
	return 0;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
