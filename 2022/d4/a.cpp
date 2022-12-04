#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<pair<pair<int,int>,pair<int,int>>> pairs;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto e_pair = split_line(s, ",");
		auto first = split_line(e_pair[0], "-");
		auto second = split_line(e_pair[1], "-");
		pairs.push_back(make_pair(make_pair(stoi(first[0]),stoi(first[1])),make_pair(stoi(second[0]),stoi(second[1]))));
	}
}

ll first() {
	int cnt = 0;
	for(auto& pair : pairs) {
		auto& first = pair.first;
		auto& second = pair.second;
		if(first.first >= second.first && first.second <= second.second || first.first <= second.first && first.second >= second.second) {
			cnt++;
		}
	}
	return cnt;
}

ll second() {
	int cnt = 0;
	for(auto& pair : pairs) {
		auto& first = pair.first;
		auto& second = pair.second;
		if(first.first >= second.first && first.first <= second.second ||
		   first.second >= second.first && first.second <= second.second ||
		   second.first >= first.first && second.first <= first.second ||
		   second.second >= first.first && second.second <= first.second) {
			cnt++;
		}
	}
	return cnt;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
