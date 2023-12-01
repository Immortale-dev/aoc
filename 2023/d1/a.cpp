#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> lines;

void prepare() {
	string s;
	while(getline(cin, s)){
		lines.push_back(s);
	}
}

ll first() {
	ll res = 0;
	for(auto s : lines) {
		int fd,ld;
		bool was = false;
		for(size_t i=0;i<s.size();i++) {
			if (s[i] >= '1' && s[i] <= '9') {
				if (!was) {
					was = true;
					fd = s[i]-'0';
				}
				ld = s[i]-'0';
			}
		}
		res += fd*10+ld;
	}
	return res;
}

ll second() {
	vector<string> real_lines = lines;
	for(auto& s : real_lines) {
		s = replace_all(s, "one", "one1one");
		s = replace_all(s, "two", "two2two");
		s = replace_all(s, "three", "three3three");
		s = replace_all(s, "four", "four4four");
		s = replace_all(s, "five", "five5five");
		s = replace_all(s, "six", "six6six");
		s = replace_all(s, "seven", "seven7seven");
		s = replace_all(s, "eight", "eight8eight");
		s = replace_all(s, "nine", "nine9nine");
	}

	lines = real_lines;
	return first();
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
