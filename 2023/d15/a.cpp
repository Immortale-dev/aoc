#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> words;

void prepare() {
	string s;
	getline(cin, s);
	words = split_line(s, ",");
}

int hash_s(string s) {
	int res = 0;
	for(auto c : s) {
		res = ((res + c)*17) % 256;
	}
	return res;
}

struct Box {
	list<pair<string, int>> lenses;
	map<string, list<pair<string, int>>::iterator> links;
};

ll first() {
	ll res = 0;
	for(auto s : words) {
		res += hash_s(s);
	}
	return res;
}

ll second() {
	vector<Box> boxes(256);
	for(auto word : words) {
		string label;
		int lense = 0;
		if (word.back() == '-') {
			label = word.substr(0, word.size()-1);
		} else {
			auto arr = split_line(word, "=");
			label = arr[0];
			lense = stoi(arr[1]);
		}
		auto& box = boxes[hash_s(label)];
		if (!lense) {
			if (box.links.count(label)) {
				box.lenses.erase(box.links[label]);
				box.links.erase(label);
			}
		} else {
			if (box.links.count(label)) {
				box.links[label]->second = lense;
			} else {
				box.lenses.push_back({label, lense});
				auto it = --box.lenses.end();
				box.links[label] = it;
			}
		}
	}
	ll res = 0;
	int i=0;
	for(auto& box : boxes) {
		++i;
		ll l_res = 0;
		int slot=0;
		for(auto& lense : box.lenses) {
			l_res += i * ++slot * lense.second;
		}
		res += l_res;
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
