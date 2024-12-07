#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
using ll = long long int;

//=======================================//

DEFINE_PARSE_INTERFACE(Test) {
	PARSE_SETUP;
	PARSE(ll) result = SINGLE();
	SKIP(char) = SINGLE(':');
	PARSE(ll) values = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Test) tests = UNTIL_END();
};

Input input(std::cin);

ll first() {
	ll res = 0;
	for (auto test : input.tests) {
		int until = 1 << test.values.size();
		for (int i=0;i<until;++i) {
			ll local = test.values[0];
			for (int j=1;j<test.values.size();++j) {
				if (i & (1 << (j-1))) {
					local += test.values[j];
				} else {
					local *= test.values[j];
				}
			}
			if (local == test.result()) {
				res += local;
				break;
			}
		}
	}
	return res;
}

ll conc(ll a, ll b) {
	vector<int> d;
	while(b > 0) {
		d.push_back(b%10);
		b/=10;
	}
	reverse(d.begin(), d.end());
	for (int v : d) a = a*10 + v;
	return a;
}

ll second() {
	ll res = 0;
	int l=0;
	for (auto test : input.tests) {
		ll until = pow(3, test.values.size()-1);
		for (int i=0;i<until;++i) {
			ll current = i;
			ll local = test.values[0];
			for (int j=1;j<test.values.size();++j) {
				int op = current % 3;
				current /= 3;
				if (op == 0) {
					local += test.values[j];
				} else if (op == 1) {
					local *= test.values[j];
				} else {
					local = conc(local, test.values[j]);
				}
			}
			if (local == test.result()) {
				res += local;
				break;
			}
		}
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
