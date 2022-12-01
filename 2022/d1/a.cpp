#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<ll>> elves_calories;

void prepare() {
	vector<ll> calories;
	string s;
	while(getline(cin, s)){
		if (s == "") {
			elves_calories.push_back(calories);
			calories = vector<ll>();
		} else {
			calories.push_back(stoll(s));
		}
	}
}

ll first() {
	ll max_calories = 0;
	for(auto& elf : elves_calories) {
		ll sum = 0;
		for(ll cal : elf) {
			sum += cal;
		}
		max_calories = max(sum, max_calories);
	}
	return max_calories;
}

ll second() {
	vector<ll> sums;
	for(auto& elf : elves_calories) {
		ll sum = 0;
		for(ll cal : elf) {
			sum += cal;
		}
		sums.push_back(sum);
	}
	sort(sums.begin(), sums.end(), [](ll& left, ll& right){
		return left > right;
	});
	return sums[0] + sums[1] + sums[2];
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
