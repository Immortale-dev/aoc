
#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(char) str = UNTIL_END();
};

Input input(std::cin);

ll first() {
	int res = 0;
	string str(input.str.begin(), input.str.end());
	regex mults("mul\\((\\d{1,3})\\,(\\d{1,3})\\)");
	for (auto b=sregex_iterator(str.begin(), str.end(), mults),e=sregex_iterator();b!=e;++b) {
		smatch match = *b;
		int n = stoi(match[1]);
		int m = stoi(match[2]);
		res += n * m;
	}
	return res;
}

ll second() {
	int res = 0;
	bool skip = false;
	string str(input.str.begin(), input.str.end());
	regex mults("mul\\((\\d{1,3})\\,(\\d{1,3})\\)|do\\(\\)|don\\'t\\(\\)");
	for (auto b=sregex_iterator(str.begin(), str.end(), mults),e=sregex_iterator();b!=e;++b) {
		smatch match = *b;
		if (match[0] == "don't()") {
			skip = true;
			continue;
		}
		if (match[0] == "do()") {
			skip = false;
			continue;
		}
		if (skip) continue;
		int n = stoi(match[1]);
		int m = stoi(match[2]);
		res += n * m;
	}
	return res;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
