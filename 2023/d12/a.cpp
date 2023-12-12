#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Report {
	string line;
	vector<int> groups;
};

vector<Report> reports;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		auto numArr = split_line(arr[1], ",");
		vector<int> nums;
		for (string n : numArr) {
			nums.push_back(stoi(n));
		}
		reports.push_back({arr[0], nums});
	}
}

class ResGen {
	public:
		ResGen(string s) : _str(s) {
			for(size_t i=0;i<_str.size();i++) {
				if (_str[i] == '?') {
					_q_pos.push_back(i);
				}
			}
			_variants = 1<<_q_pos.size();
		}
		int size() {
			return _variants;
		}
		string next() {
			for(int j=0;j<(int)_q_pos.size();j++) {
				char c = (_ind & (1<<j)) ? '.' : '#';
				_str[_q_pos[j]] = c;
			}
			++_ind;
			return _str;
		}
	private:
		string _str;
		vector<int> _q_pos;
		int _variants;
		int _ind = 0;
};

int checkPos(vector<int>& groups, int ind, string& s) {
	vector<int> res;
	int cont = 0;
	for(size_t i=0;i<s.size();i++){
		if (s[i] == '#') {
			cont ++;
		} else {
			if (cont) {
				res.push_back(cont);
			}
			cont = 0;
		}
	}
	if (cont) {
		res.push_back(cont);
	}
	if (res.size() > groups.size()-ind) {
		return -1;
	}
	for(size_t i=0;i<res.size();i++) {
		if (groups[ind] != res[i]) return -1;
		ind++;
	}
	return ind;
}

bool check(string& line, int ind, int group) {
	if(ind + group > line.size()) return false;
	if(ind + group < line.size() && line[ind+group] == '#') return false;
	for(int i=ind;i<group+ind;i++) {
		if (line[i] == '.') return false;
	}
	return true;
}

ll first() {
	ll result = 0;
	for(auto report : reports) {
		ResGen g(report.line);
		for(int i=0;i<g.size();i++) {
			string line = g.next();
			if (checkPos(report.groups, 0, line) == report.groups.size()) {
				result++;
			}
		}
	}
	return result;
}

ll second() {
	ll result = 0;
	int progress = 0;
	for(auto report : reports) {
		string new_line = report.line + "?" + report.line + "?" + report.line + "?" + report.line + "?" + report.line;
		vector<int> groups;
		for(int i=0;i<5;i++) {
			for(auto n : report.groups) {
				groups.push_back(n);
			}
		}

		map<int, ll> mem;
		mem[0] = 1;
		for(auto g : groups) {
			map<int, ll> new_mem;
			for(auto m : mem) {
				for(int i=m.first;i<(int)new_line.size();i++) {
					if (check(new_line, i, g)) {
						new_mem[i+g+1] += m.second;
					}
					if (new_line[i] == '#') break;
				}
			}
			mem = new_mem;
		}
		ll local_res = 0;
		for(auto m : mem) {
			bool good = true;
			for(int i=m.first;i<new_line.size();i++) {
				if (new_line[i] == '#') {
					good = false;
					break;
				}
			}
			if (good) {
				local_res += m.second;
			}
		}
		result += local_res;
	}
	return result;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
