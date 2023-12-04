#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<pair<vector<int>, vector<int>>> piles;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(split_line(s, ": ")[1], " | ");
		vector<int> winning;
		vector<int> your;

		auto winningArr = split_line(arr[0], " ");
		auto yourArr = split_line(arr[1], " ");

		for(string w : winningArr) {
			if (!w.size()) continue;
			winning.push_back(stoi(w));
		}
		for(string w : yourArr) {
			if (!w.size()) continue;
			your.push_back(stoi(w));
		}

		piles.push_back(make_pair(winning, your));
	}
}

ll first() {
	ll res = 0;
	for(auto pile : piles) {
		ll local_res = 0;
		set<ll> s;
		for(auto n : pile.first) {
			s.insert((ll)n);
		}
		for(ll n : pile.second) {
			if (s.count(n)) {
				if (!local_res) {
					local_res = 1;
				} else {
					local_res *= 2ll;
				}
			}
		}
		res += local_res;
	}
	return res;
}

ll second() {
	ll res = 0;
	ll p = 0;
	vector<ll> counts(piles.size(), 1);
	for(auto pile : piles) {
		++p;
		ll local_res = 0;
		set<ll> s;
		for(auto n : pile.first) {
			s.insert((ll)n);
		}
		for(ll n : pile.second) {
			if (s.count(n)) {
				++local_res;
			}
		}
		for(ll i=0;i<local_res;i++) {
			if (p+i >= counts.size()) break;
			counts[p+i] += counts[p-1];
		}
	}
	for(ll n : counts) {
		res += n;
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
