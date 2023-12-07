#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<pair<string, ll>> hands;

int get_type(string hand, bool part2 = false) {
	map<char, int> m;
	int j = 0;
	for(char c : hand) {
		if (c == 'J' && part2) {
			j++;
		} else {
			m[c]++;
		}
	}
	vector<int> parts;
	for(auto p : m) {
		parts.push_back(p.second);
	}
	sort(parts.begin(),parts.end(),greater<int>());
	if (!parts.size()) {
		parts.push_back(0);
	}
	parts[0] += j;
	int res = 0;
	int mult = 10;
	for(auto p : parts) {
		res += (p-1) * mult;
		mult -=5;
	}
	return res;
}

int get_card_score(char c, bool part2 = false) {
	if (c == 'A') return 20;
	if (c == 'K') return 19;
	if (c == 'Q') return 18;
	if (c == 'J') return part2 ? 1 : 17;
	if (c == 'T') return 16;
	return c-'0';
}

bool greater_hand(string h1, string h2, bool part2 = false) {
	int t1 = get_type(h1, part2);
	int t2 = get_type(h2, part2);
	if (t1 != t2) {
		return t1 > t2;
	}
	for(size_t i=0;i<h1.size();i++) {
		if(h1[i] != h2[i]) {
			return get_card_score(h1[i], part2) > get_card_score(h2[i], part2);
		}
	}
	return 0;
}

void prepare() {
	string s;
	while(getline(cin, s)){
		auto handsArr = split_line(s, " ");
		hands.push_back({handsArr[0], stoll(handsArr[1])});
	}
}

ll first() {
	ll res = 0;
	sort(hands.begin(), hands.end(), [](auto& h1, auto& h2)->bool{
		return greater_hand(h1.first, h2.first);
	});
	for(size_t i=0;i<hands.size();i++) {
		res += ((ll)(hands.size()-i)) * ((ll)hands[i].second);
	}
	return res;
}

ll second() {
	ll res = 0;
	sort(hands.begin(), hands.end(), [](auto& h1, auto& h2)->bool{
		return greater_hand(h1.first, h2.first, true);
	});
	for(size_t i=0;i<hands.size();i++) {
		res += ((ll)(hands.size()-i)) * ((ll)hands[i].second);
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
