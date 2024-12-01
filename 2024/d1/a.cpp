#include <bits/stdc++.h>

using namespace std;

#include "../helpers/parser.h"

typedef long long int ll;

//=======================================//

struct Pair : PARSE_INTERFACE {
	PARSE(int) left = SINGLE();
	PARSE(int) right = SINGLE();
};

struct Input : PARSE_INTERFACE {
	PARSE_SETUP;
	PARSE(Pair) arr = UNTIL_END();
};

Input input(std::cin);

ll first() {
	int diff = 0;
	vector<int> lefts;
	vector<int> rights;
	for (auto &p : input.arr) {
		lefts.push_back(p.left());
		rights.push_back(p.right());
	}
	ranges::sort(lefts);
	ranges::sort(rights);
	for (int i=0;i<lefts.size();i++) {
		diff += abs(lefts[i] - rights[i]);
	}
	return diff;
}

ll second() {
	ll res = 0;
	map<int, ll> rights;
	for (auto &p : input.arr) {
		rights[p.right()]++;
	}
	for (auto &p : input.arr) {
		res += p.left() * rights[p.left()];
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
