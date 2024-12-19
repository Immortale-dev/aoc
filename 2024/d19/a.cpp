#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(string) towels = THROUGH_LINE();
	PARSE(string) patterns = UNTIL_END();
};

Input input(std::cin);

void prepare() {
	for (auto &t : input.towels) {
		if (t[t.size()-1] == ',') t.pop_back();
	}
}

ll matches(string pattern, vector<string> &towels) {
	vector<ll> dp(pattern.size()+1);
	dp[0] = 1;
	for (int i=0;i<pattern.size();i++) {
		if (!dp[i]) continue;
		for (auto &t : towels) {
			if (pattern.compare(i,t.size(),t) != 0) continue;
			dp[i+t.size()] += dp[i];
		}
	}
	return dp[pattern.size()];
}

ll first() {
	vector<string> towels(input.towels.begin(), input.towels.end());
	int res = 0;
	for (auto &pattern : input.patterns) {
		res += !!matches(pattern, towels);
	}
	return res;
}

ll second() {
	vector<string> towels(input.towels.begin(), input.towels.end());
	ll res = 0;
	for (auto &pattern : input.patterns) {
		res += matches(pattern, towels);
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
