#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Range) {
	PARSE_SETUP;
	PARSE(ll) start = SINGLE();
	SKIP(char) = SINGLE('-');
	PARSE(ll) end = SINGLE();
	SKIP(char) = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Range) ranges = UNTIL_END();
};

Input input(std::cin);

ll digits_count(ll num) {
	int r = 0;
	while (num > 0) {
		r++;
		num/=10;
	}
	return r;
}

ll make_invalid(ll val, ll times = 1) {
	ll cnt = digits_count(val);
	ll mult = 1;
	while(cnt--) mult *= 10;

	ll res = val;
	while(times--) {
		res = res * mult + val;
	}
	return res;
}

ll first() {
	ll start = 1;
	ll end = 100000;
	ll res = 0;

	assert(make_invalid(123) == 123123);

	for (ll i=start;i<end;i++) {
		ll val = make_invalid(i);
		for (auto &r : input.ranges) {
			if (r.start() <= val && r.end() >= val) {
				res += val;
				break;
			}
		}
	}
	return res;
}

ll second() {
	ll start = 1;
	ll end = 100000;
	ll res = 0;
	std::set<ll> used;

	assert(make_invalid(12, 2) == 121212);

	for (ll i=start;i<end;i++) {
		if (used.contains(i)) continue;
		for (ll j=1;j<=10;j++) {
			ll val = make_invalid(i, j);
			if (val > end*end) break;
			used.insert(val);
			for (auto &r : input.ranges) {
				if (r.start() <= val && r.end() >= val) {
					res += val;
					break;
				}
			}
		}
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
