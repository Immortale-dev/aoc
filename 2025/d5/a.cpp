#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Range) {
	PARSE_SETUP;
	PARSE(ll) start = SINGLE();
	SKIP(char) = SINGLE('-');
	PARSE(ll) finish = SINGLE();
	SKIP(char) = SINGLE('\n');
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Range) ranges = THROUGH('\n');
	PARSE(ll) ids = UNTIL_END();
};

Input input(std::cin);

ll first() {
	set<ll> ids;
	set<ll> fresh;
	for (ll id : input.ids) {
		ids.insert(id);
	}
	for (auto &r : input.ranges) {
		auto lower = ids.lower_bound(r.start());
		auto upper = ids.upper_bound(r.finish());
		while(lower != upper) {
			fresh.insert(*lower);
			auto nxt = next(lower);
			ids.erase(lower);
			lower = nxt;
		}
	}
	return fresh.size();
}

bool intersect(pair<ll,ll> r1, pair<ll,ll> r2) {
	return r1.first <= r2.second && r2.first <= r1.second;
}

ll second() {
	ll res = 0;
	vector<pair<ll,ll>> vec;
	for (auto &r : input.ranges) {
		vec.push_back({r.start(), r.finish()});
	}
	sort(vec.begin(), vec.end());
	auto current = vec[0];
	for (int i=1;i<vec.size();i++) {
		if (intersect(current, vec[i])) {
			current.second = max(current.second, vec[i].second);
		} else {
			res += current.second - current.first + 1;
			current = vec[i];
		}
	}
	res += current.second - current.first + 1;
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
