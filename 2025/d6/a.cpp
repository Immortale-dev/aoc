#include <bits/stdc++.h>
#include "../helpers/parser.h"

using namespace std;
typedef long long int ll;

//=======================================//

DEFINE_PARSE_INTERFACE(Row) {
	PARSE_SETUP;
	PARSE(char) nums = THROUGH_LINE();
};

DEFINE_PARSE_INTERFACE(Input) {
	PARSE_SETUP;
	PARSE(Row) rows = UNTIL_END();
};

Input input(std::cin);

ll first() {
	vector<vector<ll>> num_lines;
	vector<char> signs;
	for (int i=0;i<input.rows.size()-1;i++) {
		vector<ll> line;
		stringstream ss(string(input.rows[i].nums.begin(), input.rows[i].nums.end()));
		while(!ss.eof()) {
			ll a;
			if (ss >> a) {
				line.push_back(a);
			}
		}
		num_lines.push_back(std::move(line));
	}
	stringstream ss(string(input.rows.vector().back().nums.begin(), input.rows.vector().back().nums.end()));
	while (!ss.eof()) {
		string s;
		if (ss >> s) {
			signs.push_back(s[0]);
		}
	}

	for (auto &r : num_lines) {
		assert(r.size() == signs.size());
	}

	ll result = 0;
	for (int j=0;j<signs.size();j++) {
		ll res = num_lines[0][j];
		for (int i=1;i<num_lines.size();i++) {
			if (signs[j] == '+') {
				res += num_lines[i][j];
			} else {
				res *= num_lines[i][j];
			}
		}
		result += res;
	}
	return result;
}

ll second() {
	vector<string> new_lines;
	size_t max_sz = 0;
	for (int i=0;i<input.rows.size();i++) {
		max_sz = max(max_sz, input.rows[i].nums.size());
	}
	vector<string> lines;
	for (int i=0;i<input.rows.size();i++) {
		if (input.rows[i].nums.size() < max_sz) {
			string s;
			for (int j=0;j<max_sz-input.rows[i].nums.size();j++) s.push_back(' ');
			lines.push_back(s + string(input.rows[i].nums.begin(), input.rows[i].nums.end()));
		} else {
			lines.push_back(string(input.rows[i].nums.begin(), input.rows[i].nums.end()));
		}
	}
	for (int i=0;i<lines.size()-1;i++) {
		assert(lines[i].size() == lines.back().size());
	}

	string str;
	for (int i=0;i<lines[0].size();i++) {
		bool all_empty = true;
		string s;
		for (int j=0;j<lines.size()-1;j++) {
			if (lines[j][i] != ' ') all_empty = false;
			s.push_back(lines[j][i]);
		}
		s.push_back(' ');
		if (all_empty && !s.empty()) {
			new_lines.push_back(str);
			str = "";
			continue;
		}
		str += s;
	}
	if (str.size()) {
		new_lines.push_back(str);
	}

	vector<char> signs;
	stringstream ss(lines.back());
	while (!ss.eof()) {
		string s;
		if (ss >> s) {
			signs.push_back(s[0]);
		}
	}

	ll result = 0;
	int ind = 0;
	for (auto &s : new_lines) {
		stringstream ss(s);
		ll a;
		ll res = signs[ind] == '+' ? 0 : 1;
		while (ss >> a) {
			if (signs[ind] == '+') {
				res += a;
			} else {
				res *= a;
			}
		}
		result += res;
		ind++;
	}
	return result;
}

int main() {
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
