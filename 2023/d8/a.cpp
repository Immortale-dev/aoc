#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

string moves;
map<string, pair<string, string>> network;

void prepare() {
	string s;
	getline(cin, moves);
	getline(cin, s); // skip empty line
	while(getline(cin, s)){
		auto arr = split_line(s, " = ");
		string from = arr[0];
		auto arrTo = split_line(arr[1].substr(1, arr[1].size()-2), ", ");
		network[from] = make_pair(arrTo[0], arrTo[1]);
	}
}

int findCnt(string from, string to) {
	int ind = 0;
	string node = from;
	int cnt = 0;
	while(true) {
		if (node == to) break;
		if (to == "Z" && node[node.size()-1] == 'Z') {
			break;
		}
		char move = moves[ind++];
		ind = ind % moves.size();
		++cnt;
		if (move == 'L') {
			node = network[node].first;
		} else {
			node = network[node].second;
		}
	}
	return cnt;
}

vector<int> findDivs(int a) {
	vector<int> res;
	for(int i=2;i<sqrt(a);i++) {
		while ((a%i) == 0) {
			res.push_back(i);
			a/=i;
		}
	}
	if (a > 1) {
		res.push_back(a);
	}
	return res;
}

ll first() {
	return findCnt("AAA", "ZZZ");
}

ll second() {
	vector<string> allA;
	for(auto &node : network) {
		if (node.first[node.first.size()-1] == 'A') {
			allA.push_back(node.first);
		}
	}
	vector<int> results;
	for(auto node : allA) {
		int res = findCnt(node, "Z");
		results.push_back(res);
	}

	vector<map<int,int>> divs;
	for(int a : results) {
		map<int,int> local_divs;
		for(auto d : findDivs(a)){
			local_divs[d]++;
		}
		divs.push_back(local_divs);
	}
	set<int> udivs;
	for(auto &dv : divs) {
		for(auto &d : dv) {
			udivs.insert(d.first);
		}
	}
	ll res = 1;
	for(auto d : udivs) {
		int dn = 0;
		for(auto& dv : divs) {
			dn = max(dn, dv[d]);
		}
		for(int i=0;i<dn;i++) {
			res *= (ll)d;
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
