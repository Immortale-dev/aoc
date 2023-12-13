#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<vector<string>> patterns;

void prepare() {
	string s;
	vector<string> pattern;
	while(getline(cin, s)){
		if (!s.size()) {
			patterns.push_back(pattern);
			pattern.resize(0);
			continue;
		}
		pattern.push_back(s);
	}
	if (pattern.size()) {
		patterns.push_back(pattern);
	}
}

ll find_v_mirror(vector<string>& pattern, int smug = 0) {
	int h = pattern.size();
	int w = pattern.front().size();
	for(int i=1;i<w;i++) {
		bool ok = true;
		int sc = 0;
		for(int j=0;j<min(i,w-i);j++) {
			for(int k=0;k<h;k++) {
				if (pattern[k][i+j] != pattern[k][i-1-j]) {
					if(++sc > smug) {
						ok = false;
						break;
					}
				}
			}
			if (!ok) {
				break;
			}
		}
		if (ok && smug == sc) {
			return i;
		}
	}
	return 0;
}

ll find_h_mirror(vector<string>& pattern, int smug = 0) {
	int h = pattern.size();
	int w = pattern.front().size();
	for(int i=1;i<h;i++) {
		bool ok = true;
		int sc = 0;
		for(int j=0;j<min(i,h-i);j++) {
			for(int k=0;k<w;k++) {
				if (pattern[i+j][k] != pattern[i-1-j][k]) {
					if (++sc > smug) {
						ok = false;
						break;
					}
				}
			}
			if (!ok) {
				break;
			}
		}
		if (ok && smug == sc) {
			return i;
		}
	}
	return 0;
}

ll first() {
	ll res = 0;
	for(auto pattern : patterns) {
		ll vm = find_v_mirror(pattern);
		ll hm = find_h_mirror(pattern);
		res += hm*100 + vm;
	}
	return res;
}

ll second() {
	ll res = 0;
	for(auto pattern : patterns) {
		ll vm = find_v_mirror(pattern,1);
		ll hm = find_h_mirror(pattern,1);
		res += hm*100 + vm;
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
