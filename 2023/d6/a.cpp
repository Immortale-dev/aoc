#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Race {
	int time;
	int distance;
};

vector<Race> races;

void prepare() {
	string s;
	vector<int> times;
	vector<int> distances;
	getline(cin, s);
	auto timesArr = split_line(split_line(s, ": ")[1]," ");
	for (auto t : timesArr) {
		if (!t.size()) continue;
		times.push_back(stoi(t));
	}
	getline(cin, s);
	auto durArr = split_line(split_line(s, ": ")[1]," ");
	for (auto d : durArr) {
		if (!d.size()) continue;
		distances.push_back(stoi(d));
	}
	for(size_t i=0;i<times.size();i++) {
		races.push_back({times[i], distances[i]});
	}
}

ll first() {
	vector<ll> ways;
	for(auto r : races) {
		int res = 0;
		for(int i=1;i<r.time;i++) {
			if (i * (r.time-i) > r.distance) {
				++res;
			}
		}
		ways.push_back(res);
	}
	ll result = 1;
	for(ll r : ways) {
		result *= r;
	}
	return result;
}

ll second() {
	string bigt, bigd;
	for(auto r : races) {
		bigt += to_string(r.time);
		bigd += to_string(r.distance);
	}
	ll time = stoll(bigt);
	ll distance = stoll(bigd);
	ll res = 0;
	for(ll i=1;i<time;i++) {
		if (i * (time-i) > distance) {
			++res;
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
