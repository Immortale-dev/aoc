#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Present) {
	PARSE_SETUP;
	SKIP(int) = SINGLE();
	SKIP(char) = SINGLE(':');
	PARSE(string) lines = COUNT(3);
};

DEFINE_PARSE_INTERFACE(Tree) {
	PARSE_SETUP;
	PARSE(int) rows = SINGLE();
	SKIP(char) = SINGLE('x');
	PARSE(int) cols = SINGLE();
	SKIP(char) = SINGLE(':');
	PARSE(int) nums = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Present) presents = COUNT(6);
	PARSE(Tree) trees = UNTIL_END();
};

Input input(std::cin);

struct Pr {
	vector<vector<bool>> lines;
	int cells;
};

Pr make_pr(Present& p) {
	vector<vector<bool>> lines;
	int cnt = 0;
	for (auto &l : p.lines) {
		vector<bool> line;
		for (auto c : l) {
			cnt += (c == '#');
			line.push_back(c == '#');
		}
		lines.push_back(std::move(line));
	}
	return {lines, cnt};
}

ll first() {
	vector<Pr> prs;
	for (auto &p : input.presents) {
		prs.push_back(make_pr(p));
	}

	ll res = 0;

	for (auto &t : input.trees) {
		int cells = t.rows() * t.cols();
		int p_cells = 0;
		for (int i=0;i<t.nums.size();i++) {
			p_cells += prs[i].cells * t.nums[i];
		}
		res += (cells - p_cells) > 0;
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
