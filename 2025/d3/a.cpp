#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(std::string) batteries = UNTIL_END();
};

Input input(std::cin);

ll first() {
	ll res = 0;
	for (auto &s : input.batteries) {
		std::vector<std::pair<int, int>> nums;
		int index = 0;
		for (auto c : s) {
			nums.push_back({c-'0', index++});
		}
		sort(nums.begin(), nums.end(), [](auto& p1, auto& p2){
			if (p1.first == p2.first) return p1.second < p2.second;
			return p1.first > p2.first;
		});
		auto [first_num, first_index] = nums[0];
		if (first_index == nums.size()-1) {
			res += nums[1].first * 10 + first_num;
			continue;
		}
		for (int i=1;i<nums.size();i++) {
			if (nums[i].second > first_index) {
				res += first_num * 10 + nums[i].first;
				break;
			}
		}
	}
	return res;
}

ll second() {
	ll res = 0;
	for (auto bat : input.batteries) {
		int layers = 15;
		int pins = bat.size();
		std::vector<ll> nums(pins+1, 0);
		for (int i=0;i<pins;i++) {
			nums[i+1] = bat[i]-'0';
		}
		vector<vector<ll>> dp(layers, std::vector<ll>(pins+1, 0));
		for (int l=1;l<layers;l++) {
			for (int i=1;i<=pins;i++) {
				dp[l][i] = std::max(dp[l][i-1], dp[l-1][i-1] * 10 + nums[i]);
			}
		}
		ll lres = 0;
		for (int i=1;i<=pins;i++) {
			lres = std::max(lres, dp[12][i]);
		}
		res += lres;
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
