#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

struct Inp {
	string type;
	ll val;
};
vector<Inp> input;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		input.push_back(Inp{arr[0], stoll(arr[1])});
	}
}

ll first() {
	ll position=0, depth=0;
	for(auto& it : input) {
		if(it.type == "forward") {
			position += it.val;
		} else if(it.type == "down") {
			depth += it.val;
		} else {
			depth -= it.val;
		}
	}
	return position * depth;
}

ll second() {
	ll position=0, depth=0, aim=0;
	for(auto& it : input) {
		if(it.type == "down") {
			aim += it.val;
		} else if(it.type == "up") {
			aim -= it.val;
		} else {
			position += it.val;
			depth += it.val*aim;
		}
	}
	return position*depth;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
