#include <bits/stdc++.h>

using namespace std;

#include "../helpers/parser.h"

typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Report) {
	PARSE_SETUP;
	PARSE(int) levels = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Report) reports = UNTIL_END();
};

Input input(std::cin);

bool isSafe(span<int> levels) {
	bool inc = levels[1] - levels[0] > 0;
	for (int i=1;i<levels.size();i++) {
		int diff = levels[i] - levels[i-1];
		if (abs(diff) <= 0 || abs(diff) > 3 || inc && diff < 0 || !inc && diff > 0) {
			return false;
		}
	}
	return true;
}

ll first() {
	int res = 0;
	for (auto& report : input.reports) {
		if (isSafe(span(report.levels.begin(), report.levels.end()))) ++res;
	}
	return res;
}

ll second() {
	int res = 0;
	for (auto& report : input.reports) {
		for (int i=0;i<report.levels.size();i++) {
			vector vec(report.levels.begin(), report.levels.end());
			vec.erase(vec.begin() + i);
			if (isSafe(vec)) {
				++res;
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
