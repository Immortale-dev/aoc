#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

struct Step {
	char dir;
	int moves;
	string color;
};

vector<Step> steps;

int H = 1000;
int W = 1000;
int CY = 500;
int CX = 500;

void prepare() {
	string s;
	while(getline(cin, s)){
		auto arr = split_line(s, " ");
		char c = arr[0][0];
		int moves = stoi(arr[1]);
		string color = arr[2].substr(2, 6);
		steps.push_back({c, moves, color});
	}
}

pair<int,int> get_pluses(char d) {
	if (d == 'R') return {0,1};
	if (d == 'U') return {-1,0};
	if (d == 'L') return {0,-1};
	if (d == 'D') return {1,0};
	throw logic_error("wrong direction");
}

void print_trench(vector<vector<bool>>& trench) {
	int mnx=9999999,mxx=0,mny=9999999,mxy=0;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (trench[i][j]) {
				mnx = min(mnx, j);
				mxx = max(mxx, j);
				mny = min(mny, i);
				mxy = max(mxy, i);
			}
		}
	}
	cout << endl;
	for(int i=mny;i<=mxy;i++) {
		for(int j=mnx;j<=mxx;j++) {
			cout << (trench[i][j] ? "#" : ".");
		}
		cout << endl;
	}
}

pair<int,int> get_y_bounds(vector<vector<bool>>& trench) {
	int mn=9999999,mx=0;
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (trench[i][j]) {
				mn = min(mn, i);
				mx = max(mx, i);
			}
		}
	}
	return {mn,mx};
}

struct Seg {
	ll start;
	ll finish;
	ll x;
	bool up;
};

bool is_mid(ll i, Seg& s) {
	return s.start < i && s.finish > i;
}
bool is_top(ll i, Seg& s) {
	return s.start == i;
}
bool is_bot(ll i, Seg& s) {
	return s.finish == i;
}

ll solve_trench(vector<Step>& trench) {
	vector<Seg> segs;
	int cx = 0;
	int cy = 0;

	for(auto &t : trench) {
		char dir = t.dir;
		ll moves = t.moves;
		if (dir == 'U') {
			segs.push_back({cy-moves, cy, cx, true});
			cy-=moves;
		} else if (dir == 'D') {
			segs.push_back({cy, cy+moves, cx, false});
			cy+=moves;
		} else if (dir == 'R') {
			cx += moves;
		} else {
			cx -= moves;
		}
	}

	ll mny = 99999999999999;
	ll mxy = -99999999999999;
	for(auto &s : segs) {
		mny = min(mny, s.start);
		mxy = max(mxy, s.finish);
	}

	sort(segs.begin(), segs.end(), [](auto& left, auto& right){
		return left.start < right.start;
	});

	map<ll, Seg> xmap;
	int ind = 0;
	ll res = 0;

	for(ll i=mny;i<=mxy;i++) {
		ll l_res = 0;

		vector<ll> del;
		for(auto& s : xmap) {
			if (s.second.finish < i) {
				del.push_back(s.first);
			}
		}
		for(auto d : del) {
			xmap.erase(d);
		}
		while (ind < segs.size() && i >= segs[ind].start) {
			auto& s = segs[ind];
			xmap.insert({s.x, s});
			ind++;
		}

		bool on = false;
		vector<pair<ll, Seg>> stps;
		for(auto& s : xmap) {
			stps.push_back(s);
		}
		for(int j=0;j<stps.size();j++) {
			if (on) {
				l_res += stps[j].first - stps[j-1].first - 1;
			}
			if (is_mid(i, stps[j].second)) {
				on = !on;
				continue;
			}
			if (is_top(i, stps[j].second) && is_bot(i, stps[j+1].second) || is_bot(i, stps[j].second) && is_top(i, stps[j+1].second)) {
				on = !on;
			}
			if (is_top(i, stps[j].second) || is_bot(i, stps[j].second)) {
				l_res += stps[j+1].first - stps[j].first - 1;
				j++;
			}
		}
		l_res += stps.size();
		res += l_res;
	}

	return res;
}

ll first() {
	return solve_trench(steps);
}

ll second() {
	vector<Step> new_trench;
	for(auto& m : steps) {
		int moves = 0;
		string moves_c = m.color.substr(0,5);
		char dir_c = m.color[5]-'0';
		char dir;
		if (dir_c == 0) {
			dir = 'R';
		} else if (dir_c == 1) {
			dir = 'D';
		} else if (dir_c == 2) {
			dir = 'L';
		} else {
			dir = 'U';
		}
		for(int i=0;i<moves_c.size();i++) {
			moves *= 16;
			if (moves_c[i] >= '0' && moves_c[i] <= '9') {
				moves += moves_c[i]-'0';
			} else {
				moves += moves_c[i]-'a'+10;
			}
		}
		new_trench.push_back({dir, moves, m.color});
	}

	return solve_trench(new_trench);
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
