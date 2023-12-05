#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct SMap {
	ll d_start;
	ll s_start;
	ll length;
};

vector<ll> seeds;
vector<vector<SMap>> maps;

void prepare() {
	string s;
	getline(cin, s);
	auto seedsArr = split_line(split_line(s, ": ")[1], " ");
	for (auto n : seedsArr) {
		seeds.push_back(stoll(n));
	}
	getline(cin, s); // empty
	getline(cin, s); // skip names
	vector<SMap> dests;
	while(getline(cin, s)){
		if (s.size() == 0) {
			maps.push_back(dests);
			dests = vector<SMap>();
			getline(cin, s); // skip names
			continue;
		}
		auto valsArr = split_line(s, " ");
		dests.push_back({stoll(valsArr[0]), stoll(valsArr[1]), stoll(valsArr[2])});
	}
	if (dests.size()) {
		maps.push_back(dests);
	}
	for(auto& m : maps) {
		sort(m.begin(), m.end(), [](auto& left, auto& right){
			return left.s_start < right.s_start;
		});
	}
}

ll find_dest(int step, ll source) {
	for(auto& d : maps[step]) {
		if (source >= d.s_start && source < d.s_start + d.length) {
			return source - (d.s_start - d.d_start);
		}
	}
	return source;
}

vector<pair<ll, ll>> find_dest_ranges(int step, pair<ll, ll> source_range) {
	vector<pair<ll, ll>> res;
	ll s = source_range.first;
	ll e = source_range.second;
	auto& m = maps[step];
	for(int i=0;i<m.size();i++) {
		if (m[i].s_start + m[i].length < s) continue;
		if (m[i].s_start >= e) continue;
		if (s < m[i].s_start) {
			res.push_back({s, m[i].s_start});
			s = m[i].s_start;
		}
		ll diff = (m[i].s_start - m[i].d_start);
		ll d = s - diff;
		ll se = min(e, m[i].s_start + m[i].length);
		ll de = se - diff;
		res.push_back({d, de});
		s = min(m[i].s_start + m[i].length, e);
	}
	if (s < e) {
		res.push_back({s,e});
	}
	return res;
}

ll first() {
	ll minLoc = 9999999999999999;
	for(ll seed : seeds) {
		for(int step = 0;step<maps.size();step++) {
			seed = find_dest(step, seed);
		}
		minLoc = min(minLoc, seed);
	}
	return minLoc;
}

ll second() {
	ll minLoc = 9999999999999999;
	vector<pair<ll,ll>> pairs;
	for(int i=0;i<seeds.size();i+=2) {
		pairs.push_back({seeds[i], seeds[i] + seeds[i+1]});
	}
	for(int step=0;step<maps.size();step++) {
		vector<pair<ll,ll>> nextPairs;
		for(auto p : pairs) {
			for(auto pr : find_dest_ranges(step, p)) {
				nextPairs.push_back(pr);
			}
		}
		pairs = nextPairs;
	}
	for(auto& p : pairs) {
		minLoc = min(minLoc, p.first);
	}
	return minLoc;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
