#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

vector<int> input;

void prepare() {
	string s;
	getline(cin, s);
	auto arr = split_line(s, ",");
	for(auto& it : arr){
		input.push_back(stoi(it));
	}
}

ll calc(vector<ll> timers, int count) {
	for(int i=0;i<count;i++) {
		vector<ll> new_timers(10);
		for(int i=0;i<10;i++) {
			if(!i){
				new_timers[8] += timers[i];
				new_timers[6] += timers[i];
			} else {
				new_timers[i-1] += timers[i];
			}
		}
		timers = new_timers;
	}
	
	ll sum = 0;
	for(int i=0;i<10;i++) {
		sum += timers[i];
	}
	
	return sum;
}

ll first() {
	vector<ll> timers(10);
	for(auto& it : input) {
		timers[it]++;
	}
	return calc(timers, 80);
}

ll second() {
	vector<ll> timers(10);
	for(auto& it : input) {
		timers[it]++;
	}
	return calc(timers, 256);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
