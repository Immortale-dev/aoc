#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<ll> input;

void prepare() {
	string s;
	getline(cin, s);
	auto arr = split_line(s, ",");
	for(auto& it : arr) {
		input.push_back(stoi(it));
	}
	sort(input.begin(), input.end());
}

ll crab_fuel(ll median) {
	ll fuel = 0;
	for(auto& it : input) {
		ll dist = abs(it-median);
		fuel += (dist*(dist+1))/2;
	}
	return fuel;
}

ll first() {
	int median;
	if(input.size() % 2) {
		median = input[input.size()/2];
	} else {
		median = (input[input.size()/2] + input[input.size()/2-1])/2;
	}
	int res = 0;
	for(auto& it : input){
		res += abs(median-it);
	}
	return res;
}

ll second() {
	int maxc = input[input.size()-1];
	int minc = input[0];
	
	ll minf = 9999999999999;
	for(int i=minc;i<=maxc;i++){
		minf = min(minf, crab_fuel(i));
	}
	
	return minf;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
