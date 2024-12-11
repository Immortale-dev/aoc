#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(ll) stones = UNTIL_END();
};

Input input(std::cin);

bool even_digits(ll stone) {
	int a = log10(stone);
	return a&1;
}

pair<ll,ll> split_stone(ll stone) {
	int a = log10(stone);
	++a;
	ll half = pow(10,a/2);
	return {stone/half, stone%half};
}

ll calc_stones(vector<ll> stones, int steps) {
	unordered_map<ll,ll> mstones;
	for (auto s : stones) {
		mstones[s]++;
	}
	for (int i=0;i<steps;i++) {
		unordered_map<ll,ll> new_stones;
		for (auto &p : mstones) {
			ll stone = p.first;
			if (stone == 0) {
				new_stones[stone+1] += p.second;
				continue;
			}
			if (even_digits(stone)) {
				auto st = split_stone(stone);
				new_stones[st.first] += p.second;
				new_stones[st.second] += p.second;
				continue;
			}
			new_stones[stone*2024] += p.second;
		}
		mstones = new_stones;
	}
	ll res = 0;
	for (auto &p : mstones) {
		res += p.second;
	}
	return res;
}

ll first() {
	return calc_stones(vector(input.stones.begin(), input.stones.end()), 25);
}

ll second() {
	return calc_stones(vector(input.stones.begin(), input.stones.end()), 75);
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
