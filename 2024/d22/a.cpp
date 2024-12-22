#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(ll) nums = UNTIL_END();
};

Input input(std::cin);

const ll MOD = 16777216;

ll next_secret(ll n) {
	n = (n ^ (n * 64L)) % MOD;
	n = (n ^ (n / 32L)) % MOD;
	n = (n ^ (n * 2048L)) % MOD;
	return n;
}

ll first() {
	vector<ll> vals;
	for (ll n : input.nums) {
		vals.push_back(n);
	}
	ll res = 0;
	for (int i=0;i<2000;i++) {
		for (auto &n : vals) {
			n = next_secret(n);
		}
	}
	for (auto &n : vals) {
		res += n;
	}
	return res;
}

ll sequence_hash(vector<ll> vals) {
	ll hash = 0;
	for (auto v : vals) {
		hash = hash * 100 + v + 20;
	}
	return hash;
}

ll second() {
	vector<vector<ll>> codes(input.nums.size());
	for (int i=0;i<input.nums.size();i++) {
		codes[i].push_back(input.nums[i]);
	}
	for (int j=0;j<codes.size();j++) {
		for (int i=0;i<2000;i++) {
			codes[j].push_back(next_secret(codes[j][i]));
		}
	}
	unordered_map<ll, ll> results;
	for (auto &vec : codes) {
		list<ll> l;
		unordered_set<ll> uh;
		for (int i=1;i<vec.size();i++) {
			l.push_back((vec[i]%10)-(vec[i-1]%10));
			while (l.size() > 4) {
				l.pop_front();
			}
			if (l.size() == 4) {
				ll hash = sequence_hash(vector<ll>(l.begin(), l.end()));
				if (!uh.count(hash)) {
					results[hash] += (vec[i]%10);
					uh.insert(hash);
				}
			}
		}
	}

	ll res = 0;
	for (auto &it : results) {
		res = max(res, it.second);
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
