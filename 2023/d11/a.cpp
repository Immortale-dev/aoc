#include <bits/stdc++.h>

using namespace std;

#include "../helpers/string_helpers.cpp"

typedef long long int ll;

//=======================================//

vector<string> grid;
vector<int> h_empt;
vector<int> v_empt;
vector<pair<int,int>> positions;
int W,H;

void prepare() {
	string s;
	while(getline(cin, s)){
		grid.push_back(s);
	}
	H = grid.size();
	W = grid[0].size();
	h_empt = vector<int>(H, 0);
	v_empt = vector<int>(W, 0);
	for(int i=0;i<H;i++) {
		bool empt = true;
		for(int j=0;j<W;j++) {
			if (grid[i][j] == '#') {
				empt = false;
				break;
			}
		}
		if (empt) {
			h_empt[i] = 1;
		}
	}
	for(int i=0;i<W;i++) {
		bool empt = true;
		for(int j=0;j<H;j++) {
			if (grid[j][i] == '#') {
				empt = false;
				break;
			}
		}
		if (empt) {
			v_empt[i] = 1;
		}
	}
	int assign = 0;
	for(int i=0;i<H;i++) {
		if (h_empt[i]) ++assign;
		h_empt[i] = assign;
	}
	assign = 0;
	for(int i=0;i<W;i++) {
		if (v_empt[i]) ++assign;
		v_empt[i] = assign;
	}
	for(int i=0;i<H;i++) {
		for(int j=0;j<W;j++) {
			if (grid[i][j] == '#') {
				positions.push_back({i,j});
			}
		}
	}
}

ll first() {
	ll res = 0;
	int pos_size = positions.size();
	for(int i=0;i<pos_size;i++) {
		for(int j=i+1;j<pos_size;j++) {
			auto g1 = positions[i];
			auto g2 = positions[j];
			res += abs(g1.first - g2.first) + abs(g1.second - g2.second) +
					abs(h_empt[g1.first] - h_empt[g2.first]) + abs(v_empt[g1.second] - v_empt[g2.second]);
		}
	}
	return res;
}

ll second() {
	ll res = 0;
	int pos_size = positions.size();
	for(int i=0;i<pos_size;i++) {
		for(int j=i+1;j<pos_size;j++) {
			auto g1 = positions[i];
			auto g2 = positions[j];
			res += abs(g1.first - g2.first) + abs(g1.second - g2.second) +
					abs(h_empt[g1.first] - h_empt[g2.first])*999999 + abs(v_empt[g1.second] - v_empt[g2.second])*999999;
		}
	}
	return res;
}

int main() {
	prepare();
	cout << "First: " << first() << endl;
	cout << "Second: " << second() << endl;
	return 0;
}
