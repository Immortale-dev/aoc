#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Line) {
	PARSE_SETUP;
	PARSE(char) turn = SINGLE();
	PARSE(int) size = SINGLE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Line) lines = UNTIL_END();
};

Input input(std::cin);

ll first() {
	int start = 50;
	int res = 0;
	for (auto &l : input.lines) {
		if (l.turn() == 'L') {
			start = (start + 1000 - l.size())%100;
		} else {
			start = (start + l.size())%100;
		}
		if (start == 0) res++;
	}
	return res;
}

ll second() {
	int start = 50;
	int res = 0;
	for (auto &l : input.lines) {
		int sz = l.size();
		if (l.turn() == 'L') {
			while(sz--) {
				start = (start + 100 - 1)%100;
				if (start == 0) res++;
			}
		} else {
			while(sz--) {
				start = (start + 1)%100;
				if (start == 0) res++;
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
