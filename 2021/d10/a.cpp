#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<string> input;

map<char, char> close_match{{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};

pair<int,list<char> > find_corrupted(string s) {
	list<char> opens;
	for(int i=0;i<s.size();i++){
		char c = s[i];
		if(c == '(' || c == '[' || c == '{' || c == '<') {
			opens.push_back(c);
		} else {
			if(close_match[opens.back()] != c) {
				return make_pair(i,opens);
			}
			opens.pop_back();
		}
	}
	return make_pair(-1,opens);
}

void prepare() {
	string s;
	while(getline(cin, s)){
		input.push_back(s);
	}
}

ll first() {
	map<char,int> scores{ {')',3}, {']', 57}, {'}', 1197}, {'>', 25137} };
	ll res = 0;
	for(auto& it : input){
		auto ret = find_corrupted(it);
		if(ret.first >= 0) {
			res += scores[it[ret.first]];
		}
	}
	return res;
}

ll second() {
	map<char,int> scores{ {')',1}, {']', 2}, {'}', 3}, {'>', 4} };
	vector<ll> res;
	for(auto& it : input){
		ll numb = 0;
		auto ret = find_corrupted(it);
		if(ret.first < 0) {
			list<char> opens = ret.second;
			while(!opens.empty()) {
				char c = opens.back();
				opens.pop_back();
				numb *= 5;
				numb += scores[close_match[c]];
			}
			res.push_back(numb);
		}
	}
	sort(res.begin(),res.end());

	return res[res.size()/2];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
