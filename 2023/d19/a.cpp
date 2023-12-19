#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Cond {
	char name;
	bool is_great;
	int num;
	string dir;
	bool last = false;
};

struct Rule {
	string name;
	vector<Cond> conds;
};

struct Prod {
	int x,m,a,s;
};

vector<Rule> rules;
vector<Prod> prods;

void prepare() {
	string s;
	while(getline(cin, s)){
		if (!s.size()) break;
		auto arr = split_line(s, "{");
		string rule_name = arr[0];
		auto condArr = split_line(arr[1].substr(0, arr[1].size()-1), ",");
		vector<Cond> conds;
		for(int i=0;i<condArr.size()-1;i++) {
			auto& c = condArr[i];
			auto cArr = split_line(c, ":");
			conds.push_back({cArr[0][0], cArr[0][1] == '>', stoi(cArr[0].substr(2)), cArr[1]});
		}
		conds.push_back({'.', false, 0, condArr[condArr.size()-1], true});
		rules.push_back({rule_name, conds});
	}

	while(getline(cin, s)){
		auto arr = split_line(s.substr(1, s.size()-2), ",");
		vector<int> pds;
		for(string a : arr) {
			auto pArr = split_line(a, "=");
			pds.push_back(stoi(pArr[1]));
		}
		prods.push_back({pds[0], pds[1], pds[2], pds[3]});
	}
}

string process(map<char, int>& prod, Rule& rule) {
	for(auto& cond : rule.conds) {
		if (cond.last) return cond.dir;
		if (cond.is_great && prod[cond.name] > cond.num) return cond.dir;
		if (!cond.is_great && prod[cond.name] < cond.num) return cond.dir;
	}
	throw logic_error("unreachable");
}

struct Rng {
	ll start,finish;
};

ll range_size(Rng& r) {
	return r.finish-r.start;
}

pair<map<char, Rng>, map<char, Rng>> split_range(map<char, Rng>& prod, char what, ll n) {
	map<char, Rng> left = prod;
	map<char, Rng> right = prod;
	left[what] = { min(left[what].start, n), min(left[what].finish, n) };
	right[what] = { max(right[what].start, n), max(right[what].finish, n) };
	return {left, right};
}

bool is_empty_range(map<char, Rng>& prod) {
	for(auto& r : prod) {
		if (r.second.start == r.second.finish) return true;
	}
	return false;
}

vector<pair<string, map<char, Rng>>> process_range(map<char, Rng>& range, Rule& rule) {
	map<char, Rng> prod = range;
	vector<pair<string, map<char, Rng>>> res;
	for(auto& cond : rule.conds) {
		if (cond.last) {
			res.push_back({cond.dir, prod});
			break;
		}
		auto new_r = split_range(prod, cond.name, cond.num + cond.is_great);
		if (cond.is_great) {
			res.push_back({cond.dir, new_r.second});
			prod = new_r.first;
		} else {
			res.push_back({cond.dir, new_r.first});
			prod = new_r.second;
		}
	}
	return res;
}

ll first() {
	vector<map<char, int>> prods_map;
	for(auto& p : prods) {
		map<char, int> m;
		m['x'] = p.x;
		m['m'] = p.m;
		m['a'] = p.a;
		m['s'] = p.s;
		prods_map.push_back(m);
	}

	map<string, Rule> rules_map;
	for(auto& rule : rules) {
		rules_map[rule.name] = rule;
	}

	vector<int> accepted;
	for(int i=0;i<prods_map.size();i++) {
		string a = "in";
		while(true) {
			a = process(prods_map[i], rules_map[a]);
			if (a == "A") {
				accepted.push_back(i);
				break;
			}
			if (a == "R") {
				break;
			}
		}
	}

	ll res = 0;
	for(auto ind : accepted) {
		res += prods[ind].x + prods[ind].m + prods[ind].a + prods[ind].s;
	}

	return res;
}

ll second() {
	map<char, Rng> r;
	r['x'] = {1,4001};
	r['m'] = {1,4001};
	r['a'] = {1,4001};
	r['s'] = {1,4001};

	vector<pair<string, map<char, Rng>>> ranges;
	ranges.push_back({"in", r});

	map<string, Rule> rules_map;
	for(auto& rule : rules) {
		rules_map[rule.name] = rule;
	}

	ll accepted = 0;
	while(ranges.size()) {
		vector<pair<string, map<char, Rng>>> new_ranges;
		for(auto& m : ranges) {
			auto res = process_range(m.second, rules_map[m.first]);
			for(auto& r : res) {
				if (is_empty_range(r.second)) continue;
				if (r.first == "R") continue;
				if (r.first == "A") {
					accepted += range_size(r.second['x']) * range_size(r.second['m']) * range_size(r.second['a']) * range_size(r.second['s']);
					continue;
				}
				new_ranges.push_back(r);
			}
		}
		ranges = new_ranges;
	}

	return accepted;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
