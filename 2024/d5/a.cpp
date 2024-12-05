#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Rule) {
	PARSE_SETUP;
	PARSE(int) x = SINGLE();
	SKIP(char) = SINGLE('|');
	PARSE(int) y = SINGLE();
	SKIP(char) = SINGLE('\n');
};

DEFINE_PARSE_INTERFACE(Page) {
	PARSE_SETUP;
	SKIP(char) = SINGLE(',');
	PARSE(int) val = SINGLE();
};

DEFINE_PARSE_INTERFACE(Update) {
	PARSE_SETUP;
	PARSE(int) first = SINGLE();
	PARSE(Page) pages = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Rule) rules = UNTIL('\n');
	PARSE(Update) updates = UNTIL_END();
};

Input input(std::cin);

unordered_map<int, unordered_set<int>> rules;
vector<vector<int>> updates;

void prepare() {
	for (auto &rule : input.rules) {
		rules[rule.x()].insert(rule.y());
	}
	for (auto &update : input.updates) {
		vector<int> u;
		u.push_back(update.first());
		for (auto &page : update.pages) {
			u.push_back(page.val());
		}
		updates.push_back(u);
	}
}

ll first() {
	int res = 0;
	for (auto &update : updates) {
		if (is_sorted(update.begin(), update.end(), [](int a, int b){ return rules[a].count(b); })) {
			res += update[update.size()/2];
		}
	}
	return res;
}

ll second() {
	int res = 0;
	for (auto &update : updates) {
		if (!is_sorted(update.begin(), update.end(), [](int a, int b){ return rules[a].count(b); })) {
			vector<int> u(update);
			sort(u.begin(), u.end(), [](int a, int b){
				return rules[b].count(a);
			});
			res += u[u.size()/2];
		}
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
