#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> nums;

void prepare() {
	string s;
	while(getline(cin, s)){
		nums.push_back(s);
	}
}

ll snaf_to_dec(string num) {
	ll mult = 1;
	ll res = 0;
	for(int i=num.size()-1;i>=0;i--) {
		int n;
		if (num[i] == '=') {
			n = -2;
		} else if (num[i] == '-') {
			n = -1;
		} else {
			n = num[i]-'0';
		}
		res += n*mult;
		mult *= 5;
	}
	return res;
}

string dec_to_snaf(ll num) {
	string res;
	bool next_plus = false;
	while(num) {
		if (next_plus) num++;
		int n = num%5LL;
		num /= 5LL;
		if (n > 2) {
			next_plus = true;
			if (n == 3) {
				res += '=';
			} else {
				res += '-';
			}
		} else {
			next_plus = false;
			res += n+'0';
		}
	}
	if (next_plus) {
		res += '1';
	}
	reverse(res.begin(), res.end());
	return res;
}

string first() {
	ll sum = 0;
	for(auto &s : nums) {
		sum += snaf_to_dec(s);
	}
	return dec_to_snaf(sum);
}

string second() {
	return "THAT'S ALL FOLKS";
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
