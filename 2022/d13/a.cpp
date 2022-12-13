#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"
#include "signal.cpp"

typedef long long int ll;

//=======================================//

vector<pair<Signal*, Signal*>> signal_pairs;

void prepare() {
	string s;
	while(getline(cin, s)){
		if (s == "") continue;
		Signal *s1, *s2;
		s1 = Signal::parse(s);
		getline(cin, s);
		s2 = Signal::parse(s);
		signal_pairs.push_back(make_pair(s1,s2));
	}
}

ll first() {
	ll sum = 0;
	for(size_t i=0;i<signal_pairs.size();i++) {
		if (*(signal_pairs[i].first) < *(signal_pairs[i].second) && !(*(signal_pairs[i].second) < *(signal_pairs[i].first))) {
			sum += (i+1);
		}
	}
	return sum;
}

ll second() {
	vector<Signal*> all;
	for(auto &it : signal_pairs) {
		all.push_back(it.first);
		all.push_back(it.second);
	}
	Signal* s2 = Signal::parse("[[2]]");
	Signal* s6 = Signal::parse("[[6]]");
	all.push_back(s2);
	all.push_back(s6);
	sort(all.begin(), all.end(), [](auto*& left, auto*& right){
		return *left < *right;
	});
	vector<int> inds;
	int i=1;
	for(auto* sig : all) {
		if (sig == s2 || sig == s6) {
			inds.push_back(i);
		}
		i++;
	}
	return inds[0] * inds[1];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
